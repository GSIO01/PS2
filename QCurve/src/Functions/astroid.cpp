#include "astroid.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Astroid::Astroid(double a, double x0, double y0)
{
  m_name = "Astroid";
  m_param = Parameter(0, 2 * PI, "t");
  
  if (a > 0) { setVariable("a", a); }
  else { setVariable("a", 1.0); }
  
  setVariable("x0", x0);
  setVariable("y0", y0);
}

Astroid::Astroid(const Astroid& other)
{ *this = other; }

Function* Astroid::clone() const
{ return new Astroid(*this); }

QString Astroid::toParametricFormula() const
{
  static QString genFormula = QString("<math></math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}

double Astroid::calculateX(double t) const
{
  double result = getVariable("x0") + (getVariable("a") * pow(cos(t), 3));
  
  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
}

double Astroid::calculateY(double t) const
{
  double result = getVariable("y0") + (getVariable("a") * pow(sin(t), 3));
  
  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
}

double Astroid::calculateZ(double t) const
{ return 0; }