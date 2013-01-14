#include "lemniscate.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Lemniscate::Lemniscate(double a, double x0, double y0)
{
  m_name = QCoreApplication::translate("Lemniscate", "Lemniscate");
  m_param = Parameter(0, 2*PI, "t");

  Variable var("a", a);
  var.setColor(QColor(255, 255, 0));
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

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
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(var.name());
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

Point3D Lemniscate::calculatePoint(double t) const
{
  double a = getVariable("a");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  double tmp = a * sqrt(2 * cos(2 * t));
  double x = x0 + (tmp * cos(t));
  double y = y0 + (tmp * sin(t));

  if (x != x) { x = x0; }
  if (y != y) { y = y0; }

  return Point3D(x, y, 0);
}

void Lemniscate::initDimension()
{
  double a = getVariable("a");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  m_dimension = QRectF(-2 * a + x0, -a + y0, 4 * a, 2 * a);
}
