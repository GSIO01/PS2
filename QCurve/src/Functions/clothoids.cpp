#include "clothoids.h"

#include <math.h>

Clothoids::Clothoids(double a,double n, double x0, double y0)
{
  m_name = QCoreApplication::translate("Clothoids", "Clothoids");
  m_param = Parameter(-9.42, 9.42, "t");

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  Variable var("a");
  var.setColor(QColor(255, 255, 0));
  var.interval().setLowerEnd(0);
  var.setValue(a);
  setVariable(var);

  var = Variable("n");
  var.setColor(QColor(0, 255, 255));
  var.interval().setLowerEnd(0);
  var.setValue(n);
  setVariable(var);

  initDimension();
}

Clothoids::Clothoids(const Clothoids& other)
{ *this = other; }

Function* Clothoids::clone() const
{ return new Clothoids(getVariable("a"), getVariable("n"), getVariable("x0"), getVariable("y0")); }

QString Clothoids::toParametricFormula() const
{
  static QString genFormula = QString("<math>x(t)=<mo>&Integral;</mo>, y(t)=</math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(var.name());
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

Point3D Clothoids::calculatePoint(double t) const
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  double n = getVariable("n");
  double h = t / n;
  double r1, r2;

  double x = 0, y = 0;
  for(int i = 0; i <= n; i++)
  {
    r1 = pow(((i + 0.5) * h), 2);
    r2 = pow(2 * a, 2);
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
