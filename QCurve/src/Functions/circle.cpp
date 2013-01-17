#include "circle.h"

#include "Primitives/GraphicalPoint"
#include "Primitives/GraphicalLine"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Circle::Circle(double r, double x0, double y0)
{
  m_param = Parameter(0, 2 * PI, "t");
  m_name = QCoreApplication::translate("Circle", "Circle");

  Variable var("r", r);
  var.setColor(QColor(255, 255, 0));
  var.interval().setLowerEnd(0);
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  updatePoints();
  initDimension();
}

Circle::Circle(const Circle& other)
{ *this = other; }

Function* Circle::clone() const
{ return new Circle(getVariable("r"), getVariable("x0"), getVariable("y0")); }

QString Circle::toParametricFormula() const
{
  static QString genFormula = QString("<math>x(t)<mo>=</mo><mi>x0</mi><mo>+</mo><mi>r</mi><mo>&middot;</mo><mi>cos</mi>(<mi>t</mi>), y(t)<mo>=</mo><mi>y0</mi><mo>+</mo><mi>r</mi><mo>&middot;</mo><mi>sin</mi>(<mi>t</mi>)</math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(var.name());
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

Point3D Circle::calculatePoint(double t) const
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double r = getVariable("r");

  return Point3D(x0 + r * cos(t), y0 + r * sin(t), 0);
}

void Circle::initDimension()
{
  double r = getVariable("r");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  m_dimension = QRectF(-r + x0, -r + y0 , 2 * r, 2 * r);
}

void Circle::updatePoints(const QString& name, double value) {
  Q_UNUSED(value);
  
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double r = getVariable("r");
  
  Point3D m(x0, y0, 0);
  Point3D d1 = calculatePoint(M_PI/4);
  Point3D d2 = calculatePoint(M_PI*1.25);
  
  if(name.isNull()) {
    Primitive* item = new GraphicalLine(Point3D(x0 + r, y0, 0), Point3D(x0, y0, 0), "r", QCoreApplication::translate("Circle", "Radius of the circle."));
    QString desc = QCoreApplication::translate("Circle", "The Center point of the circle.");

    m_helper.clear();
    
    m_helper.append(new GraphicalPoint(m, "M", desc));
    m_helper.append(item);
    item = new GraphicalLine(d1, d2, "d", QCoreApplication::translate("Circle", "Diameter of the circle."));
    m_helper.append(item);
  } else {
    ((GraphicalPoint*)getHelperItem("M"))->setPoint(m);
    ((GraphicalLine*)getHelperItem("r"))->setStartPoint(Point3D(x0 + r, y0, 0));
    ((GraphicalLine*)getHelperItem("r"))->setEndPoint(Point3D(x0, y0, 0));
    ((GraphicalLine*)getHelperItem("d"))->setStartPoint(d1);
    ((GraphicalLine*)getHelperItem("d"))->setEndPoint(d2);
  }
}
