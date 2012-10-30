#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow> 
#include <QtGui/QTreeView>

class Splitter;
class FunctionWidget;
class MainWindow : public QMainWindow 
{
  Q_OBJECT
  
  public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();
    
  private slots:
    void splitterDoubleClicked();
    
  private:
    void initMenu();
    void initComponents();
    
    Splitter* m_splitter;
    FunctionWidget* m_functionWgt;
    QTreeView* m_treeView;
};

#endif