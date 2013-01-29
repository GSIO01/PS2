#include "ellipse.h"

#include "Primitives/GraphicalPoint"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Ellipse::Ellipse(double a, double b, double x0, double y0)
{
  init();

  m_param = Parameter(0, 2 * PI, "t");
  m_name = QCoreApplication::translate("Ellipse", "Ellipse");
  m_param.interval().setLowerEnd(0, true);
  m_param.interval().setUpperEnd(2 * PI, true);

  Variable var("a", a);
  var.setDescription(QCoreApplication::translate("Ellipse",
    "The radius along the x-axis. The x-axis is the major radius [a > b] or the minor radius."));
  var.setColor(QColor(255, 128, 0));
  var.interval().setLowerEnd(0);
  setVariable(var);

  var = Variable("b", b);
  var.setDescription(QCoreApplication::translate("Ellipse",
    "The radius along the y-axis. The y-axis is the major radius [b > a] or the minor radius."));
  var.setColor(QColor(0, 128, 255));
  var.interval().setLowerEnd(0);
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  updatePoints();
  initDimension();
}

Ellipse::Ellipse(const Ellipse& other)
{ *this = other; }

Function* Ellipse::clone() const
{ return new Ellipse(*this); }

QString Ellipse::toParametricFormula() const
{
  static QString genFormula = QString("<math>x(t)<mo>=</mo><mi>x0</mi><mo>+</mo><mi>a</mi><mo>&middot;</mo><mi>cos</mi>(<mi>t</mi>)" \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "y(t)<mo>=</mo><mi>y0</mi><mo>+</mo><mi>b</mi><mo>&middot;</mo><mi>sin</mi>(<mi>t</mi>)</math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), var.formula()); }

  return curFormula;
}

void Ellipse::updatePoints(const QString& name, double value)
{
  Q_UNUSED(value);

  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");
  double b = getVariable("b");

  Point3D f1; Point3D f2;
  if (b < a)
  {
    double f = sqrt(pow(a, 2) - pow(b, 2));
    f1 = Point3D(-f + x0, y0, 0);
    f2 = Point3D( f + x0, y0, 0);
  }
  else
  {
    double f = sqrt(pow(b, 2) - pow(a, 2));
    f1 = Point3D(x0, -f + y0, 0);
    f2 = Point3D(x0,  f + y0, 0);
  }

  if (name.isNull()) // first call -> init
  {
    m_helper.clear();
    QString desc = QCoreApplication::translate("Ellipse", "One focus point of the ellipse. \
    The foci always lie on the major (longest) axis and \
    are equidistant from the center point.");

    GraphicalPoint* p = new GraphicalPoint(Point3D(x0, y0), "M(x0,y0)",
      QCoreApplication::translate("Ellipse", "The center point of the ellipse."));
    p->setColor(QColor(0, 200, 0));
    m_helper.append(p);

    m_helper.append(new GraphicalPoint(f1, "F1", desc));
    m_helper.append(new GraphicalPoint(f2, "F2", desc));

    p = new GraphicalPoint(Point3D( a + x0, y0, 0), "a", m_variables.at(2).description());
    p->setColor(m_variables.at(2).color());
    m_helper.append(p);

    p = new GraphicalPoint(Point3D(-a + x0, y0, 0), "-a", m_variables.at(2).description());
    p->setColor(m_variables.at(2).color());
    m_helper.append(p);

    p = new GraphicalPoint(Point3D(x0,  b + y0, 0), "b", m_variables.at(3).description());
    p->setColor(m_variables.at(3).color());
    m_helper.append(p);

    p = new GraphicalPoint(Point3D(x0, -b + y0, 0), "-b", m_variables.at(3).description());
    p->setColor(m_variables.at(3).color());
    m_helper.append(p);
  }
  else //update helper items
  {
    ((GraphicalPoint*)getHelperItem("M(x0,y0)"))->setPoint(Point3D(x0, y0));
    ((GraphicalPoint*)getHelperItem("F1"))->setPoint(f1);
    ((GraphicalPoint*)getHelperItem("F2"))->setPoint(f2);
    ((GraphicalPoint*)getHelperItem("a"))->setPoint(Point3D( a + x0, y0, 0));
    ((GraphicalPoint*)getHelperItem("-a"))->setPoint(Point3D(-a + x0, y0, 0));
    ((GraphicalPoint*)getHelperItem("b"))->setPoint(Point3D(x0,  b + y0, 0));
    ((GraphicalPoint*)getHelperItem("-b"))->setPoint(Point3D(x0, -b + y0, 0));
  }
}

Point3D Ellipse::calculatePoint(double t) const
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");
  double b = getVariable("b");

  return Point3D(x0 + a * cos(t), y0 + b * sin(t), 0);
}

void Ellipse::initDimension()
{
  double a = getVariable("a");
  double b = getVariable("b");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  m_dimension = QRectF(-a + x0, -b + y0, 2 * a, 2 * b);
}