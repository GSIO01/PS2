#include "cycloid.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Cycloid::Cycloid(double x0, double y0, double r, double m)
{
  m_name = "Cycloid";
  m_param = Parameter(-25, 25, "t");
    
  setVariable("r", r);
  setVariable("m", m);
  setVariable("x0", x0);
  setVariable("y0", y0);
}

Cycloid::Cycloid(const Cycloid& other)
{ *this = other; }

Function* Cycloid::clone() const
{ return new Cycloid(*this); }


QString Cycloid::toParametricFormula() const
{
  static QString genFormula = QString("<math></math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}
    
double Cycloid::calculateX(double t) const
{
  double result = getVariable("x0") + getVariable("r") * (t - getVariable("m") * sin(t));
    
  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
}
 
double Cycloid::calculateY(double t) const
{
  double result = getVariable("y0") + getVariable("r") * (1 - getVariable("m") * cos(t)); //FIXME t or 1?
    
  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
}

double Cycloid::calculateZ(double t) const
{ return 0; }