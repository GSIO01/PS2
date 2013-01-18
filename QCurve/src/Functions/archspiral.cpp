#include "archspiral.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

ArchimedeanSpiral::ArchimedeanSpiral(double x0, double y0)
{
  m_name = QCoreApplication::translate("ArchimedeanSpiral", "Archimedean Spiral");
  m_param = Parameter(0, 4 * PI, "t");

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  initDimension();
}

ArchimedeanSpiral::ArchimedeanSpiral(const ArchimedeanSpiral& other)
{ *this = other; }

Function* ArchimedeanSpiral::clone() const
{ return new ArchimedeanSpiral(getVariable("x0"), getVariable("y0")); }

QString ArchimedeanSpiral::toParametricFormula() const
{
  static QString genFormula = QString("<math><apply><mi>x</mi><mo>(</mo><mi>t</mi><mo>)</mo><mi/><mo>=</mo><mi/><mi>x0</mi><mo>+</mo><mi>t</mi><mi>cos</mi><mo>(</mo><mi>t</mi><mo>)</mo><mi/><mi>,</mi><mi/><mi>y</mi><mo>(</mo><mi>t</mi><mo>)</mo><mi/><mo>=</mo><mi/><mi>y0</mi><mo>+</mo><mi>t</mi><mi>sin</mi><mo>(</mo><mi>t</mi><mo>)</mo><mi/><mi>,</mi><mi/><mi>t</mi><mo>&gt;</mo><mn>0</mn><mi/><mi>,</mi><mi/><mi>t</mi><mo stretchy=\"false\">&isin;</mo><mo>R</mo></apply></math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(var.name());
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

Point3D ArchimedeanSpiral::calculatePoint(double t) const
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  return Point3D(x0 + t * cos(t), y0 + t * sin(t), 0);
}

void ArchimedeanSpiral::initDimension()
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  double w = m_param.to() * cos(m_param.to());
  double h = m_param.to() * sin(m_param.to());

  if (w < h) { w = h; }

  m_dimension = QRectF(-w + x0, -w + y0, 2 * w, 2 * w);
}
