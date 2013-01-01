#include "cycloid.h"

#include "Primitives/GraphicalCircle"
#include "Primitives/GraphicalLine"

#include <QtCore/qmath.h> //TODO
#define PI 3.141592653589793

Cycloid::Cycloid(double r, double m, double x0, double y0)
{
  m_name = "Cycloid";
  m_param = Parameter(-2*PI, 2*PI, "t");

  Variable var("r",r);
  var.setColor(QColor(255, 255, 0));
  setVariable(var);

  var = Variable("mu", m);
  var.setColor(QColor(0, 255, 255));
  var.setFormula("<mi color=\"#00FFFF\">&mu;</mi>");
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  updatePoints();
  initDimension();
}

Cycloid::Cycloid(const Cycloid& other)
{ *this = other; }

Function* Cycloid::clone() const
{ return new Cycloid(getVariable("r"), getVariable("mu"), getVariable("x0"), getVariable("y0")); }

QString Cycloid::toParametricFormula() const
{
  static QString genFormula = QString("<math><semantics><mi>x</mi><mo>(</mo><mi>t</mi><mo>)</mo><mi/><mo>=</mo><mi/><mi>r</mi><mo>(</mo><mi>t</mi><mo>-</mo><mi>mu</mi><mi>sin</mi><mo>(</mo><mi>t</mi><mo>)</mo><mo>)</mo><mi/><mi>,</mi><mi/>" \
                                      "<mi>y</mi><mo>(</mo><mi>t</mi><mo>)</mo><mi/><mo>=</mo><mi/><mi>r</mi><mo>(</mo><mn>1</mn><mo>-</mo><mi>mu</mi><mi>cos</mi><mo>(</mo><mi>t</mi><mo>)</mo><mo>)</mo><mi/><mi>,</mi><mi/><mi>t</mi><mo>&isin;</mo><mo>R</mo></semantics></math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(QString::number(var.value()));
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

void Cycloid::updatePoints(const QString& name, double value)
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double r = getVariable("r");

  if(name.isNull())
  {
    Primitive* item = new GraphicalCircle(Point3D(x0, y0 + r, 0), r, "Rc");
    item->setIsAnimated(true);
    m_helper.append(item);

    item = new GraphicalLine(Point3D(x0, y0 + r, 0), Point3D(x0, y0, 0), "Rcl");
    item->setIsAnimated(true);
    m_helper.append(item);
  }
  else if (name == "r")
  {
    ((GraphicalLine*)getHelperItem("Rcl"))->setStartPoint(Point3D(x0, y0 + r, 0));

    GraphicalCircle* item = (GraphicalCircle*)getHelperItem("Rc");
    item->setMidPoint(Point3D(x0, y0 + r, 0));
    item->setRadius(value);
  }
}

Point3D Cycloid::calculatePoint(double t) const
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double r = getVariable("r");
  double mu = getVariable("mu");

  Point3D result = Point3D(x0 + r * (t - mu * sin(t)), y0 + r * (1 - mu * cos(t)), 0);

  ((GraphicalCircle*)getHelperItem("Rc"))->setMidPoint(Point3D(result.x() + r * sin(t), y0 + r, 0));

  Primitive* item = getHelperItem("Rcl");
  ((GraphicalLine*)getHelperItem("Rcl"))->setStartPoint(Point3D(result.x() + r * sin(t), y0 + r, 0));
  ((GraphicalLine*)getHelperItem("Rcl"))->setEndPoint(Point3D(result.x(), result.y(), 0));

  return result;
}

void Cycloid::initDimension()
{
  double r = getVariable("r");
  double mu = getVariable("mu");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  double w0 = r * (m_param.from() - mu * sin(m_param.from()));
  double w1 = r * (m_param.to() - mu * sin(m_param.to()));
  double h0 = r * (1 - mu);
  double h1 = r * (1 + mu);

  m_dimension = QRectF(w0 + x0, h0 + y0, w1 - w0, h1 - h0);
}
