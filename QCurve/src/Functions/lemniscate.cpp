#include "lemniscate.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Lemniscate::Lemniscate(double a, double x0, double y0)
{
  m_name = "Lemniscate";
  m_param = Parameter(0, 2*PI, "t");

  Variable var("a", a);
  var.setColor(QColor(255, 255, 0));
  setVariable(var);

  setVariable("x0", x0);
  setVariable("y0", y0);

  initDimension();
}

Lemniscate::Lemniscate(const Lemniscate& other)
{ *this = other; }

Function* Lemniscate::clone() const
{ return new Lemniscate(getVariable("a"), getVariable("x0"), getVariable("y0")); }


QString Lemniscate::toParametricFormula() const
{
  static QString genFormula = QString("<math> <semantics> <mrow> <mi>x</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow> <mi/> <mo stretchy=\"false\">=</mo> <mi/> </mrow> <mfrac> <mrow> <mi>a</mi> <msqrt> <mrow> <mn>2</mn> </mrow> </msqrt> <mi>cos</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> </mrow> <mrow> <mi>sin</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mo stretchy=\"false\">+</mo> <mn>1</mn> </mrow> </mrow> </mfrac> <mi/> <mi>,</mi> <mi/> <mi>y</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow> <mi/> <mo stretchy=\"false\">=</mo> <mi/> </mrow> <mfrac> <mrow> <mi>a</mi> <msqrt> <mrow> <mn>2</mn> </mrow> </msqrt> <mi>cos</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mi>sin</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> </mrow> <mrow> <mi>sin</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mo stretchy=\"false\">+</mo> <mn>1</mn> </mrow> </mrow> </mfrac> <mi/> <mi>,</mi> <mi/> <mrow> <mrow> <mn>0</mn> <mo stretchy=\"false\">&leq;</mo> <mi>t</mi> </mrow> <mo stretchy=\"false\">&lt;</mo> <mn>2</mn> </mrow> <mo stretchy=\"false\">&pi;</mo> </mrow> </semantics> </math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(QString::number(var.value()));
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

double Lemniscate::calculateX(double t) const
{
  double result = getVariable("x0") + (getVariable("a") * sqrt(2 * cos(2 * t)) * cos(t));

  if (result != result) { return getVariable("x0"); }

  return result;
}

double Lemniscate::calculateY(double t) const
{
  double result = getVariable("y0") + (getVariable("a") * sqrt(2* cos(2 * t)) * sin(t));

  if (result != result) { return getVariable("y0"); }

  return result;
}

double Lemniscate::calculateZ(double t) const
{ return 0; }

void Lemniscate::initDimension()
{
  double a = getVariable("a");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  m_dimension = QRectF(-2 * a + x0, -a + y0, 4 * a, 2 * a);
}
