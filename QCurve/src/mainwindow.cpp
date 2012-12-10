#include "mainwindow.h"

#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>

#include "Widgets/Splitter"
#include "Models/FunctionItemModel"
#include "functionwidget.h"

#include "Functions/Ellipse"
#include "Functions/Parabola"
#include "Functions/Hyperbola"
#include "Functions/Strophoid"
#include "Functions/Cissoid"
#include "Functions/Limacon"
#include "Functions/Lemniscate"

#include "Functions/ArchimedeanSpiral"
#include "Functions/LogarithmicSpiral"
#include "Functions/Helix"
#include "Functions/Cycloid"
#include "Functions/Hypocycloid"
#include "Functions/Tractrix"
#include "Functions/Catenary"
#include "Functions/Astroid"
#include "Functions/Clothoids"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
  setWindowTitle("Parametric Curve Viewer");
  //setWindowIcon(QIcon());

  initMenu();
  initComponents();
  
  m_functionItemModel->addCategory(tr("Rational functions"));
  //m_functionItemModel->addFunction(tr("Line"), tr("Rational functions");
  //m_functionItemModel->addFunction(tr("Polynomial"), tr("Rational functions");
  
  m_functionItemModel->addCategory(tr("Nonrational functions"));
  
  m_functionItemModel->addCategory(tr("Plane algebraic curve of degree 2 (Conic sections)"));
  m_functionItemModel->addFunction(Ellipse(1, 1), tr("Plane algebraic curve of degree 2 (Conic sections)"));
  m_functionItemModel->addFunction(Ellipse(), tr("Plane algebraic curve of degree 2 (Conic sections)"));
  m_functionItemModel->addFunction(Parabola(), tr("Plane algebraic curve of degree 2 (Conic sections)"));
  m_functionItemModel->addFunction(Hyperbola(), tr("Plane algebraic curve of degree 2 (Conic sections)"));
  
  m_functionItemModel->addCategory(tr("Plane algebraic curve of degree 3"));
  m_functionItemModel->addFunction(Strophoid(), tr("Plane algebraic curve of degree 3"));
  m_functionItemModel->addFunction(Cissoid(), tr("Plane algebraic curve of degree 3"));
  
  m_functionItemModel->addCategory(tr("Plane algebraic curve of degree 4"));
  m_functionItemModel->addFunction(Limacon(), tr("Plane algebraic curve of degree 4"));
  m_functionItemModel->addFunction(Lemniscate(), tr("Plane algebraic curve of degree 4"));
  
  m_functionItemModel->addCategory(tr("Cycloids"));
  m_functionItemModel->addFunction(Cycloid(), tr("Cycloids"));
  m_functionItemModel->addFunction(Astroid(), tr("Cycloids"));
  m_functionItemModel->addFunction(Hypocycloid(), tr("Cycloids"));
  
  m_functionItemModel->addCategory(tr("Spirals"));
  m_functionItemModel->addFunction(ArchimedeanSpiral(), tr("Spirals"));
  m_functionItemModel->addFunction(LogarithmicSpiral(), tr("Spirals"));
  
  m_functionItemModel->addCategory(tr("Other curves"));
  m_functionItemModel->addFunction(Catenary(), tr("Other curves"));
  m_functionItemModel->addFunction(Clothoids(1), tr("Other curves"));
  m_functionItemModel->addFunction(Tractrix(), tr("Other curves"));
  
  m_functionItemModel->addCategory(tr("3D curves"));
  m_functionItemModel->addFunction(Helix(), tr("3D curves"));
  
  connect(m_splitter, SIGNAL(mouseDoubleClicked()), this, SLOT(splitterDoubleClicked()));
  connect(m_treeView, SIGNAL(activated(QModelIndex)), this, SLOT(itemActivated(QModelIndex)));
}

MainWindow::~MainWindow()
{ }

void MainWindow::itemActivated(const QModelIndex& idx)
{
  Function* func = m_functionItemModel->functionAt(idx);
  
  if (func)
  { m_functionWgt->setFunction(*func); }
}

void MainWindow::initMenu()
{
  QMenuBar* menubar = new QMenuBar();
  
  QMenu* menu = new QMenu(tr("File"));
  QMenu* subMenu = new QMenu(tr("Export"));
  menu->addMenu(subMenu);
  menu->addSeparator();
  QAction* action = new QAction(QIcon::fromTheme("window-close"), tr("Close"), this);
  connect(action, SIGNAL(triggered(bool)), this, SLOT(close()));
  menu->addAction(action);
  menubar->addMenu(menu);
  
  menu = new QMenu(tr("Edit"));
  menubar->addMenu(menu);
  
  menu = new QMenu(tr("View"));
  menubar->addMenu(menu);
  
  menu = new QMenu(tr("Help"));
  action = new QAction(QIcon::fromTheme("help-contents"), tr("Help"), this);
  //connect(action, SIGNAL(triggered(bool)), this, SLOT(close()));
  menu->addAction(action);
  menu->addSeparator();
  action = new QAction(QIcon::fromTheme("help-about"), tr("About"), this);
  //connect(action, SIGNAL(triggered(bool)), this, SLOT(close()));
  menu->addAction(action);
  menubar->addMenu(menu);
  
  setMenuBar(menubar);
}

void MainWindow::initComponents()
{
  m_functionItemModel = new FunctionItemModel(this);
  
  m_treeView = new QTreeView();
  m_treeView->setModel(m_functionItemModel);
  
  m_functionWgt = new FunctionWidget();
  
  m_splitter = new Splitter();
  m_splitter->addWidget(m_treeView);
  m_splitter->addWidget(m_functionWgt);
  
  setCentralWidget(m_splitter);
}

void MainWindow::splitterDoubleClicked()
{ m_splitter->setWidgetCollapsed(0, !m_splitter->isWidgetCollapsed(0)); }
