#include "clothoids.h"

#include <math.h>

Clothoids::Clothoids(double a,double n, double x0, double y0)
{
  m_name = "Clothoids";
  m_param = Parameter(-20, 20, "t");

  setVariable("x0", x0);
  setVariable("y0", y0);

  Variable var("a");
  var.interval().setLowerEnd(0);
  var.setValue(a);
  setVariable(var);

  var = Variable("n");
  var.interval().setLowerEnd(0);
  var.setValue(n);
  setVariable(var);
}

Clothoids::Clothoids(const Clothoids& other)
{ *this = other; }

Function* Clothoids::clone() const
{ return new Clothoids(*this); }

QString Clothoids::toParametricFormula() const
{
  static QString genFormula = QString("<math>x(t)=, y(t)=</math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }

  return curFormula;
}

double Clothoids::calculateX(double t) const
{
    int h;
    int i;
    double r1,r2,r3;
    double result=0;
    h = (t/getVariable("n"));

   for(i=0;i<=getVariable("n");i++)
    {
        r1 = pow(((i+0.5)*(t/getVariable("n"))),2);
        r2 = 2*getVariable("a");
        r3 = pow(r2,2);
        result+= cos(r1/r3);
    }
    result*=(t/getVariable("n"));
    result+=getVariable("x0");

    if (result < m_dimension.left())
    { m_dimension.setLeft(result); }
    else if (result > m_dimension.right())
    { m_dimension.setRight(result); }

  return result;
}

double Clothoids::calculateY(double t) const
{
    int n = 100;
    int h = t/getVariable("n");
    int i;
    double r1,r2,r3;
    double result=0;

    for(i=0;i<=getVariable("n");i++)
    {
        r1 = pow(((i+0.5)*(t/getVariable("n"))),2);
        r3 = 2*getVariable("a");
        r2 = pow(r3,2);
        result+= sin(r1/r2);
    }
    result*=(t/getVariable("n"));
    result+=getVariable("y0");

    if (result < m_dimension.bottom())
    { m_dimension.setBottom(result); }
    else if (result > m_dimension.top())
    { m_dimension.setTop(result); }

  return result;
}

double Clothoids::calculateZ(double t) const
{ return 0; }
