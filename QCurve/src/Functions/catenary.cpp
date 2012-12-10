 
#include "catenary.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Catenary::Catenary(double a, double x0, double y0)
{
  m_name = "Catenary";
  m_param = Parameter(-1, 1, "t");
    
  setVariable("a", a);
}

Catenary::Catenary(const Catenary& other)
{ *this = other; }

Function* Catenary::clone() const
{ return new Catenary(*this); }


QString Catenary::toParametricFormula() const
{
  static QString genFormula = QString("<math></math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}
    
double Catenary::calculateX(double t) const
{
  double result = getVariable("x0") + t;
    
  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
}
 
double Catenary::calculateY(double t) const
{
  double result = getVariable("y0") + getVariable("a") * cosh(t / getVariable("a"));
    
  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
}

double Catenary::calculateZ(double t) const
{ return 0; }
