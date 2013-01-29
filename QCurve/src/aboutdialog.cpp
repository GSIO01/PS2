#include "aboutdialog.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent)
{
  initComponents();
  m_icon = QIcon("QCurve.svg");

  setWindowIcon(m_icon);
}

AboutDialog::~AboutDialog()
{ }

void AboutDialog::initComponents()
{
  QVBoxLayout* layout = new QVBoxLayout(this);

  QHBoxLayout* lyt = new QHBoxLayout();
  QLabel* icon = new QLabel("<img src=\"QCurve.svg\" width=\"64\" height=\"64\"> </img>");

  QVBoxLayout* subLyt = new QVBoxLayout();
  QLabel* progName = new QLabel(QString("<b>%1</b>").arg(tr("QCurve")));
  QLabel* versionName = new QLabel("Version 1.0");
  subLyt->addWidget(progName);
  subLyt->addWidget(versionName);

  lyt->addWidget(icon);
  lyt->addLayout(subLyt);

  QWidget* about = new QWidget();
  subLyt = new  QVBoxLayout(about);
  subLyt->addWidget(new QLabel(tr("QCurve - Parametric curve viewer")));
  subLyt->addWidget(new QLabel(tr("(c) 2012-2013 QCurve team")));
  subLyt->addWidget(new QLabel(QString("<a href=\"http://opensource.org/licenses/mit-license.php\">%1</a>")
    .arg(tr("License: MIT License"))));

  QWidget* authors = new QWidget();

  m_tabWgt = new QTabWidget();
  m_tabWgt->addTab(about, tr("About"));
  m_tabWgt->addTab(authors, tr("Authors"));

  layout->addLayout(lyt);
  layout->addWidget(m_tabWgt);
}