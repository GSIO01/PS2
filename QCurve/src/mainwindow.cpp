#include "mainwindow.h"

#include <QtCore/QTimer>
#include <QtCore/QDir>
#include <QtCore/QDebug>

#include <QtGui/QApplication>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QActionGroup>

#include "Widgets/Splitter"
#include "Models/FunctionItemModel"
#include "functionwidget.h"

#include "Functions/Functions"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
  switchTranslator(m_translator, "de");

  setWindowTitle(tr("Parametric Curve Viewer"));
  //setWindowIcon(QIcon());

  initMenu();
  initComponents();

  QTimer::singleShot(0, this, SLOT(init()));
}

MainWindow::~MainWindow()
{ }

void MainWindow::init()
{
  connect(m_splitter, SIGNAL(mouseDoubleClicked()), this, SLOT(splitterDoubleClicked()));
  connect(m_treeView, SIGNAL(activated(QModelIndex)), this, SLOT(itemActivated(QModelIndex)));

  initFunctions();

  m_functionWgt->setFunction(Ellipse());
}

void MainWindow::itemActivated(const QModelIndex& idx)
{
  Function* func = m_functionItemModel->functionAt(idx);

  if (func)
  { m_functionWgt->setFunction(*func); }
}

void MainWindow::initFunctions()
{
  //TODO use a function creator instead...

  m_functionItemModel->addCategory(tr("Rational functions"));
  //m_functionItemModel->addFunction(tr("Line"), tr("Rational functions"));
  //m_functionItemModel->addFunction(tr("Polynomial"), tr("Rational functions"));

  m_functionItemModel->addCategory(tr("Nonrational functions"));

  m_functionItemModel->addCategory(tr("Plane algebraic curve of degree 2 (Conic sections)"));
  m_functionItemModel->addFunction(Circle(), tr("Plane algebraic curve of degree 2 (Conic sections)"));
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

  QFontMetrics fm(font());
  m_treeView->setMaximumWidth(fm.width(tr("Plane algebraic curve of degree 2 (Conic sections)")) + 48);
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

  subMenu = new QMenu(tr("Projection"));
  QActionGroup* actionGroup = new QActionGroup(this);
  action = new QAction(tr("Paralell"), this);
  action->setCheckable(true);
  action->setEnabled(false);
  actionGroup->addAction(action);
  subMenu->addAction(action);
  action = new QAction(tr("Perspective"), this);
  action->setCheckable(true);
  action->setChecked(true);
  actionGroup->addAction(action);
  subMenu->addAction(action);
  menu->addMenu(subMenu);

  subMenu = new QMenu(tr("Animation"));
  actionGroup = new QActionGroup(this);
  action = new QAction(tr("Repeat"), this);
  action->setCheckable(true);
  action->setData(0);
  actionGroup->addAction(action);
  connect(action, SIGNAL(triggered(bool)), this, SLOT(setAnimationMode()));
  subMenu->addAction(action);
  action = new QAction(tr("Once"), this);
  action->setCheckable(true);
  action->setChecked(true);
  action->setData(1);
  actionGroup->addAction(action);
  connect(action, SIGNAL(triggered(bool)), this, SLOT(setAnimationMode()));
  subMenu->addAction(action);
  action = new QAction(tr("None"), this);
  action->setCheckable(true);
  action->setData(2);
  actionGroup->addAction(action);
  connect(action, SIGNAL(triggered(bool)), this, SLOT(setAnimationMode()));
  subMenu->addAction(action);
  menu->addMenu(subMenu);

  action = new QAction(tr("Grid"), this);
  action->setCheckable(true);
  action->setChecked(true);
  connect(action, SIGNAL(triggered(bool)), this, SLOT(setShowGrid(bool)));
  menu->addAction(action);

  action = new QAction(tr("Antialiasing"), this);
  action->setCheckable(true);
  action->setChecked(true);
  connect(action, SIGNAL(triggered(bool)), this, SLOT(setUseAntialiasing(bool)));
  menu->addAction(action);

  menu = new QMenu(tr("Help"));
  action = new QAction(QIcon::fromTheme("help-contents"), tr("Help"), this);
  //connect(action, SIGNAL(triggered(bool)), this, SLOT(close()));
  menu->addAction(action);
  menu->addMenu(createLanguageMenu());
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

void MainWindow::setShowGrid(bool isVisible)
{ m_functionWgt->setShowGrid(isVisible); }

void MainWindow::setUseAntialiasing(bool useAntialiasing)
{ m_functionWgt->setUseAntialiasing(useAntialiasing); }

void MainWindow::setAnimationMode()
{
  QAction* action = qobject_cast<QAction*>(sender());
  if (!action)
  { return; }

  switch (action->data().toInt())
  {
    case 0: m_functionWgt->setAnimationMode(1, true); break;
    case 1: m_functionWgt->setAnimationMode(1, false); break;
    case 2: m_functionWgt->setAnimationMode(0, false); break;
  }
}

void MainWindow::splitterDoubleClicked()
{ m_splitter->setWidgetCollapsed(0, !m_splitter->isWidgetCollapsed(0)); }

QMenu* MainWindow::createLanguageMenu()
{
  QMenu* menu = new QMenu(tr("Language"));

  QActionGroup* langGroup = new QActionGroup(this);
  langGroup->setExclusive(true);

  connect(langGroup, SIGNAL(triggered(QAction *)), this, SLOT(languageChanged(QAction *)));

  // format systems language
  QString defaultLocale;
  if (m_currLang.isEmpty())
  {
    defaultLocale = QLocale::system().name();       // e.g. "de_DE"
    defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "de"
  }
  else { defaultLocale = m_currLang; }

  QString langPath = QApplication::applicationDirPath();
  langPath.append("/po");
  QDir dir(langPath);
  QStringList fileNames = dir.entryList(QStringList("trans_*.qm"));

  for (int i = 0; i < fileNames.size(); ++i)
  {
    QString locale;
    locale = fileNames[i];
    locale.truncate(locale.lastIndexOf('.'));
    locale.remove(0, locale.indexOf('_') + 1);

    QString lang = QLocale::languageToString(QLocale(locale).language());
    QIcon ico(QString("%1/%2.png").arg(langPath).arg(locale));

    QAction *action = new QAction(ico, lang, this);
    action->setCheckable(true);
    action->setData(locale);

    menu->addAction(action);
    langGroup->addAction(action);

    if (defaultLocale == locale)
    { action->setChecked(true); }
  }

  return menu;
}

void MainWindow::changeEvent(QEvent* event)
{
  if(event)
  {
    switch(event->type())
    {
      case QEvent::LanguageChange:
      {
        initMenu();
        //translateFunctions();
        break;
      }
      case QEvent::LocaleChange:
      {
        QString locale = QLocale::system().name();
        locale.truncate(locale.lastIndexOf('_'));
        loadLanguage(locale);
        break;
      }
      default: break;
    }
  }

  QMainWindow::changeEvent(event);
}

void MainWindow::languageChanged(QAction* action)
{
  if (action)
  { loadLanguage(action->data().toString()); }
}

void MainWindow::switchTranslator(QTranslator& translator, const QString& filename)
{
  qApp->removeTranslator(&translator);

  if (translator.load(filename))
  {  qApp->installTranslator(&translator); }
}

void MainWindow::loadLanguage(const QString& rLanguage)
{
  if(m_currLang != rLanguage)
  {
    m_currLang = rLanguage;
    QLocale locale = QLocale(m_currLang);
    QLocale::setDefault(locale);
    QString languageName = QLocale::languageToString(locale.language());
    switchTranslator(m_translator, QString("trans_%1.qm").arg(rLanguage));
    switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(rLanguage));
  }
}