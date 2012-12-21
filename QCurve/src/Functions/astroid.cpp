#include "astroid.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Astroid::Astroid(double a, double x0, double y0)
{
  m_name = "Astroid";
  m_param = Parameter(0, 2 * PI, "t");

  setVariable("x0", x0);
  setVariable("y0", y0);

  Variable var("a");
  var.setColor(QColor(255, 255, 0));
  var.interval().setLowerEnd(0);
  var.setValue(a);
  setVariable(var);

  initDimension();
}

Astroid::Astroid(const Astroid& other)
{ *this = other; }

Function* Astroid::clone() const
{ return new Astroid(getVariable("a"), getVariable("x0"), getVariable("y0")); }

QString Astroid::toParametricFormula() const
{
  static QString genFormula = QString("<math><semantics> <mi>x</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo>  <mo>=</mo> <mi>a</mi><mo>&middot;</mo><msup><mi>cos</mi><mn>3</mn> </msup> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mi>,</mi><mi>y</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mo>=</mo> <mi>a</mi><mo>&middot;</mo><msup><mi>sin</mi> <mn>3</mn> </msup> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mi>,</mi> <mi>a</mi><mo>&gt;</mo><mn>0</mn> <mi>,</mi><mi>a</mi><mo>&isin;</mo><mo>R</mo><mi>,</mi><mi>t</mi><mo>&isin;</mo> <mo>[</mo> <mn>0</mn> <mo>,</mo><mn>2</mn><mo>&pi;</mo><mo>)</mo> </semantics></math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(QString::number(var.value()));
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

double Astroid::calculateX(double t) const
{ return getVariable("x0") + (getVariable("a") * pow(cos(t), 3)); }

double Astroid::calculateY(double t) const
{ return getVariable("y0") + (getVariable("a") * pow(sin(t), 3)); }

double Astroid::calculateZ(double t) const
{ return 0; }

void Astroid::initDimension()
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  double w0 = a * pow(cos(PI), 3);
  double h0 = a * pow(sin(PI*1.5), 3);

  m_dimension = QRectF(x0 + w0, y0 + h0, -w0 * 2, -h0 * 2);
}

