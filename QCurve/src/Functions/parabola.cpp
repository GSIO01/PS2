#include "parabola.h"

#include <QtCore/qmath.h> //TODO

#include "Primitives/GraphicalPoint"
#include "Primitives/GraphicalLine"

Parabola::Parabola(double p, double x0, double y0)
{
  init();

  m_name = QCoreApplication::translate("Parabola", "Parabola");
  m_param = Parameter(-5, 5, "t");

  Variable var("p", p);
  var.interval().setLowerEnd(0);
  var.setColor(QColor(255, 128, 0));
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  initDimension();
  updatePoints();
}

Parabola::Parabola(const Parabola& other)
{ *this = other; }

Function* Parabola::clone() const
{ return new Parabola(getVariable("p"), getVariable("x0"), getVariable("y0")); }

QString Parabola::toParametricFormula() const
{
  static QString genFormula = QString("<math> <mrow> <mi>x</mi> <mrow> <mrow> <mo>(</mo> <mrow> <mi>t</mi> </mrow> <mo>)</mo> </mrow> <mo>=</mo><mi>x0</mi><mo>+</mo> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow>"\
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>"\
    "<mi>y</mi> <mrow> <mrow> <mo>(</mo> <mrow> <mi>t</mi> </mrow> <mo>)</mo> </mrow> <mo>=</mo> <mi>y0</mi><mo>+</mo> <mrow> <msqrt> <mrow> <mn>2</mn> <mo>&middot;</mo> <mi>p</mi> </mrow> </msqrt> <mo>&middot;</mo> <mi>t</mi> </mrow> </mrow>"\
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>"\
    "<mi>t</mi> <mo>&isin;</mo> <mo>R</mo> </mrow> </math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), var.formula()); }

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

void Parabola::updatePoints(const QString& name, double value)
{
  Q_UNUSED(value);

  double x0 = getVariable("x0");
  double p = getVariable("p");
  double y0 = getVariable("y0");

  if (name.isEmpty())
  {
    Primitive* item = new GraphicalPoint(Point3D(x0 + p/2, y0), "F",
      QCoreApplication::translate("Parabola", "Focus point."));
    m_helper.append(item);

    item = new GraphicalLine(Point3D(x0 - p/2, m_dimension.bottom() * 2), Point3D(x0 - p/2, m_dimension.top() * 2),
      "g", QCoreApplication::translate("Parabola", "Directrix"));
    m_helper.append(item);
  }
  else
  {
    ((GraphicalPoint*)getHelperItem("F"))->setPoint(Point3D(x0 + p/2, y0));

    ((GraphicalLine*)getHelperItem("g"))->setStartPoint(Point3D(x0 - p/2, m_dimension.bottom() * 2));
    ((GraphicalLine*)getHelperItem("g"))->setEndPoint(Point3D(x0 - p/2, m_dimension.top() * 2));
  }
}