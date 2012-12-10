#include "helix.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Helix::Helix(double r, double h, double x0, double y0, double z0)
{
  m_name = "Helix";
  m_param = Parameter(-PI, PI, "t"); //TODO

  setVariable("x0", x0);
  setVariable("y0", y0);

  Variable var("z0", z0);
  var.setFormula("<math><mrow><msub><mi>z</mi><mr>0</mr></msub></mrow></math>");
  var.setDescription("Moves the function on the z-axis");
  setVariable(var);

  var = Variable("r");
  var.interval().setLowerEnd(0);
  var.setValue(r);
  setVariable(var);

  var = Variable("h");
  var.interval().setLowerEnd(0);
  var.setValue(h);
  setVariable(var);
}

Helix::Helix(const Helix& other)
{ *this = other; }

Function* Helix::clone() const
{ return new Helix(*this); }


QString Helix::toParametricFormula() const
{
  static QString genFormula = QString("<math></math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}
    
double Helix::calculateX(double t) const
{
  double result = getVariable("x0") + getVariable("r") * cos(t);
    
  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
}
 
double Helix::calculateY(double t) const
{
  double result = getVariable("y0") + getVariable("r") * sin(t);
    
  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
}

double Helix::calculateZ(double t) const
{ 
  double result = getVariable("z0") + getVariable("h") * t;
  
  return result; 
} 
