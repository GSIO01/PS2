#include "logspiral.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

LogarithmicSpiral::LogarithmicSpiral(double a, double x0, double y0)
{
  m_name = "Logarithmic Spiral";
  m_param = Parameter(0, 4 * PI, "t");
    
  setVariable("a", a);
  setVariable("x0", x0);
  setVariable("y0", y0);
}

LogarithmicSpiral::LogarithmicSpiral(const LogarithmicSpiral& other)
{ *this = other; }

Function* LogarithmicSpiral::clone() const
{ return new LogarithmicSpiral(*this); }


QString LogarithmicSpiral::toParametricFormula() const
{
  static QString genFormula = QString("<math></math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}
    
double LogarithmicSpiral::calculateX(double t) const
{
  double result = getVariable("x0") + pow(getVariable("a"), t) * cos(t);
    
  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
}
 
double LogarithmicSpiral::calculateY(double t) const
{
  double result = getVariable("y0") + pow(getVariable("a"), t) * sin(t);
    
  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
}

double LogarithmicSpiral::calculateZ(double t) const
{ return 0; } 
