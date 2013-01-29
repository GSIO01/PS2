#include "strophoid.h"

#include "Primitives/GraphicalPoint"
#include "Primitives/GraphicalLine"

Strophoid::Strophoid(double a, double x0, double y0)
{
  init();

  m_name = QCoreApplication::translate("Strophoid", "Strophoid");
  m_param = Parameter(-2.8, 2.8, "t");

  Variable var("a", a);
  var.interval().setLowerEnd(0);
  var.setColor(QColor(255, 128, 0));
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  initDimension();
  updatePoints();
}

Strophoid::Strophoid(const Strophoid& other)
{ *this = other; }

Function* Strophoid::clone() const
{ return new Strophoid(getVariable("a"), getVariable("x0"), getVariable("y0")); }

QString Strophoid::toParametricFormula() const
{
  static QString genFormula = QString("<math><mrow> <mi>x</mi> <mrow> <mo>(</mo> <mrow> <mi>t</mi> </mrow> <mo>)</mo> </mrow> <mrow> <mo stretchy=\"false\">=</mo> <mi>x0</mi><mo>+</mo> </mrow> <mfrac> <mrow> <mi>a</mi> <mrow><mo>(</mo> <mrow> <mrow> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> <mo stretchy=\"false\">-</mo> <mn>1</mn> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> </mrow> <mrow> <mrow> <mn>1</mn> <mo stretchy=\"false\">+</mo> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> </mrow> </mfrac>" \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>y</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow>  <mo stretchy=\"false\">=</mo> <mi>y0</mi><mo>+</mo> </mrow> <mfrac> <mrow> <mi>a</mi> <mo>t</mo> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mrow> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> <mo stretchy=\"false\">-</mo> <mn>1</mn> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> </mrow> <mrow> <mrow> <mn>1</mn> <mo stretchy=\"false\">+</mo> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> </mrow> </mfrac>" \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>t</mi> <mo stretchy=\"false\">&isin;</mo> <mo stretchy=\"false\">R</mo> </mrow></math>");


  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), var.formula()); }

  return curFormula;
}

Point3D Strophoid::calculatePoint(double t) const
{
  double a = getVariable("a");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  return Point3D(x0 + (a * (t*t - 1))/(1 + t*t), y0 + (a * t * (t*t - 1))/(1 + t*t), 0);
}

void Strophoid::initDimension()
{
  double a = getVariable("a");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  double h = (a * m_param.to()   * (m_param.to()   * m_param.to()   - 1)) / (1 + m_param.to()   * m_param.to()) -
             (a * m_param.from() * (m_param.from() * m_param.from() - 1)) / (1 + m_param.from() * m_param.from());

  m_dimension = QRectF(-a + x0, y0 - h/2, a * 2, h);
}

void Strophoid::updatePoints(const QString& name, double value)
{
  Q_UNUSED(value);

  double a = getVariable("a");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  Point3D o(x0, y0, 0);
  Point3D s(-a, 0, 0);

  if (name.isNull())
  {
    Primitive * item = new GraphicalPoint(o, "O", QCoreApplication::translate("Strophoid", "The origin point of the curve."));
    item->setColor(QColor(0, 200, 0));
    m_helper.append(item);

    item = new GraphicalPoint(s, "S", QCoreApplication::translate("Strophoid", "Fixed point of the strophoid."));
    m_helper.append(item);

    item = new GraphicalLine(Point3D(a, m_dimension.top() * 2), Point3D(a, m_dimension.bottom() * 2), "A",
                             QCoreApplication::translate("Strophoid", "Asymptote of the curve (x=a)."));
    item->setColor(m_variables.at(2).color());
    m_helper.append(item);
  }
  else
  {
    ((GraphicalPoint*)getHelperItem("O"))->setPoint(o);
    ((GraphicalPoint*)getHelperItem("S"))->setPoint(s);
    ((GraphicalLine*)getHelperItem("A"))->setStartPoint(Point3D(a, -a * 100 + y0));
    ((GraphicalLine*)getHelperItem("A"))->setEndPoint(Point3D(a, a * 100, 0));
  }
}
