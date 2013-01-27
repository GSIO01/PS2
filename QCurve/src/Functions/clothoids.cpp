#include "clothoids.h"

#include "Primitives/GraphicalPoint"
#include "Primitives/GraphicalLine"

#include <math.h>

#define PI 3.141592653589793

Clothoids::Clothoids(double a, double x0, double y0)
{
  init();

  m_name = QCoreApplication::translate("Clothoids", "Clothoids");
  m_param = Parameter(-6, 6, "t");

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  Variable var("a");
  var.setColor(QColor(255, 128, 0));
  var.setDescription(QCoreApplication::translate("Clothoids","Parameter of the clothoid"));
  var.interval().setLowerEnd(0.5);
  var.setValue(a);
  setVariable(var);

  updatePoints();
  initDimension();
}

Clothoids::Clothoids(const Clothoids& other)
{ *this = other; }

Function* Clothoids::clone() const
{ return new Clothoids(getVariable("a"), getVariable("x0"), getVariable("y0")); }

QString Clothoids::toParametricFormula() const
{
  static QString genFormula = QString("<math> <mrow> <mi>x</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow>  <mo stretchy=\"false\">=</mo> <mi>x0</mi><mo>+</mo>  </mrow> <mrow> <munderover> <mo stretchy=\"false\">&int;</mo> <mrow> <mn>0</mn> </mrow> <mrow> <mi>t</mi> </mrow> </munderover> <mi>cos</mi> </mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mfrac> <mrow> <msup> <mi>s</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> <mrow> <msup> <mn>2<mi>a</mi></mn> <mrow> <mn>2</mn> </mrow> </msup> </mrow> </mfrac> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mi mathvariant=\"italic\">ds</mi> " \
  "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
  "<mi>y</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow>  <mo stretchy=\"false\">=</mo> <mi>y0</mi><mo>+</mo>  </mrow> <mrow> <munderover> <mo stretchy=\"false\">&int;</mo> <mrow> <mn>0</mn> </mrow> <mrow> <mi>t</mi> </mrow> </munderover> <mi>sin</mi> </mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mfrac> <mrow> <msup> <mi>s</mi> <mrow> <mn>2</mn> </mrow> </msup> </mrow> <mrow> <msup> <mn>2<mi>a</mi></mn> <mrow> <mn>2</mn> </mrow> </msup> </mrow> </mfrac> </mrow> <mo stretchy=\"false\">)</mo> <mi mathvariant=\"italic\">ds</mi> </mrow> " \
  "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
  "<mrow> <mi>a</mi> <mo stretchy=\"false\">&gt;</mo> <mn>0</mn> </mrow> " \
  "<mtext>,&ThickSpace;&ThickSpace;</mtext>  <mi>a</mi> <mtext>,&ThickSpace;</mtext> <mi>t</mi> <mo stretchy=\"false\">&isin;</mo> <mo stretchy=\"false\">R</mo> </mrow></math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), var.formula()); }

  return curFormula;
}

void Clothoids::updatePoints(const QString& name, double value)
{
  Q_UNUSED(value);

  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

 // QString descXLabel1,descYLabel1,descXLabel2,descYLabel2;

  double p;
  Point3D P1,P2;

  p = ((a/2)*sqrt(PI));

  P1 = Point3D(x0+p,y0+p,0);
  P2 = Point3D(x0-p,y0-p,0);

  if(name.isNull())
  {
     m_helper.clear();
//asymptotic points
    m_helper.append(new GraphicalPoint(P1, "P1",QCoreApplication::translate("Clothoids", "Asymptotic Point")));
    m_helper.append(new GraphicalPoint(P2, "P2",QCoreApplication::translate("Clothoids", "Asymptotic Point")));
    m_helper.append(new GraphicalPoint(Point3D((x0+p), 0, 0), "P01"));
    m_helper.append(new GraphicalPoint(Point3D(0, (y0+p), 0), "P02"));
    m_helper.append(new GraphicalPoint(Point3D((x0-p), 0, 0), "P03"));
    m_helper.append(new GraphicalPoint(Point3D(0, (y0-p), 0), "P04"));


    Primitive* item = new GraphicalLine(Point3D((x0+p), 0, 0), Point3D(P1), "g1");
    item->setIsAnimated(false);
    m_helper.append(item);

    item = new GraphicalLine(Point3D(0, (y0+p), 0), Point3D(P1), "g2");
    item->setIsAnimated(false);
    m_helper.append(item);

    item = new GraphicalLine(Point3D((x0-p), 0, 0), Point3D(P2), "g3");
    item->setIsAnimated(false);
    m_helper.append(item);

    item = new GraphicalLine(Point3D(0, (y0-p), 0), Point3D(P2), "g4");
    item->setIsAnimated(false);
    m_helper.append(item);

  }
  else
  {
    ((GraphicalPoint*)getHelperItem("P1"))->setPoint(P1);
    ((GraphicalPoint*)getHelperItem("P2"))->setPoint(P2);

    ((GraphicalPoint*)getHelperItem("P01"))->setPoint(Point3D((x0+p), 0, 0));
    ((GraphicalPoint*)getHelperItem("P02"))->setPoint(Point3D(0, (y0+p), 0));
    ((GraphicalPoint*)getHelperItem("P03"))->setPoint(Point3D((x0-p), 0, 0));
    ((GraphicalPoint*)getHelperItem("P04"))->setPoint(Point3D(0, (y0-p), 0));

    ((GraphicalLine*)getHelperItem("g1"))->setStartPoint(Point3D((x0+p), 0, 0));
    ((GraphicalLine*)getHelperItem("g1"))->setEndPoint(P1);
    ((GraphicalLine*)getHelperItem("g2"))->setStartPoint(Point3D(0, (y0+p), 0));
    ((GraphicalLine*)getHelperItem("g2"))->setEndPoint(P1);

    ((GraphicalLine*)getHelperItem("g3"))->setStartPoint(Point3D((x0-p), 0, 0));
    ((GraphicalLine*)getHelperItem("g3"))->setEndPoint(P2);
    ((GraphicalLine*)getHelperItem("g4"))->setStartPoint(Point3D(0, (y0-p), 0));
    ((GraphicalLine*)getHelperItem("g4"))->setEndPoint(P2);
  }

}

Point3D Clothoids::calculatePoint(double t) const
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  double n = 100 *(abs(t)+1);
  double h = t / n;
  double r1;
  double r2 = 2 * pow(a, 2);
  double x  = 0;
  double y  = 0;

  for(int i = 0; i <= n; i++)
  {
    r1 = pow(((i + 0.5) * h), 2);
    x += cos(r1 / r2);
    y += sin(r1 / r2);
  }
  x = x * h + x0;
  y = y * h + y0;

  return Point3D(x, y, 0);
}

void Clothoids::initDimension()
{
  double a = 2 * getVariable("a");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  m_dimension = QRectF(-a + x0, -a + y0, 2 * a, 2 * a);
}
