#include "hyperbola.h"

#include <QtCore/qmath.h> //TODO

#include "Primitives/GraphicalPoint"

Hyperbola::Hyperbola(double a, double b, double x0, double y0)
{
  init();

  m_calculations[1] = static_cast<Point3D(Function::*)(double)const>(&Hyperbola::calculatePoint2);

  m_name = QCoreApplication::translate("Hyperbola", "Hyperbola");
  m_param = Parameter(-1.5, 1.5, "t");

  Variable var("a", a);
  var.setColor(QColor(255, 128, 0));
  setVariable(var);

  var = Variable("b", b);
  var.setColor(QColor(0, 128, 255));
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  initDimension();
  updatePoints();
}

Hyperbola::Hyperbola(const Hyperbola& other)
{ *this = other; }

Function* Hyperbola::clone() const
{ return new Hyperbola(getVariable("a"), getVariable("b"), getVariable("x0"), getVariable("y0")); }

QString Hyperbola::toParametricFormula() const
{
  static QString genFormula = QString("<math><mi>x</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mo>=</mo> <mi>x0</mi><mo>+</mo> <mi>a</mi> <mo>&middot;</mo> <mi>cosh</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo>"\
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>"\
    "<mi>y</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo> <mo>=</mo> <mi>y0</mi><mo>+</mo> <mi>b</mi> <mo>&middot;</mo> <mi>sinh</mi> <mo>(</mo> <mi>t</mi> <mo>)</mo> "\
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>"\
    "<mi>t</mi> <mo>&isin;</mo> <mo>R</mo></math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), var.formula()); }

  return curFormula;
}

Point3D Hyperbola::calculatePoint(double t) const
{
  double a = getVariable("a");
  double b = getVariable("b");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  return Point3D(x0 + a * cosh(t), y0 + b * sinh(t));
}

Point3D Hyperbola::calculatePoint2(double t) const
{
  double a = getVariable("a");
  double b = getVariable("b");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  return Point3D(x0 - a * cosh(t), y0 + b * sinh(t));
}

void Hyperbola::initDimension()
{
  double x0 = getVariable("x0");
  double a = getVariable("a");
  double b = getVariable("b");
  double y0 = getVariable("y0");

  double t = (abs(m_param.to()) > abs(m_param.from())) ? m_param.to() : m_param.from();
  double w = a * cosh(t);
  double h0 = b * sinh(m_param.from());
  double h = b * sinh(m_param.to()) - h0;

  m_dimension = QRectF(x0 - w/2, h0 + y0, w, h);
}

void Hyperbola::updatePoints(const QString& name, double value)
{
  Q_UNUSED(value);

  double x0 = getVariable("x0");
  double a = getVariable("a");
  double b = getVariable("b");
  double y0 = getVariable("y0");

  Point3D f1 = Point3D(x0 -sqrt(pow(a, 2) + pow(b, 2)),  y0, 0);
  Point3D f2 = Point3D(x0 + sqrt(pow(a, 2) + pow(b, 2)), y0, 0);

  if (name.isEmpty())
  {
    Primitive* item = new GraphicalPoint(f1, "F1", QCoreApplication::translate("Hyperbola", "Left focus point."));
    m_helper.append(item);

    item = new GraphicalPoint(f2, "F2", QCoreApplication::translate("Hyperbola", "Right focus point."));
    m_helper.append(item);

    item = new GraphicalPoint(Point3D(x0 + a, y0), "a", QCoreApplication::translate("Hyperbola", "Right vertex."));
    item->setColor(m_variables.at(2).color());
    m_helper.append(item);

    item = new GraphicalPoint(Point3D(x0 - a, y0), "-a", QCoreApplication::translate("Hyperbola", "Left vertex."));
    item->setColor(m_variables.at(2).color());
    m_helper.append(item);

    item = new GraphicalPoint(Point3D(x0, y0), "P(x0,y0)");
    item->setColor(QColor(0, 200, 0));
    m_helper.append(item);
  }
  else
  {
    ((GraphicalPoint*)getHelperItem("F1"))->setPoint(Point3D(f1));
    ((GraphicalPoint*)getHelperItem("F2"))->setPoint(Point3D(f2));
    ((GraphicalPoint*)getHelperItem("a"))->setPoint(Point3D(x0 + a, y0));
    ((GraphicalPoint*)getHelperItem("-a"))->setPoint(Point3D(x0 - a, y0));
    ((GraphicalPoint*)getHelperItem("P(x0,y0)"))->setPoint(Point3D(x0, y0));
  }
}