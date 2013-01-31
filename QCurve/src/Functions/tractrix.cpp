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

#include "tractrix.h"

#include <QtCore/qmath.h> //TODO

#include <limits>

#define PI 3.141592653589793

Tractrix::Tractrix(double a, double x0, double y0)
{
  init();

  m_name = QCoreApplication::translate("Tractrix", "Tractrix");
  m_param = Parameter(0, PI, "t");
  m_param.interval().setLowerEnd(0);
  m_param.interval().setUpperEnd(PI, true);

  Variable var("a", a);
  var.interval().setLowerEnd(0);
  var.setColor(QColor(255, 128, 0));
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  initDimension();
}

Tractrix::Tractrix(const Tractrix& other)
{ *this = other; }

Function* Tractrix::clone() const
{ return new Tractrix(getVariable("a"), getVariable("x0"), getVariable("y0")); }

QString Tractrix::toParametricFormula() const
{
  static QString genFormula = QString("<math><mrow> <mi>x</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow>  <mo stretchy=\"false\">=</mo> <mi>x0</mi><mo>+</mo> <mrow>  <mo stretchy=\"false\">-</mo> <mi>a</mi><mo>&middot;</mo> </mrow> </mrow> <mi>cos</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mo stretchy=\"false\">-</mo> <mi>a</mi><mo>&middot;</mo> </mrow> <mi>ln</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>tan</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mfrac> <mrow> <mi>t</mi> </mrow> <mrow> <mn>2</mn> </mrow> </mfrac> </mrow> <mo stretchy=\"false\">)</mo> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> " \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>y</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow>  <mo stretchy=\"false\">=</mo> <mi>y0</mi><mo>+</mo> </mrow> <mi>a</mi><mo>&middot;</mo> <mi>sin</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow>" \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>t</mi> <mo stretchy=\"false\">&isin;</mo> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mn>0,</mn> <mo stretchy=\"false\">&pi;</mo> </mrow> <mo stretchy=\"false\">)</mo> </mrow> </mrow></math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), var.formula()); }

  return curFormula;
}

Point3D Tractrix::calculatePoint(double t) const
{
  double a = getVariable("a");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  double x = x0 + (-a * cos(t) - a * log(tan(t / 2)));
  if (x > std::numeric_limits<qreal>::max()) { x =  m_dimension.right();  }
  else if (x < -std::numeric_limits<qreal>::max()) { x = m_dimension.left(); }

  return Point3D(x, y0 + a * sin(t), 0);
}

void Tractrix::initDimension() //TODO FIXME
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  double w = -a * cos(3.14) - a * log(tan(3.14 / 2));

  m_dimension = QRectF(w + x0, y0, -w * 2, a);
}