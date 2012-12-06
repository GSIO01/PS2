#include "archspiral.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

ArchimedeanSpiral::ArchimedeanSpiral(double x0, double y0)
{
  m_name = "Archimedean Spiral";
  m_param = Parameter(0, 4 * PI, "t");
    
  setVariable("x0", x0);
  setVariable("y0", y0);
}

ArchimedeanSpiral::ArchimedeanSpiral(const ArchimedeanSpiral& other)
{ *this = other; }

Function* ArchimedeanSpiral::clone() const
{ return new ArchimedeanSpiral(*this); }


QString ArchimedeanSpiral::toParametricFormula() const
{
  static QString genFormula = QString("<math></math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}
    
double ArchimedeanSpiral::calculateX(double t) const
{
  double result = getVariable("x0") + (t * cos(t));
    
  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
}
 
double ArchimedeanSpiral::calculateY(double t) const
{
  double result = getVariable("y0") + (t * sin(t));
    
  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
}

double ArchimedeanSpiral::calculateZ(double t) const
{ return 0; } 
