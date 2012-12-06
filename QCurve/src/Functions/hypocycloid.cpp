#include "hypocycloid.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Hypocycloid::Hypocycloid( double a, double c, double x0, double y0)
{
  m_name = "Hypocycloid";
  m_param = Parameter(0, 2 * PI, "t");
    
  setVariable("a", a);
  setVariable("c", c);
  setVariable("x0", x0);
  setVariable("y0", y0);
}

Hypocycloid::Hypocycloid(const Hypocycloid& other)
{ *this = other; }

Function* Hypocycloid::clone() const
{ return new Hypocycloid(*this); }


QString Hypocycloid::toParametricFormula() const
{
  static QString genFormula = QString("<math></math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}
    
double Hypocycloid::calculateX(double t) const
{
  double result = getVariable("x0") + (0.75 * getVariable("a") * cos(t) + getVariable("c") * cos(3*t));
    
  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
}
 
double Hypocycloid::calculateY(double t) const
{
  double result = getVariable("y0") + (0.75 * getVariable("a") * sin(t) - getVariable("c") * sin(3*t));
    
  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
}

double Hypocycloid::calculateZ(double t) const
{ return 0; } 
