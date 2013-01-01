#include "helix.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Helix::Helix(double r, double h, double x0, double y0, double z0)
{
  m_is2Dimensional = false;

  m_name = "Helix";
  m_param = Parameter(0, PI * 2, "t"); //TODO

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  Variable var("z0", z0);
  var.setColor(QColor(255, 0, 0));
  var.setFormula("<math><mrow><msub><mi color=\"#FF0000\">z</mi><mr color=\"#FF0000\">0</mr></msub></mrow></math>");
  var.setDescription("Moves the function on the z-axis");
  setVariable(var);

  var = Variable("r");
  var.setColor(QColor(255, 255, 0));
  var.interval().setLowerEnd(0);
  var.setValue(r);
  setVariable(var);

  var = Variable("h");
  var.setColor(QColor(0, 255, 255));
  var.interval().setLowerEnd(0);
  var.setValue(h);
  setVariable(var);

  initDimension();
}

Helix::Helix(const Helix& other)
{ *this = other; }

Function* Helix::clone() const
{ return new Helix(getVariable("r"), getVariable("h"), getVariable("x0"), getVariable("y0"), getVariable("z0")); }

QString Helix::toParametricFormula() const
{
  static QString genFormula = QString("<math></math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(QString::number(var.value()));
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

Point3D Helix::calculatePoint(double t) const
{
  double r = getVariable("r");
  double h = getVariable("h");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double z0 = getVariable("z0");

  return Point3D(x0 + r * cos(t), y0 + r * sin(t), z0 + h * t);
}

void Helix::initDimension()
{
  double r = getVariable("r");
  double h = getVariable("h");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  m_dimension = QRectF(-r + x0, -r + y0, 2 * r, 2 * r);
}
