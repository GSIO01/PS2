#include "function.h"

Function::Function()
  : m_dimension(QRectF(0, 0, 0, 0))
{
  Variable var("x0", 0);
  var.setColor(QColor(0, 0, 255));
  var.setFormula("<math><mrow><msub><mi color=\"#0000FF\">x</mi><mr color=\"#00F\">0</mr></msub></mrow></math>");
  var.setDescription("Moves the function on the x-axis.");
  setVariable(var);

  var = Variable("y0", 0);
  var.setColor(QColor(0, 255, 0));
  var.setFormula("<math><mrow><msub><mi color=\"#00FF00\">y</mi><mr color=\"#00FF00\">0</mr></msub></mrow></math>");
  var.setDescription("Moves the function on the y-axis.");
  setVariable(var);
}

Function::~Function()
{ }

Parameter& Function::parameter() const
{ return const_cast<Parameter&>(m_param); }

void Function::setParameter(const Parameter& param)
{ m_param = param; }

QList<Variable> Function::variables() const
{ return m_variables; }

void Function::updatePoints(const QString& var, double value)
{ }

double Function::getVariable(const QString& name) const
{
  foreach(const Variable& var, m_variables)
  {
    if (var.name() == name)
    { return var.value(); }
  }

  return 0;
}

void Function::setVariable(const QString& name, double value)
{
  Variable tmp(name, value);
  if (m_variables.contains(tmp)) //TODO
  {
    int idx = m_variables.indexOf(tmp);
    Variable c = m_variables.takeAt(idx);
    c.setValue(value);
    m_variables.insert(idx, c);
  }
  else { m_variables.append(Variable(name, value)); }

  updatePoints(name, value);
  initDimension();
}

void Function::setVariable(const Variable& variable)
{
  if (m_variables.contains(variable))
  {
    int idx = m_variables.indexOf(variable);
    m_variables.removeAt(idx);
    m_variables.insert(idx, variable);
  }
  else { m_variables.append(variable); }

  updatePoints(variable.name(), variable.value());
  initDimension();
}

void Function::setPoint(const Point& point)
{
  if (m_points.contains(point))
  { m_points.removeOne(point); }

  m_points.append(point);
}

QList<Point> Function::points() const
{ return m_points; }

const QRectF& Function::dimension() const
{ return m_dimension; }
