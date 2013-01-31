/*
 * (C) Copyright 2012-2013 QCurve Team
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser General Public License
 * (LGPL) version 2.1 which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl-2.1.html
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 */

#include "logspiral.h"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

#include <Primitives/GraphicalPoint>

LogarithmicSpiral::LogarithmicSpiral(double a, double k, double x0, double y0)
{
  init();

  m_name = QCoreApplication::translate("LogarithmicSpiral", "Logarithmic Spiral");
  m_param = Parameter(0, 3.99, "t");
  m_param.interval().setLowerEnd(0, true);

  Variable var("a", a);
  var.interval().setLowerEnd(0);
  var.setColor(QColor(255, 128, 0));
  setVariable(var);

  var = Variable("k", k);
  var.interval().setLowerEnd(0);
  var.setColor(QColor(0, 128, 255));
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  initDimension();
  updatePoints();
}

LogarithmicSpiral::LogarithmicSpiral(const LogarithmicSpiral& other)
{ *this = other; }

Function* LogarithmicSpiral::clone() const
{ return new LogarithmicSpiral(getVariable("a"), getVariable("k"), getVariable("x0"), getVariable("y0")); }

QString LogarithmicSpiral::toParametricFormula() const
{
  static QString genFormula = QString("<math> <mrow> <mi>x</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow> <mo stretchy=\"false\">=</mo> </mrow> <mi>x0</mi> <mo>+</mo> <mi>a</mi> <mo>&middot;</mo> <msup> <mi>e</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mrow> <mi>k</mi> <mo stretchy=\"false\">&middot;</mo> <mi>t</mi> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> </mrow> </msup> <mi>cos</mi> <mrow> <mo stretchy=\"false\">(</mo> <mi>2</mi> <mi>&pi;</mi> <mo>&middot;</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow>" \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>y</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow> <mo stretchy=\"false\">=</mo> </mrow> <mi>y0</mi> <mo>+</mo> <mi>a</mi> <mo>&middot;</mo> <msup> <mi>e</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mrow> <mi>k</mi> <mo stretchy=\"false\">&middot;</mo> <mi>t</mi> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> </mrow> </msup> <mi>sin</mi> <mrow> <mo stretchy=\"false\">(</mo> <mi>2</mi> <mi>&pi;</mi> <mo>&middot;</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow>" \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>a</mi> <mi>,</mi> <mrow> <mi>k</mi> <mo stretchy=\"false\">&gt;</mo> <mn>0</mn> </mrow>" \
    "<mo>&InvisibleTimes;</mo>" \
    "<mi>a</mi> <mi>,</mi> <mi>k</mi> <mi>,</mi> <mi>t</mi> <mo stretchy=\"false\">&isin;</mo> <mo stretchy=\"false\">R</mo> </mrow> </math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), var.formula()); }

  return curFormula;
}

Point3D LogarithmicSpiral::calculatePoint(double t) const
{
  double a = getVariable("a");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double k = getVariable("k");

  return Point3D(x0 + a * exp(k * t) * cos(2 * PI * t), y0 + a * exp(k * t) * sin(2 * PI * t), 0);
}

void LogarithmicSpiral::initDimension()
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");
  double k = getVariable("k");

  double h = a * exp(k * m_param.to()) * sin(2 * PI * m_param.to());
  double w = a * exp(k * m_param.to()) * cos(2 * PI * m_param.to());

  if (w < h) { w = h; }

  m_dimension = QRectF(-w + x0, -w + y0 , w * 2, w * 2);
}

void LogarithmicSpiral::updatePoints(const QString& name, double value)
{
  Q_UNUSED(value);

  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  if (name.isEmpty())
  {
    Primitive* item = new GraphicalPoint(Point3D(x0, y0), "P(x0,y0)");
    item->setColor(QColor(0, 200, 0));
    m_helper.append(item);
  }
  else
  {
    ((GraphicalPoint*)getHelperItem("P(x0,y0)"))->setPoint(Point3D(x0, y0));
  }
}
