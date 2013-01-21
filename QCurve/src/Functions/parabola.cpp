#include "parabola.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

#include <QtCore/QDebug>

Parabola::Parabola(double p, double x0, double y0)
{
  m_name = QCoreApplication::translate("Parabola", "Parabola");
  m_param = Parameter(-PI, PI, "t");

  Variable var("p", p);
  var.setColor(QColor(255, 255, 0));
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  initDimension();
}

Parabola::Parabola(const Parabola& other)
{ *this = other; }

Function* Parabola::clone() const
{ return new Parabola(getVariable("p"), getVariable("x0"), getVariable("y0")); }

QString Parabola::toParametricFormula() const
{
  static QString genFormula = QString("<math> <semantics> <mrow> <mi>x</mi> <mrow> <mrow> <mo>(</mo> <mrow> <mi>t</mi> </mrow> <mo>)</mo> </mrow> <mo>=</mo> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> <mtext>,&ThickSpace;&ThickSpace;</mtext> <mi>y</mi> <mrow> <mrow> <mo>(</mo> <mrow> <mi>t</mi> </mrow> <mo>)</mo> </mrow> <mo>=</mo> <mrow> <msqrt> <mrow> <mn>2</mn> <mo>&middot;</mo> <mi>p</mi> </mrow> </msqrt> <mo>&middot;</mo> <mi>t</mi> </mrow> </mrow> <mtext>,&ThickSpace;&ThickSpace;</mtext> <mi>t</mi> <mo>&isin;</mo> <mo>R</mo> </mrow> </semantics> </math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(var.name());
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

Point3D Parabola::calculatePoint(double t) const
{
  double p = getVariable("p");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  return Point3D(x0 + t * t, y0 + sqrt(2 * p) * t, 0);
}

void Parabola::initDimension()
{
  double x0 = getVariable("x0");
  double p = getVariable("p");
  double y0 = getVariable("y0");

  double h = calculatePoint(m_param.to()).y() - calculatePoint(m_param.from()).y(); //TODO
  double w = m_param.to() * m_param.to();

  m_dimension = QRectF(x0, y0 + sqrt(2* p) * m_param.from(), w, h);
}
