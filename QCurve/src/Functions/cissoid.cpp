#include "cissoid.h"

Cissoid::Cissoid(double a, double x0, double y0)
{
  m_name = "Cissoid";
  m_param = Parameter(-1, 1, "t");

  setVariable("a", a);
  setVariable("x0", x0);
  setVariable("y0", y0);
}

Cissoid::Cissoid(const Cissoid& other)
{ *this = other; }

Function* Cissoid::clone() const
{ return new Cissoid(*this); }

QString Cissoid::toParametricFormula() const
{
  static QString genFormula = QString("<math> <semantics> <mi>x</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mi/> <mo>=</mo> <mi/> <mfrac> <msup> <mi>at</mi> <mn>2</mn>   </msup>       <mn>1</mn> <mo>+</mo> <msup> <mi>t</mi> <mn>2</mn> </msup> </mfrac> <mi/> <mi>,</mi> <mi/> <mi>y</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mi/> <mo>=</mo> <mi/> <mfrac> <msup> <mi>at</mi> <mn>3</mn> </msup> <mn>1</mn> <mo>+</mo> <msup> <mi>t</mi>   <mn>2</mn>   </msup>     </mfrac> <mi/> <mi>,</mi> <mi/> <mi>t</mi> <mo>?</mo> <mo>R</mo>   </semantics> </math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), QString::number(var.value())); }

  return curFormula;
}

double Cissoid::calculateX(double t) const
{
  double result = getVariable("x0") + ((getVariable("a")*(t*t))/(1+(t*t)));

  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }

  return result;
}

double Cissoid::calculateY(double t) const
{
  double result = getVariable("y0") + ((getVariable("a")*(t*t*t))/(1+(t*t)));

  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }

  return result;
}

double Cissoid::calculateZ(double t) const
{ return 0; }