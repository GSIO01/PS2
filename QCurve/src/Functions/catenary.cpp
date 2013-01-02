#include "catenary.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Catenary::Catenary(double a, double x0, double y0)
{
  m_name = "Catenary";
  m_param = Parameter(-1, 1, "t");

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  Variable var("a", a);
  var.setColor(QColor(255, 255, 0));
  setVariable(var);

  initDimension();
}

Catenary::Catenary(const Catenary& other)
{ *this = other; }

Function* Catenary::clone() const
{ return new Catenary(getVariable("a"), getVariable("x0"), getVariable("y0")); }

QString Catenary::toParametricFormula() const
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

Point3D Catenary::calculatePoint(double t) const
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  return Point3D(x0 + t, y0 + a * cosh(t / a), 0);
}

void Catenary::initDimension()
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  double w = m_param.to() - m_param.from();
  double h = a * cosh(0);

  m_dimension = QRectF(m_param.from() + x0, a + y0, w, h);
}
