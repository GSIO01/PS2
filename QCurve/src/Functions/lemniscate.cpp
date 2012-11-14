#include "lemniscate.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Lemniscate::Lemniscate(double a, double x0, double y0)
{
  m_name = "Lemniscate";
  m_param = Parameter(0, 2 * PI, "t");
    
  setVariable("a", a);
  setVariable("x0", x0);
  setVariable("y0", y0);
}

Lemniscate::Lemniscate(const Lemniscate& other)
{ *this = other; }

Function* Lemniscate::clone() const
{ return new Lemniscate(*this); }


QString Lemniscate::toParametricFormula() const
{
  static QString genFormula = QString("<math></math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}
    
double Lemniscate::calculateX(double t) const
{
  double result = getVariable("x0") + getVariable("a") * sqrt(cos(2 * t)) * cos(t);
    
  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
}
 
double Lemniscate::calculateY(double t) const
{
  double result = getVariable("y0") + getVariable("a") * sqrt(cos(2 * t)) * sin(t);
    
  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
}

double Lemniscate::calculateZ(double t) const
{ return 0; }