#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QtGui/QTabWidget>
#include <QtGui/QLabel>
#include <QtGui/QIcon>
#include <QtGui/QDialog>

class AboutDialog : public QDialog
{
  Q_OBJECT
  public:
    AboutDialog(QWidget* parent = 0);
    ~AboutDialog();

  private:
    void initComponents();

    QTabWidget* m_tabWgt;
    QLabel* m_progName;
    QLabel* m_progVersion;
    QLabel* m_description;

    QIcon m_icon;
};

#endif
