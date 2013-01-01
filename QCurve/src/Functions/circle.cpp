#include "circle.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Circle::Circle(double r, double x0, double y0)
{
  m_param = Parameter(0, 2 * PI, "t");
  m_name = "Circle";

  Variable var("r", r);
  var.setColor(QColor(255, 255, 0));
  var.interval().setLowerEnd(0);
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

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
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(QString::number(var.value()));
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
