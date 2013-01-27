#include "cissoid.h"
#include <cmath>
#include <QDebug>
#include "Primitives/GraphicalPoint"
#include "Primitives/GraphicalCircle"
#include "Primitives/GraphicalLine"

Cissoid::Cissoid(double a, double x0, double y0)
{
  init();

  m_name = QCoreApplication::translate("Cissoid", "Cissoid");
  m_param = Parameter(-2, 2, "t");

  Variable var("a", a);
  var.setDescription(QCoreApplication::translate("Cissoid","Radius of the circle"));
  var.setColor(QColor(255, 128, 0));
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
  static QString genFormula = QString("<math><mrow> <mi>x</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow>  <mo stretchy=\"false\">=</mo> <mi>x0</mi><mo>+</mo> </mrow> <mfrac> <mrow> <mi>a</mi> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> <mrow> <mrow> <mn>1</mn> <mo stretchy=\"false\">+</mo> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> </mrow> </mfrac>  " \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>y</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow>  <mo stretchy=\"false\">=</mo> <mi>y0</mi><mo>+</mo> </mrow> <mfrac> <mrow> <mi>a</mi> <msup> <mi>t</mi> <mrow> <mn>3</mn> </mrow> </msup> </mrow> <mrow> <mrow> <mn>1</mn> <mo stretchy=\"false\">+</mo> <msup> <mi>t</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> </mrow> </mfrac>  " \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>t</mi> <mo stretchy=\"false\">&isin;</mo> <mo stretchy=\"false\">R</mo> </mrow></math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), var.formula()); }

  return curFormula;
}

void Cissoid::updatePoints(const QString& name, double value)
{
  Q_UNUSED(value);

  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  if(name.isNull())
  {
    Primitive* item = new GraphicalCircle(Point3D((a/2) + x0, y0), ((a/2) < 0 ? -a/2 : a/2), "Rc");
    m_helper.append(item);

    item = new GraphicalPoint(Point3D(a/2+x0,y0,0), "M(x0,y0)", QCoreApplication::translate("Cissoid","Center of the circle"));
    m_helper.append(item);

    item = new GraphicalPoint(Point3D(x0,y0,0), "S");
    item->setColor(QColor(0, 200, 0));
    m_helper.append(item);

    item = new GraphicalLine(Point3D(a + x0, -a + y0), Point3D(a + x0, a + y0), "g1",
                             QCoreApplication::translate("Cissoid", "Asymptote of the curve"));
    m_helper.append(item);
  }
  else
  {
    ((GraphicalPoint*)getHelperItem("M"))->setPoint(Point3D(a/2+x0,y0,0));
    ((GraphicalPoint*)getHelperItem("S"))->setPoint(Point3D(x0,y0,0));

    ((GraphicalLine*)getHelperItem("g1"))->setStartPoint(Point3D(a+x0, -a+y0, 0));
    ((GraphicalLine*)getHelperItem("g1"))->setEndPoint(Point3D(a+x0, a+y0, 0));

    GraphicalCircle* item = (GraphicalCircle*)getHelperItem("Rc");
    item->setMidPoint(Point3D((a/2)));
    item->setRadius((a/2)<0?(-a/2):(a/2));
  }

}

Point3D Cissoid::calculatePoint(double t) const
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  double t2 = t * t;
  double a3t = a * t2 * t;

  ((GraphicalLine*)getHelperItem("g1"))->setStartPoint(Point3D(a+x0, -(a3t / (1 + t2))+y0, 0));
  ((GraphicalLine*)getHelperItem("g1"))->setEndPoint(Point3D(a+x0, (a3t / (1 + t2))+y0, 0));

  return Point3D(x0 + (a * t2 / (1 + t2)), y0 + (a3t / (1 + t2)), 0);
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
