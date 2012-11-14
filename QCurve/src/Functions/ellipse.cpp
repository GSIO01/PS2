#include "ellipse.h"

#include <QtCore/QDebug>

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Ellipse::Ellipse(double a, double b, double x0, double y0)
{ 
  m_param = Parameter(0, 2 * PI, "t");
  
  if (a != b)
  {
    m_name = "Ellipse";
    setVariable("a", a);
    setVariable("b", b);
  }
  else 
  { 
    m_name = "Circle";
    setVariable("r", a);
  }
  
  m_points.append(Point(a, y0, "a"));
  m_points.append(Point(-a, y0, "-a"));
  m_points.append(Point(x0, -b, "b"));
  m_points.append(Point(x0, b, "-b"));
    
  m_dimension = QRectF(-a, -b, 2*a, 2*b);
  
  setVariable("x0", x0);
  setVariable("y0", y0);
}

Ellipse::Ellipse(const Ellipse& other)
{ *this = other; }

Function* Ellipse::clone() const
{ return new Ellipse(*this); }

QString Ellipse::toParametricFormula() const
{
  static QString genFormula = QString("<math>x(t)=<mi>a</mi>*cos(t), y(t)=<mi>b</mi>*sin(t)</math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}

double Ellipse::calculateX(double t) const
{
  double val = (m_name == "Circle") ? getVariable("r") : getVariable("a");

  double result = getVariable("x0") + val * qCos(t);
  
  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
} 

double Ellipse::calculateY(double t) const
{
  double val = (m_name == "Circle") ? getVariable("r") : getVariable("b");
  
  double result = getVariable("y0") + val * qSin(t);
  
  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
}

double Ellipse::calculateZ(double t) const
{ return 0; }