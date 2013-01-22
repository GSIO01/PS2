#include "hypocycloid.h"

#include "Primitives/GraphicalCircle"
#include "Primitives/GraphicalLine"

#include <QtCore/qmath.h> //TODO
#define PI 3.141592653589793

Hypocycloid::Hypocycloid( double a, double c, double x0, double y0)
{
  m_name = QCoreApplication::translate("Hypocycloid", "Hypocycloid"); //TODO
  m_param = Parameter(0, 2 * PI, "t");

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  Variable var("a");
  var.setDescription(QCoreApplication::translate("Hypocycloid",
    "The radius of the circle where a circle (r=a/4) rolls around inside."));
  var.setColor(QColor(255, 255, 0));
  var.interval().setLowerEnd(0);
  var.setValue(a);
  setVariable(var);

  var = Variable("c");
  var.setDescription(QCoreApplication::translate("Hypocycloid",
    "The (relative) distance from the midpoint of the rolling cycle.\n \
    If c is less than or higher than a/4 the hypocycloid is shortend or lengthened."));
  var.setColor(QColor(0, 255, 255));
  var.interval().setLowerEnd(0);
  var.setValue(c);
  setVariable(var);

  updatePoints();
  initDimension();
}

Hypocycloid::Hypocycloid(const Hypocycloid& other)
{ *this = other; }

Function* Hypocycloid::clone() const
{ return new Hypocycloid(getVariable("a"), getVariable("c"), getVariable("x0"), getVariable("y0")); }

QString Hypocycloid::toParametricFormula() const
{
  static QString genFormula = QString("<math><mi>x</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo>  <mo>=</mo> <mi>x0</mi><mo>+</mo> <mfrac> <mn>3</mn> <mn>4</mn> </mfrac> <mo>&middot;</mo> <mi>a</mi> <mo>&middot;</mo> <mi>cos</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mo>+</mo> <mi>c</mi>  <mo>&middot;</mo> <mi>cos</mi> <mo>(</mo> <mn>3t</mn> <mo>)</mo>" \
  "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
  "<mi>y</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo>  <mo>=</mo><mi>y0</mi><mo>+</mo>   <mfrac> <mn>3</mn> <mn>4</mn> </mfrac> <mo>&middot;</mo> <mi>a</mi> <mo>&middot;</mo> <mi>sint</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mo>-</mo> <mi>c</mi> <mo>&middot;</mo> <mi>sin</mi> <mo>(</mo> <mn>3t</mn> <mo>)</mo>" \
  "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>"
  "<mi>a</mi> <mo>,</mo> <mi>c</mi> <mo>&gt;</mo> <mn>0</mn>" \
  ",<mo>&InvisibleTimes;</mo>" \
  "<mi>a</mi> <mi>,</mi> <mi>c</mi> <mo>&isin;</mo> <mo>R</mo>" \
  ",<mo>&InvisibleTimes;</mo>" \
  "<mi>t</mi> <mo>&isin;</mo> <mo>[</mo> <mn>0</mn> <mo>,</mo> <mn>2</mn> <mo>&pi;</mo> <mo>)</mo></math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), var.formula()); }

  return curFormula;
}

void Hypocycloid::updatePoints(const QString& name, double value)
{
  Q_UNUSED(value);

  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  if (name.isNull())
  {
    Primitive* item = new GraphicalCircle(Point3D(x0, y0 + a/4, 0), a/4, "Rc");
    item->setIsAnimated(true);
    m_helper.append(item);

    item = new GraphicalCircle(Point3D(x0, y0, 0), a, "K0");
    item->setIsAnimated(true); //TODO
    m_helper.append(item);

    item = new GraphicalLine(Point3D(x0, y0 + a/4, 0), Point3D(x0, y0, 0), "Rcl");
    item->setIsAnimated(true);
    m_helper.append(item);
  }
  else
  {
    ((GraphicalLine*)getHelperItem("Rcl"))->setStartPoint(Point3D(x0, y0 + a/4, 0));

    GraphicalCircle* item = (GraphicalCircle*)getHelperItem("Rc");
    item->setMidPoint(Point3D(x0, y0 + a/4, 0));
    if (name == "a") { item->setRadius(a/4); }

    item = (GraphicalCircle*)getHelperItem("K0");
    item->setMidPoint(Point3D(x0, y0, 0));
    if (name == "a") { item->setRadius(a); }
  }
}

Point3D Hypocycloid::calculatePoint(double t) const
{
  double a = getVariable("a");
  double c = getVariable("c");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  Point3D result(x0 + (0.75 * a * cos(t) + c * cos(3 * t)),
                 y0 + (0.75 * a * sin(t) - c * sin(3 * t)), 0);

  ((GraphicalCircle*)getHelperItem("Rc"))->setMidPoint(Point3D(x0 + ((3*a)/4) * cos(t), y0 + ((3*a)/4) * sin(t), 0));

  GraphicalLine* item = (GraphicalLine*)getHelperItem("Rcl");
  item->setStartPoint(Point3D(x0 + ((3*a)/4) * cos(t), y0 + ((3*a)/4) * sin(t), 0));
  item->setEndPoint(Point3D(result.x(), result.y(), 0));

  return result;
}

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
