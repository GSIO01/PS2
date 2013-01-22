#include "cissoid.h"

#include "Primitives/GraphicalLine"

Cissoid::Cissoid(double a, double x0, double y0)
{
  m_name = QCoreApplication::translate("Cissoid", "Cissoid");
  m_param = Parameter(-1, 1, "t");

  Variable var("a", a);
  var.setColor(QColor(255, 255, 0));
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  updatePoints();
  initDimension();
}

Cissoid::Cissoid(const Cissoid& other)
{ *this = other; }

Function* Cissoid::clone() const
{ return new Cissoid(getVariable("a"), getVariable("x0"), getVariable("y0")); }

QString Cissoid::toParametricFormula() const
{
  static QString genFormula = QString("<math><mrow> <mi>x</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow>  <mo stretchy=\"false\">=</mo> <mi>x0</mi><mo>+</mo> </mrow> <mfrac> <mrow> <mi>a</mi> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> <mrow> <mrow> <mn>1</mn> <mo stretchy=\"false\">+</mo> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> </mrow> </mfrac>" \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>y</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow>  <mo stretchy=\"false\">=</mo> <mi>y0</mi><mo>+</mo> </mrow> <mfrac> <mrow> <mi>a</mi> <msup> <mi>t</mi> <mrow> <mn>3</mn> </mrow> </msup> </mrow> <mrow> <mrow> <mn>1</mn> <mo stretchy=\"false\">+</mo> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> </mrow> </mfrac>" \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>t</mi> <mo stretchy=\"false\">&isin;</mo> <mo stretchy=\"false\">R</mo> </mrow></math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), var.formula()); }

  return curFormula;
}

Point3D Cissoid::calculatePoint(double t) const
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  double t2 = t * t;

  return Point3D(x0 + ((a * t2) / (1 + t2)), y0 + ((a * t2 * t) / (1 + t2)), 0);
}

void Cissoid::initDimension()
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  double t2 = m_param.to() * m_param.to();

  double w = (a * t2) / (1 + t2);
  double h = (a * t2 * m_param.to()) / (1 + t2);

  m_dimension = QRectF(x0, -h + y0 , w, h * 2);
}

void Cissoid::updatePoints(const QString& name, double value)
{
  Q_UNUSED(value);

  double a = getVariable("a");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  Point3D o(x0, y0, 0);
  Point3D s(-a, 0, 0);

  if (name.isNull())
  {
    QString desc;
    Primitive* item = 0;

    m_helper.clear();

    desc = QCoreApplication::translate("Cissoid", "Asymptote of the curve.");
    item = new GraphicalLine(Point3D(a, -a * 100), Point3D(a, a * 100), "A", desc);
    m_helper.append(item);
  }
  else
  {
    ((GraphicalLine*)getHelperItem("A"))->setStartPoint(Point3D(a, -a * 100 + y0));
    ((GraphicalLine*)getHelperItem("A"))->setEndPoint(Point3D(a, a * 100, 0));
  }

}