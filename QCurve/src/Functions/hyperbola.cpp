#include "hyperbola.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Hyperbola::Hyperbola(double a, double b, double x0, double y0)
{
  m_name = "Hyperbola";
  m_param = Parameter(-PI, PI, "t");

  Variable var("a", a);
  var.setColor(QColor(255, 255, 0));
  setVariable(var);

  var = Variable("b", b);
  var.setColor(QColor(0, 255, 255));
  setVariable(var);

  setVariable("x0", x0);
  setVariable("y0", y0);

  initDimension();
}

Hyperbola::Hyperbola(const Hyperbola& other)
{ *this = other; }

Function* Hyperbola::clone() const
{ return new Hyperbola(getVariable("a"), getVariable("b"), getVariable("x0"), getVariable("y0")); }

QString Hyperbola::toParametricFormula() const
{
  static QString genFormula = QString("<math> <semantics> <mi>x</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mo>=</mo> <mi>a</mi> <mo>&middot;</mo> <mi>cosh</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mi>,</mi> <mi>y</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mo>=</mo> <mi>b</mi> <mo>&middot;</mo> <mi>sinh</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mi>,</mi> <mi>t</mi> <mo>&isin;</mo> <mo>R</mo> </semantics> </math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(QString::number(var.value()));
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

double Hyperbola::calculateX(double t) const
{ return getVariable("x0") + getVariable("a") * cosh(t); }

double Hyperbola::calculateY(double t) const
{ return getVariable("y0") + getVariable("b") * sinh(t); }

double Hyperbola::calculateZ(double t) const
{ return 0; }

void Hyperbola::initDimension()
{
  double x0 = getVariable("x0");
  double a = getVariable("a");
  double b = getVariable("b");
  double y0 = getVariable("y0");

  double t = (abs(m_param.to()) > abs(m_param.from())) ? m_param.to() : m_param.from();
  double w = a * cosh(t);
  double h0 = a * sinh(m_param.from());
  double h = a * sinh(m_param.to()) - h0;

  m_dimension = QRectF(a + x0, h0 + y0, w, h);
}
