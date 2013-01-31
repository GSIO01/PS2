/*
 * (C) Copyright 2012-2013 QCurve Team
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser General Public License
 * (LGPL) version 2.1 which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl-2.1.html
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 */

#include "mainwindow.h"

#include <QtCore/QTimer>
#include <QtCore/QDir>
#include <QtCore/QSettings>

#include <QtGui/QApplication>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QActionGroup>

#include "Widgets/Splitter"
#include "Models/FunctionItemModel"
#include "functionwidget.h"

#include "Functions/Functions"

#include "Export/EPSExporter"
#include "Export/ExportDialog"

#include "aboutdialog.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
  loadLanguage(preferredLanguage());

  setWindowTitle(tr("Parametric Curve Viewer"));
  //setWindowIcon(QIcon("hicolor/32x32/app/qcurve.png"));

  initMenu();
  initComponents();

  QTimer::singleShot(0, this, SLOT(init()));
}

MainWindow::~MainWindow()
{ }

void MainWindow::init()
{
  initFunctions();

  m_functionWgt->setFunction(Ellipse());
  m_treeView->expandAll();
  m_treeView->setCurrentIndex(m_functionItemModel->index(2, 0).child(1, 0)); //select 'ellipse'

  connect(m_splitter, SIGNAL(mouseDoubleClicked()), this, SLOT(splitterDoubleClicked()));
  connect(m_treeView, SIGNAL(activated(QModelIndex)), this, SLOT(itemActivated(QModelIndex)));
}

void MainWindow::itemActivated(const QModelIndex& idx)
{
  Function* func = m_functionItemModel->functionAt(idx);

  if (func)
  { m_functionWgt->setFunction(*func); }
}

void MainWindow::initFunctions()
{
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
  m_functionItemModel->addFunction(Clothoids(1), tr("Spirals"));

  m_functionItemModel->addCategory(tr("Other curves"));
  m_functionItemModel->addFunction(Catenary(), tr("Other curves"));
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
  QAction* action = new QAction(QIcon::fromTheme("document-export"), tr("Export as EPS..."), this);
  connect(action, SIGNAL(triggered(bool)), this, SLOT(exportAsEPS()));
  subMenu->addAction(action);
  menu->addMenu(subMenu);
  menu->addSeparator();

  action = new QAction(QIcon::fromTheme("window-close"), tr("Close"), this);
  connect(action, SIGNAL(triggered(bool)), this, SLOT(close()));
  menu->addAction(action);
  menubar->addMenu(menu);

  //menu = new QMenu(tr("Edit"));
  //menubar->addMenu(menu);

  menu = new QMenu(tr("View"));
  menubar->addMenu(menu);

  subMenu = new QMenu(tr("Projection"));
  QActionGroup* actionGroup = new QActionGroup(this);
  action = new QAction(tr("Paralell"), this);
  action->setCheckable(true);
  action->setChecked(true);
  actionGroup->addAction(action);
  subMenu->addAction(action);
  action = new QAction(tr("Perspective"), this);
  action->setCheckable(true);
  action->setEnabled(false);
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
  action->setChecked(false);
  connect(action, SIGNAL(triggered(bool)), this, SLOT(setUseAntialiasing(bool)));
  menu->addAction(action);

  menu = new QMenu(tr("Help"));
  action = new QAction(QIcon::fromTheme("help-contents"), tr("Help"), this);
  //connect(action, SIGNAL(triggered(bool)), this, SLOT(close()));
  menu->addAction(action);
  menu->addMenu(createLanguageMenu());
  menu->addSeparator();
  action = new QAction(QIcon::fromTheme("help-about"), tr("About"), this);
  connect(action, SIGNAL(triggered(bool)), this, SLOT(showAbout()));
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

void MainWindow::exportAsEPS()
{
  ExportDialog dlg;
  if (dlg.exec())
  {
    EpsExporter exporter(dlg.selectedFiles().at(0), dlg.author());
    exporter.setShowGrid(dlg.showGrid());
    exporter.setShowLabels(dlg.showLabels());
    exporter.setShowHelperItems(dlg.showHelperItems());
    exporter.exportToFile(m_functionWgt->function());
  }
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
    case 0: m_functionWgt->setAnimationMode(7, true); break;  //Repeat
    case 1: m_functionWgt->setAnimationMode(7, false); break; //Once
    case 2: m_functionWgt->setAnimationMode(0, false); break; //None
  }
}

void MainWindow::showAbout()
{
  AboutDialog dlg;
  dlg.exec();
}

void MainWindow::splitterDoubleClicked()
{ m_splitter->setWidgetCollapsed(0, !m_splitter->isWidgetCollapsed(0)); }

QMenu* MainWindow::createLanguageMenu()
{
  QMenu* menu = new QMenu(tr("Language"));

  QActionGroup* langGroup = new QActionGroup(this);
  langGroup->setExclusive(true);

  connect(langGroup, SIGNAL(triggered(QAction *)), this, SLOT(languageChanged(QAction *)));

  if (m_currLang.isEmpty())
  { m_currLang = preferredLanguage(); }

  QString langPath = QApplication::applicationDirPath() + "/po";
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

    if (m_currLang == locale)
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
    switchTranslator(m_translator, QString("po/trans_%1.qm").arg(rLanguage));
    switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(rLanguage));
  }
}

QString MainWindow::preferredLanguage() const
{
  QString lang;
  //If the app runs under KDE try to use it's language settings
  if (!qgetenv("KDE_FULL_SESSION").isEmpty())
  {
    QSettings settings(QDir::homePath() +
      QLatin1String("/.kde4/share/config/kdeglobals"), QSettings::IniFormat);

    lang = settings.value(QLatin1String("Locale/Language"), QString()).toString();

    if (!lang.isEmpty())
    { return lang.left(2); }
  }

  lang = QLocale::system().name();
  lang = lang.toLower();
  lang = lang.left(2);

  /* Window XP Prof MUI Multiuser && Multilanguage == stay
   * only "c" language && user setting setenv !!! */
  if (lang == "c")
  {
    QString languser = getenv("LANG");
    languser = languser.toLower();
    if (languser.size() > 2 && languser.contains("_"))
    { lang = languser.left(2); }
  }

  return lang;
}
