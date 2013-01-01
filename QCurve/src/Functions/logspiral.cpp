#include "logspiral.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

LogarithmicSpiral::LogarithmicSpiral(double a, double x0, double y0)
{
  m_name = "Logarithmic Spiral";
  m_param = Parameter(0, 4 * PI, "t");

  Variable var("a", a);
  var.setColor(QColor(255, 255, 0));
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  initDimension();
}

LogarithmicSpiral::LogarithmicSpiral(const LogarithmicSpiral& other)
{ *this = other; }

Function* LogarithmicSpiral::clone() const
{ return new LogarithmicSpiral(getVariable("a"), getVariable("x0"), getVariable("y0")); }

QString LogarithmicSpiral::toParametricFormula() const
{
  static QString genFormula = QString("<math> <semantics> <mrow> <mi>x</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow>  <mo stretchy=\"false\">=</mo>  </mrow> <mi>k</mi> <msup> <mi>e</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mrow> <mi>a</mi> <mo stretchy=\"false\">&middot;</mo> <mi>t</mi> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> </mrow> </msup> <mi>cos</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow>  <mi>,</mi>  <mi>y</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow>  <mo stretchy=\"false\">=</mo>  </mrow> <mi>k</mi> <msup> <mi>e</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mrow> <mi>a</mi> <mo stretchy=\"false\">&middot;</mo> <mi>t</mi> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> </mrow> </msup> <mi>sin</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow>  <mi>,</mi>  <mrow> <mi>a</mi> <mo stretchy=\"false\">&gt;</mo> <mn>0</mn> </mrow>  <mi>,</mi>  <mi>a</mi> <mi>,</mi> <mi>t</mi> <mo stretchy=\"false\">&isin;</mo> <mo stretchy=\"false\">R</mo> </mrow></semantics> </math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(QString::number(var.value()));
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

Point3D LogarithmicSpiral::calculatePoint(double t) const
{
  double a = getVariable("a");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  double powat = pow(a, t);

  return Point3D(x0 + powat * cos(t), y0 + powat * sin(t), 0);
}

void LogarithmicSpiral::initDimension()
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  double h = pow(a, m_param.to()) * sin(m_param.to());
  double w = pow(a, m_param.to()) * cos(m_param.to());

  if (w < h) { w = h; }

  m_dimension = QRectF(-w + x0, -w + y0 , w * 2, w * 2);
}
