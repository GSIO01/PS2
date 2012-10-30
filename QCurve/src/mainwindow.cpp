#include "mainwindow.h"

#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>

#include <Widgets/Splitter>

#include "functionwidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
  setWindowTitle("Parametric Curve Viewer");
  //setWindowIcon(QIcon());

  initMenu();
  initComponents();
  
  connect(m_splitter, SIGNAL(mouseDoubleClicked()), this, SLOT(splitterDoubleClicked()));
}

MainWindow::~MainWindow()
{ }

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
  m_treeView = new QTreeView();
  
  m_functionWgt = new FunctionWidget();
  
  m_splitter = new Splitter();
  m_splitter->addWidget(m_treeView);
  m_splitter->addWidget(m_functionWgt);
  
  setCentralWidget(m_splitter);
}

void MainWindow::splitterDoubleClicked()
{ m_splitter->setWidgetCollapsed(0, !m_splitter->isWidgetCollapsed(0)); }