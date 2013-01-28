#include "exportdialog.h"

#include <QtGui/QGridLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>

ExportDialog::ExportDialog(QWidget* parent) : QFileDialog(parent)
{
  setFileMode(QFileDialog::AnyFile);
  setNameFilter(tr("Text (*.eps, *.epsf, *.epsi)"));
  setAcceptMode(QFileDialog::AcceptSave);
  setOption(QFileDialog::HideNameFilterDetails, false);
  setWindowTitle(tr("Export function as EPS..."));

  extendLayout();

  m_author->setText(tr("QCurve"));
  m_helperItems->setChecked(true);
}

ExportDialog::~ExportDialog()
{ }

void ExportDialog::extendLayout()
{
  QGroupBox* grpBox = new QGroupBox(tr("Settings"));

  m_author = new QLineEdit();
  m_helperItems = new QCheckBox(tr("Show additonal items (like points or lines)"));
  m_grid = new QCheckBox(tr("Show grid"));
  m_labels = new QCheckBox(tr("Show labels"));

  QVBoxLayout* subLyt = new QVBoxLayout(grpBox);
  subLyt->addWidget(m_helperItems);
  subLyt->addWidget(m_grid);
  subLyt->addWidget(m_labels);

  QHBoxLayout* hbox = new QHBoxLayout();
  hbox->addWidget(new QLabel(tr("Author")));
  hbox->addWidget(m_author);
  subLyt->addLayout(hbox);

  QGridLayout* lyt = (QGridLayout*)layout();
  lyt->addWidget(grpBox, 4, 0, 1, 4);
}