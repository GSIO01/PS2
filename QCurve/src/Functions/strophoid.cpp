#include "strophoid.h"

Strophoid::Strophoid(double a, double x0, double y0)
{
  m_name = "Strophoid";
  m_param = Parameter(-2, 2, "t");

  Variable var("a", a);
  var.setColor(QColor(255, 255, 0));
  setVariable(var);

  setVariable("x0", x0);
  setVariable("y0", y0);

  initDimension();
}

Strophoid::Strophoid(const Strophoid& other)
{ *this = other; }

Function* Strophoid::clone() const
{ return new Strophoid(getVariable("a"), getVariable("x0"), getVariable("y0")); }

QString Strophoid::toParametricFormula() const
{
  static QString genFormula = QString("<math> <semantics> <mrow> <mi>x</mi> <mrow> <mo>(</mo> <mrow> <mi>t</mi> </mrow> <mo>)</mo> </mrow> <mrow> <mi/><mo stretchy=\"false\">=</mo> <mi/> </mrow> <mfrac> <mrow> <mi>a</mi> <mrow><mo>(</mo> <mrow> <mrow> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> <mo stretchy=\"false\">-</mo> <mn>1</mn> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> </mrow> <mrow> <mrow> <mn>1</mn> <mo stretchy=\"false\">+</mo> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> </mrow> </mfrac> <mi/> <mi>,</mi> <mi/> <mi>y</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow> <mi/> <mo stretchy=\"false\">=</mo> <mi/> </mrow> <mfrac> <mrow> <mi>a</mi> <mo>t</mo> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mrow> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> <mo stretchy=\"false\">-</mo> <mn>1</mn> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> </mrow> <mrow> <mrow> <mn>1</mn> <mo stretchy=\"false\">+</mo> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> </mrow> </mfrac> <mi/> <mi>,</mi> <mi/> <mi>t</mi> <mo stretchy=\"false\">&isin;</mo> <mo stretchy=\"false\">R</mo> </mrow> </semantics> </math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(QString::number(var.value()));
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

double Strophoid::calculateX(double t) const
{
  double result = getVariable("x0") + ((getVariable("a") * ((t*t)-1))/(1+(t*t)));

  if (result < m_dimension.left())
  { m_dimension.setLeft(result); }
  else if (result > m_dimension.right())
  { m_dimension.setRight(result); }

  return result;
}

double Strophoid::calculateY(double t) const
{
  double result = getVariable("y0") + ((getVariable("a") * t * ((t*t)-1))/(1+(t*t)));

  if (result < m_dimension.bottom())
  { m_dimension.setBottom(result); }
  else if (result > m_dimension.top())
  { m_dimension.setTop(result); }

  return result;
}

double Strophoid::calculateZ(double t) const
{ return 0; }

void Strophoid::initDimension()
{
  double a = getVariable("a");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  m_dimension = QRectF(-a + x0, -a * 1.15 + y0, a * 2, a * 2.3);
}
