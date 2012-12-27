#include "variableedit.h"

#include <QtGui/QKeyEvent>
#include <QtGui/QHBoxLayout>

#include "Widgets/QtMmlWidget"

VariableEdit::VariableEdit(const Variable& var, QWidget* parent)
  : m_variable(var.name())
{
  m_variableLbl = new QtMmlWidget();
  m_value = new QDoubleSpinBox();

  m_variableLbl->setContent(var.formula());
  m_value->setKeyboardTracking(false);

  if (!var.interval().lowerEndIsClosed())
  { m_value->setMinimum(var.interval().lowerEnd() + 0.01); }
  else { m_value->setMinimum(var.interval().lowerEnd()); }
  if (!var.interval().upperEndIsClosed())
  { m_value->setMaximum(var.interval().upperEnd() - 0.01); }
  else { m_value->setMaximum(var.interval().upperEnd()); }
  m_value->setValue(var.value());

  QHBoxLayout* lyt = new QHBoxLayout(this);
  lyt->addWidget(m_variableLbl);
  lyt->addWidget(m_value);

  //Tooltip = name + description + domain
  QString toolTip = QString("<b>%2</b><br/>%1<br/>%2 %3 %4").arg(var.description()).
    arg(var.name()).arg(QChar(0x2208)).arg(var.interval().toString());
  setToolTip(toolTip);

  connect(m_value, SIGNAL(valueChanged(double)), this, SLOT(valueChanged(double)));
}

void VariableEdit::setVariable(const Variable& var)
{
  m_variable = var.name();

  m_variableLbl->setContent(var.formula());

  if (!var.interval().lowerEndIsClosed())
  { m_value->setMinimum(var.interval().lowerEnd() + 0.01); }
  else { m_value->setMinimum(var.interval().lowerEnd()); }
  if (!var.interval().upperEndIsClosed())
  { m_value->setMaximum(var.interval().lowerEnd() - 0.01); }
  else { m_value->setMaximum(var.interval().upperEnd()); }

  m_value->setValue(var.value());
}

void VariableEdit::valueChanged(double value)
{ emit valueChanged(m_variable, value); }
