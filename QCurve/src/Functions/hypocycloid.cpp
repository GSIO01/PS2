#include "hypocycloid.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Hypocycloid::Hypocycloid( double a, double c, double x0, double y0)
{
  m_name = "Hypocycloid";
  m_param = Parameter(0, 2 * PI, "t");

  setVariable("x0", x0);
  setVariable("y0", y0);

  Variable var("a");
  var.setColor(QColor(255, 255, 0));
  var.interval().setLowerEnd(0);
  var.setValue(a);
  setVariable(var);

  var = Variable("c");
  var.setColor(QColor(0, 255, 255));
  var.interval().setLowerEnd(0);
  var.setValue(c);
  setVariable(var);

  initDimension();
}

Hypocycloid::Hypocycloid(const Hypocycloid& other)
{ *this = other; }

Function* Hypocycloid::clone() const
{ return new Hypocycloid(getVariable("a"), getVariable("c"), getVariable("x0"), getVariable("y0")); }

QString Hypocycloid::toParametricFormula() const
{
  static QString genFormula = QString("<math> <semantics> <mi>x</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo>  <mo>=</mo>  <mfrac> <mn>3</mn> <mn>4</mn> </mfrac> <mo>&middot;</mo> <mi>a</mi> <mo>&middot;</mo> <mi>cos</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mo>+</mo> <mi>c</mi>  <mo>&middot;</mo> <mi>cos</mi> <mo>(</mo> <mn>3t</mn> <mo>)</mo>  <mi>,</mi>  <mi>y</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo>  <mo>=</mo>  <mfrac> <mn>3</mn> <mn>4</mn> </mfrac> <mo>&middot;</mo> <mi>a</mi> <mo>&middot;</mo> <mi>sint</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mo>-</mo> <mi>c</mi> <mo>&middot;</mo> <mi>sin</mi> <mo>(</mo> <mn>3t</mn> <mo>)</mo>  <mo>;</mo>  <mi>a</mi> <mo>,</mo> <mi>c</mi> <mo>&gt;</mo> <mn>0</mn>  <mo>;</mo>  <mi>a</mi> <mi>,</mi> <mi>c</mi> <mo>&isin;</mo> <mo>R</mo>  <mo>;</mo>  <mi>t</mi> <mo>&isin;</mo> <mo>[</mo> <mn>0</mn> <mo>,</mo> <mn>2</mn> <mo>&pi;</mo> <mo>)</mo> </semantics> </math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(QString::number(var.value()));
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

double Hypocycloid::calculateX(double t) const
{ return getVariable("x0") + (0.75 * getVariable("a") * cos(t) + getVariable("c") * cos(3*t)); }

double Hypocycloid::calculateY(double t) const
{ return getVariable("y0") + (0.75 * getVariable("a") * sin(t) - getVariable("c") * sin(3*t)); }

double Hypocycloid::calculateZ(double t) const
{ return 0; }

void Hypocycloid::initDimension()
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");
  double c = getVariable("c");

  double w0 = 0.75 * a * cos(PI) + c * cos(PI * 3);
  double h0 = 0.75 * a * sin(PI * 1.5) - c * sin(PI * 1.5 * 3);

  m_dimension = QRectF(x0 + w0, y0 + h0, -w0 * 2, -h0 * 2);
}
