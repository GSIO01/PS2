#include "function.h"

Function::Function()
  : m_dimension(QRectF(0, 0, 0, 0))
{ }

Function::~Function()
{ }

Parameter& Function::parameter() const
{ return const_cast<Parameter&>(m_param); }

void Function::setParameter(const Parameter& param)
{ m_param = param; }

QList<Variable> Function::variables() const
{ return m_variables; }

void Function::setVariable(const QString& name, double value)
{
  Variable tmp(name, value);
  if (m_variables.contains(tmp)) //TODO 
  {
    Variable c = m_variables.takeAt(m_variables.indexOf(tmp));
    c.setValue(value);
    m_variables.append(c);
  }
  else { m_variables.append(Variable(name, value)); }
}

void Function::setVariable(const Variable& variable)
{
  if (m_variables.contains(variable))
  {
    m_variables.removeAt(m_variables.indexOf(variable));
    m_variables.append(variable);
  }
  else { m_variables.append(variable); }
}

QList<Point> Function::points() const
{ return m_points; }

const QRectF& Function::dimension() const
{ return m_dimension; }