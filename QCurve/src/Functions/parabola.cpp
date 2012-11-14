#include "parabola.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Parabola::Parabola(double p, double x0, double y0)
{
  m_name = "Parabola";
  m_param = Parameter(-PI, PI, "t");
  
  setVariable("p", p);
  setVariable("x0", x0);
  setVariable("y0", y0);
}

Parabola::Parabola(const Parabola& other)
{ *this = other; }

Function* Parabola::clone() const
{ return new Parabola(*this); }

QString Parabola::toParametricFormula() const
{
  static QString genFormula = QString("<math></math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}
    
double Parabola::calculateX(double t) const
{
  double result = getVariable("x0") + t * t;
  
   if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
}

double Parabola::calculateY(double t) const
{
  double result = getVariable("y0") + sqrt(2 * getVariable("p")) * t;
  
  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
}

double Parabola::calculateZ(double t) const
{ return 0; }