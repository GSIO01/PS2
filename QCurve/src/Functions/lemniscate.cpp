#include "lemniscate.h"

#include "Primitives/GraphicalPoint"
#include "Primitives/GraphicalLine"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Lemniscate::Lemniscate(double a, double x0, double y0)
{
  init();

  m_name = QCoreApplication::translate("Lemniscate", "Lemniscate");
  m_param = Parameter(0, 2*PI, "t");
  m_param.interval().setLowerEnd(0, true);
  m_param.interval().setUpperEnd(2 * PI, true);

  Variable var("a", a);
  var.interval().setLowerEnd(0);
  var.setColor(QColor(255, 128, 0));
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  initDimension();
  updatePoints();
}

Lemniscate::Lemniscate(const Lemniscate& other)
{ *this = other; }

Function* Lemniscate::clone() const
{ return new Lemniscate(getVariable("a"), getVariable("x0"), getVariable("y0")); }


QString Lemniscate::toParametricFormula() const
{
  static QString genFormula = QString("<math> <mrow> <mi>x</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow>  <mo stretchy=\"false\">=</mo>  </mrow> <mi>x0</mi> <mo>+</mo> <mi>a</mi> <mrow> <msqrt> <mrow> <mrow> <mn>2</mn> <mo stretchy=\"false\">&middot;</mo> <mi>cos</mi> </mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mn>2t</mn> </mrow> <mo stretchy=\"false\">)</mo> </mrow> </mrow> </msqrt> <mo stretchy=\"false\">&middot;</mo> <mi>cos</mi> </mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> " \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>y</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow>  <mo stretchy=\"false\">=</mo>  </mrow> <mi>y0</mi> <mo>+</mo> <mi>a</mi> <mrow> <msqrt> <mrow> <mrow> <mn>2</mn> <mo stretchy=\"false\">&middot;</mo> <mi>cos</mi> </mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mn>2t</mn> </mrow> <mo stretchy=\"false\">)</mo> </mrow> </mrow> </msqrt> <mo stretchy=\"false\">&middot;</mo> <mi>sin</mi> </mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> " \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mrow> <mrow> <mn>0</mn> <mo stretchy=\"false\">&leq;</mo> <mi>t</mi> </mrow> <mo stretchy=\"false\">&lt;</mo> <mn>2</mn> </mrow> <mo stretchy=\"false\">&pi;</mo> </mrow> </math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), var.formula()); }

  return curFormula;
}

Point3D Lemniscate::calculatePoint(double t) const
{
  double a = getVariable("a");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  double tmp = a * sqrt(2 * cos(2 * t));
  double x = x0 + (tmp * cos(t));
  double y = y0 + (tmp * sin(t));

  if (x != x) { x = x0; }
  if (y != y) { y = y0; }

  return Point3D(x, y, 0);
}

void Lemniscate::initDimension()
{
  double a = getVariable("a");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  m_dimension = QRectF(-2 * a + x0, -a + y0, 4 * a, 2 * a);
}

void Lemniscate::updatePoints(const QString& name, double value)
{
  Q_UNUSED(value);

  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  Point3D F1(-a,y0,0);
  Point3D F2(a,y0,0);

  if(name.isNull())
  {
    QString descl = QCoreApplication::translate("Lemniscate", "The left focus point.");
    QString descr = QCoreApplication::translate("Lemniscate", "The rigth focus point.");

    GraphicalPoint* p = new GraphicalPoint(Point3D(x0, y0), "P(x0,y0)");
    p->setColor(QColor(0, 200, 0));
    m_helper.append(p);

    p = new GraphicalPoint(F1, "F1", descl);
    p->setColor(QColor(255, 128, 0));
    m_helper.append(p);

    p = new GraphicalPoint(F2, "F2", descr);
    p->setColor(QColor(255, 128, 0));
    m_helper.append(p);
  }
  else
  {
    ((GraphicalPoint*)getHelperItem("F1"))->setPoint(Point3D(x0, y0));
    ((GraphicalPoint*)getHelperItem("F1"))->setPoint(F1);
    ((GraphicalPoint*)getHelperItem("F2"))->setPoint(F2);
  }
}
