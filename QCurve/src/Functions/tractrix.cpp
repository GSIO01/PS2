#include "tractrix.h"

#include <QtCore/qmath.h> //TODO

#include <limits>

#define PI 3.141592653589793

Tractrix::Tractrix(double a, double x0, double y0)
{
  m_name = "Tractrix";
  m_param = Parameter(0, PI/1.1, "t");//TODO
    
  setVariable("a", a);
  setVariable("x0", x0);
  setVariable("y0", y0);
}

Tractrix::Tractrix(const Tractrix& other)
{ *this = other; }

Function* Tractrix::clone() const
{ return new Tractrix(*this); }


QString Tractrix::toParametricFormula() const
{
  static QString genFormula = QString("<math></math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}
    
double Tractrix::calculateX(double t) const
{
  double result = getVariable("x0") + (-getVariable("a") * cos(t) - getVariable("a") * log(tan(t / 2)));
    
  if (result > std::numeric_limits<qreal>::max()) { return m_dimension.right();  }
  else if (result < -std::numeric_limits<qreal>::max()) { return m_dimension.left(); }
  
  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
}
 
double Tractrix::calculateY(double t) const
{
  double result = getVariable("y0") + getVariable("a") * sin(t);
  
  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
}

double Tractrix::calculateZ(double t) const
{ return 0; } 
