#include "limacon.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Limacon::Limacon(double a, double b, double x0, double y0)
{
  m_name = QCoreApplication::translate("Limacon", "Limacon");
  m_param = Parameter(0, 2 * PI, "t");

  Variable var("a", a);
  var.setColor(QColor(255, 255, 0));
  setVariable(var);

  var = Variable("b", b);
  var.setColor(QColor(0, 255, 255));
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  initDimension();
}

Limacon::Limacon(const Limacon& other)
{ *this = other; }

Function* Limacon::clone() const
{ return new Limacon(getVariable("a"), getVariable("b"), getVariable("x0"), getVariable("y0")); }

QString Limacon::toParametricFormula() const
{
  static QString genFormula = QString("<math> <semantics> <mrow> <mi>x</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow> <mi/> <mo stretchy=\"false\">=</mo> <mi/> </mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mn>2</mn><mo>&middot;</mo><mi>a</mi> <mi>cos</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mo stretchy=\"false\">+</mo> <mi>t</mi> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mi>cos</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mi/> <mtext>,&ThickSpace;&ThickSpace;</mtext> <mi/> <mi>y</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow> <mi/> <mo stretchy=\"false\">=</mo> <mi/> </mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mn>2</mn><mo>&middot;</mo><mi>a</mi> <mi>cos</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mo stretchy=\"false\">+</mo> <mi>b</mi> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mi>sin</mi> <mrow> <mo stretchy=\"false\">(</mo><mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mi/> <mtext>,&ThickSpace;&ThickSpace;</mtext> <mi/> <mi>t</mi> <mo stretchy=\"false\">&isin;</mo> <mo stretchy=\"false\">Rù</mo> </mrow> </semantics> </math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(var.name());
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

Point3D Limacon::calculatePoint(double t) const
{
  double a = getVariable("a");
  double b = getVariable("b");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  double tmp = 2 * a * cos(t) + b;

  return Point3D(x0 + tmp * cos(t), y0 + tmp * sin(t), 0);
}

void Limacon::initDimension()
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");
  double b = getVariable("b");

  double h = 2 * a + b * sin(0.3);

  m_dimension = QRectF(-a + x0, -h + y0, 4 * a, 2 * h);
}
