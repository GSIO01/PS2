#include "strophoid.h"

Strophoid::Strophoid(double a, double x0, double y0)
{
  m_name = "Strophoid";
  m_param = Parameter(-2, 2, "t");
  
  setVariable("a", a);
  setVariable("x0", x0);
  setVariable("y0", y0);
}

Strophoid::Strophoid(const Strophoid& other)
{ *this = other; }

Function* Strophoid::clone() const
{ return new Strophoid(*this); }

QString Strophoid::toParametricFormula() const
{
  static QString genFormula = QString("<math></math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}
    
double Strophoid::calculateX(double t) const
{
  double result = getVariable("x0") + ((getVariable("a") * ((t*t)-1))/(1+(t*t)));
  
  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
}

double Strophoid::calculateY(double t) const
{
  double result = getVariable("y0") + ((getVariable("a") * t * ((t*t)-1))/(1+(t*t)));
  
  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
}

double Strophoid::calculateZ(double t) const
{ return 0; }