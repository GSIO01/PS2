#include "ellipse.h"

#include <QtCore/QDebug>

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Ellipse::Ellipse(double r)
{
  m_name = "Ellipse";
  m_param = Parameter(0, 2 * PI, "t");
  
  setVariable("R", r);
  
}

Ellipse::Ellipse(double a, double b)
{ 
  m_name = "Ellipse";
  m_param = Parameter(0, 2 * PI, "t");
  
  if (a != b)
  { 
    setVariable("a", a);
    setVariable("b", b);
  }
  else { setVariable("R", a); }
}

Ellipse::Ellipse(const Ellipse& other)
{ *this = other; }

Function* Ellipse::clone() const
{ return new Ellipse(*this); }

QString Ellipse::toFormula() const
{
  static QString genFormula = QString("<math>x(t)=<mi>a</mi>*cos(t), y(t)=<mi>b</mi>*sin(t)</math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}

double Ellipse::calculateX(double t) const
{
  double result = m_variables.at(0).value() * qCos(t);
  
  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
} 

double Ellipse::calculateY(double t) const
{ 
  double result = m_variables.at(1).value() * qSin(t);
  
  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
}