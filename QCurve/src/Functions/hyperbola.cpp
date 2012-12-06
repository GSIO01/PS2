#include "hyperbola.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Hyperbola::Hyperbola(double a, double b, double x0, double y0)
{
  m_name = "Hyperbola";
  m_param = Parameter(-PI, PI, "t");

  setVariable("a", a);
  setVariable("b", b);
  setVariable("x0", x0);
  setVariable("y0", y0);
}

Hyperbola::Hyperbola(const Hyperbola& other)
{ *this = other; }

Function* Hyperbola::clone() const
{ return new Hyperbola(*this); }

QString Hyperbola::toParametricFormula() const
{
  static QString genFormula = QString("<math></math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}

double Hyperbola::calculateX(double t) const
{
  double result = getVariable("x0") + getVariable("a") * cosh(t);
  
  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
}

double Hyperbola::calculateY(double t) const
{
  double result = getVariable("y0") + getVariable("b") * sinh(t);
  
  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
}

double Hyperbola::calculateZ(double t) const
{ return 0; }