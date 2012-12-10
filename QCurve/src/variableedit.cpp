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

  setToolTip(var.description());
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

void VariableEdit::focusOutEvent(QFocusEvent* event)
{ emit valueChanged(m_variable, m_value->value()); }

void VariableEdit::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Enter  || event->key() == Qt::Key_Return)
  { emit valueChanged(m_variable, m_value->value()); }
}
