#include "helix.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Helix::Helix(double r, double h, double x0, double y0, double z0)
{
  init();

  m_is2Dimensional = false;

  m_name = QCoreApplication::translate("Helix", "Helix");
  m_param = Parameter(-PI * 2, PI * 2, "t"); //TODO

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  Variable var("z0", z0);
  var.setColor(QColor(255, 0, 0));
  var.setFormula("<math><mrow><msub><mi color=\"#FF0000\">z</mi><mr color=\"#FF0000\">0</mr></msub></mrow></math>");
  var.setDescription(QCoreApplication::translate("Helix", "Moves the function on the z-axis"));
  setVariable(var);

  var = Variable("r");
  var.setColor(QColor(255, 128, 0));
  var.interval().setLowerEnd(0);
  var.setValue(r);
  setVariable(var);

  var = Variable("h");
  var.setColor(QColor(0, 128, 255));
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
  static QString genFormula = QString("<math><mrow> <mi>x</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mo stretchy=\"false\">=</mo> <mrow> <mi>x0</mi> <mo stretchy=\"false\">+</mo> <mrow> <mi>r</mi> <mo stretchy=\"false\">&middot;</mo> <mi>cos</mi> </mrow> </mrow> </mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow>" \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>y</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mo stretchy=\"false\">=</mo> <mrow> <mi>y0</mi> <mo stretchy=\"false\">+</mo> <mrow> <mi>r</mi> <mo stretchy=\"false\">&middot;</mo> <mi>sin</mi> </mrow> </mrow> </mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow>" \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>z</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mo stretchy=\"false\">=</mo> <mrow> <mi>z0</mi> <mo stretchy=\"false\">+</mo> <mrow> <mi>h</mi> <mo stretchy=\"false\">&middot;</mo> <mi>t</mi> </mrow> </mrow> </mrow> </mrow>" \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>t</mi> <mo>&isin;</mo> <mi>R</mi></math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), var.formula()); }

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