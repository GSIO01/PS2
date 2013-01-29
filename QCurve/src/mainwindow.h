#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QModelIndex>
#include <QtCore/QString>
#include <QtCore/QTranslator>
#include <QtCore/QEvent>

#include <QtGui/QMainWindow>
#include <QtGui/QTreeView>
#include <QtGui/QMenu>

class Splitter;
class FunctionWidget;
class FunctionItemModel;
class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

  protected:
    virtual void changeEvent(QEvent*);

  private slots:
    void init();
    void splitterDoubleClicked();
    void itemActivated(const QModelIndex& idx);

    void setShowGrid(bool isVisible);
    void setUseAntialiasing(bool useAntialiasing);
    void setAnimationMode();

    void exportAsEPS();

    void languageChanged(QAction* action);
    void switchTranslator(QTranslator& translator, const QString& filename);
    void showAbout();

  private:
    void initMenu();
    void initComponents();
    void initFunctions();

    QMenu* createLanguageMenu();
    void loadLanguage(const QString& rLanguage);
    QString preferredLanguage() const;

    Splitter* m_splitter;
    FunctionWidget* m_functionWgt;
    QTreeView* m_treeView;

    FunctionItemModel* m_functionItemModel;

    QTranslator m_translator;
    QTranslator m_translatorQt;
    QString m_currLang;
};

#endif
