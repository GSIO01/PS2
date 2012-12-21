#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QModelIndex>

#include <QtGui/QMainWindow>
#include <QtGui/QTreeView>

class Splitter;
class FunctionWidget;
class FunctionItemModel;
class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private slots:
    void init();
    void splitterDoubleClicked();
    void itemActivated(const QModelIndex& idx);

  private:
    void initMenu();
    void initComponents();

    Splitter* m_splitter;
    FunctionWidget* m_functionWgt;
    QTreeView* m_treeView;

    FunctionItemModel* m_functionItemModel;
};

#endif