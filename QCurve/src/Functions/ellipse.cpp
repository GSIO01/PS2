#include "ellipse.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Ellipse::Ellipse(double a, double b, double x0, double y0)
{
  m_param = Parameter(0, 2 * PI, "t");
  m_name = "Ellipse";

  Variable var("a", a);
  var.setDescription("The radius along the x-axis. The x-axis is the major radius [a > b] or the minor radius.");
  var.setColor(QColor(255, 255, 0));
  var.interval().setLowerEnd(0);
  setVariable(var);

  var = Variable("b", b);
  var.setDescription("The radius along the y-axis. The y-axis is the major radius [b < a] or the minor radius.");
  var.setColor(QColor(0, 255, 255));
  var.interval().setLowerEnd(0);
  setVariable(var);

  setVariable("x0", x0);
  setVariable("y0", y0);

  updatePoints();
  initDimension();
}

Ellipse::Ellipse(const Ellipse& other)
{ *this = other; }

Function* Ellipse::clone() const
{ return new Ellipse(*this); }

QString Ellipse::toParametricFormula() const
{
  static QString genFormula = QString("<math>x(t)<mo>=</mo><mi>x0</mi><mo>+</mo><mi>a</mi><mo>&middot;</mo><mi>cos</mi>(<mi>t</mi>), y(t)<mo>=</mo><mi>y0</mi><mo>+</mo><mi>b</mi><mo>&middot;</mo><mi>sin</mi>(<mi>t</mi>)</math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(QString::number(var.value()));
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

void Ellipse::updatePoints(const QString& name, double value)
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");
  double b = getVariable("b");

  QString desc = "One focus point of the ellipse. \
    The foci always lie on the major (longest) axis and \
    are equidistant from the center point.";
  if (b < a)
  {
    double f = sqrt(pow(a, 2) - pow(b, 2));
    setPoint(Point(-f + x0, y0, "F1", desc));
    setPoint(Point( f + x0, y0, "F2", desc));
  }
  else
  {
    double f = sqrt(pow(b, 2) - pow(a, 2));
    setPoint(Point(x0, -f + y0, "F1", desc));
    setPoint(Point(x0,  f + y0, "F2", desc));
  }

  if (name != "b")
  {
    setPoint(Point( a + x0, y0, "a" ));
    setPoint(Point(-a + x0, y0, "-a"));
  }
  if (name != "a")
  {
    setPoint(Point(x0,-b + y0, "-b"));
    setPoint(Point(x0, b + y0, "b" ));
  }
}

double Ellipse::calculateX(double t) const
{ return getVariable("x0") + getVariable("a") * qCos(t); }

double Ellipse::calculateY(double t) const
{ return getVariable("y0") + getVariable("b") * qSin(t); }

double Ellipse::calculateZ(double t) const
{ return 0; }

void Ellipse::initDimension()
{
  double a = getVariable("a");
  double b = getVariable("b");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  m_dimension = QRectF(-a + x0, -b + y0, 2 * a, 2 * b);
}