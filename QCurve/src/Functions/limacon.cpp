#include "limacon.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Limacon::Limacon(double a, double b, double x0, double y0)
{
  m_name = "Limacon";
  m_param = Parameter(0, 2 * PI, "t");
  
  setVariable("a", a);
  setVariable("b", b);
  setVariable("x0", x0);
  setVariable("y0", y0);
}

Limacon::Limacon(const Limacon& other)
{ *this = other; }

Function* Limacon::clone() const
{ return new Limacon(*this); }

QString Limacon::toParametricFormula() const
{
  static QString genFormula = QString("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"> <semantics> <mrow> <mi>x</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow> <mi/> <mo stretchy=\"false\">=</mo> <mi/> </mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mn>2a</mn> <mi>cos</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mo stretchy=\"false\">+</mo> <mi>t</mi> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mi>cos</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mi/> <mi>,</mi> <mi/> <mi>y</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow> <mi/> <mo stretchy=\"false\">=</mo> <mi/> </mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mn>2a</mn> <mi>cos</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mo stretchy=\"false\">+</mo> <mi>b</mi> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mi>sin</mi> <mrow> <mo stretchy=\"false\">(</mo><mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mi/> <mi>,</mi> <mi/> <mi>t</mi> <mo stretchy=\"false\">&isin;</mo> <mo stretchy=\"false\">ℝ</mo> </mrow> </semantics> </math>");
  
  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }
  
  return curFormula;
}

double Limacon::calculateX(double t) const
{
  double result = getVariable("x0") + (2 * getVariable("a") * cos(t) + getVariable("b")) * cos(t);

  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }
  
  return result;
}

double Limacon::calculateY(double t) const
{
  double result = getVariable("y0") + (2 * getVariable("a") * cos(t) + getVariable("b")) * sin(t);

  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }
  
  return result;
} 

double Limacon::calculateZ(double t) const
{ return 0; }