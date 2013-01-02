#include "astroid.h"

#include "Primitives/GraphicalCircle"
#include "Primitives/GraphicalLine"

#include <QtCore/qmath.h> //TODO
#define PI 3.141592653589793

Astroid::Astroid(double a, double x0, double y0)
{
  m_name = "Astroid";
  m_param = Parameter(0, 2 * PI, "t");

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  Variable var("a");
  var.setDescription("The radius of the circle where a circle (r=a/4) rolls around inside.");
  var.setColor(QColor(255, 255, 0));
  var.interval().setLowerEnd(0);
  var.setValue(a);
  setVariable(var);

  updatePoints();
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

void Astroid::updatePoints(const QString& name, double value)
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

Point3D Astroid::calculatePoint(double t) const
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  Point3D result(x0 + a * pow(cos(t), 3), x0 + a * pow(sin(t), 3), 0);

  ((GraphicalCircle*)getHelperItem("Rc"))->setMidPoint(Point3D(x0 + ((3*a)/4) * cos(t), y0 + ((3*a)/4) * sin(t), 0));

  GraphicalLine* item = (GraphicalLine*)getHelperItem("Rcl");
  item->setStartPoint(Point3D(x0 + ((3*a)/4) * cos(t), y0 + ((3*a)/4) * sin(t), 0));
  item->setEndPoint(Point3D(result.x(), result.y(), 0));

  return result;
}

void Astroid::initDimension()
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  double w0 = a * pow(cos(PI), 3);
  double h0 = a * pow(sin(PI * 1.5), 3);

  m_dimension = QRectF(x0 + w0, y0 + h0, -w0 * 2, -h0 * 2);
}

