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

#include "archspiral.h"

#include "Primitives/GraphicalPoint"
#include "Primitives/GraphicalLine"

#include <QtCore/QDebug>

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

ArchimedeanSpiral::ArchimedeanSpiral(double x0, double y0, double a)
{
  init();

  m_name = QCoreApplication::translate("ArchimedeanSpiral", "Archimedean Spiral");
  m_param = Parameter(0, 3.99, "t");
  m_param.interval().setLowerEnd(0, true);

  Variable var("a", a);
  var.interval().setLowerEnd(0);
  var.setColor(QColor(255, 128, 0));
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  initDimension();
  updatePoints();
}

ArchimedeanSpiral::ArchimedeanSpiral(const ArchimedeanSpiral& other)
{ *this = other; }

Function* ArchimedeanSpiral::clone() const
{ return new ArchimedeanSpiral(getVariable("x0"), getVariable("y0"), getVariable("a")); }

QString ArchimedeanSpiral::toParametricFormula() const
{
  static QString genFormula = QString("<math><apply><mi>x</mi><mo>(</mo><mi>t</mi><mo>)</mo><mo>=</mo><mi>x0</mi><mo>+</mo><mi>a</mi><mo>&middot;</mo><mi>t</mi><mo>&middot;</mo><mi>cos</mi><mo>(</mo><mi>2</mi><mi>&pi;</mi><mo>&middot;</mo><mi>t</mi><mo>)</mo>" \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>y</mi><mo>(</mo><mi>t</mi><mo>)</mo><mo>=</mo><mi>y0</mi><mo>+</mo><mi>a</mi><mo>&middot;</mo><mi>t</mi><mo>&middot;</mo><mi>sin</mi><mo>(</mo><mi>2</mi><mi>&pi;</mi><mo>&middot;</mo><mi>t</mi><mo>)</mo>" \
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
    "<mi>t</mi><mo>&geq;</mo><mn>0</mn>" \
    ",<mo>&InvisibleTimes;</mo>" \
    "<mi>t</mi><mo stretchy=\"false\">&isin;</mo><mo>R</mo></apply></math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  { curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), var.formula()); }

  return curFormula;
}

Point3D ArchimedeanSpiral::calculatePoint(double t) const
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double  a = getVariable("a");

  Point3D p(x0 + a * t * cos(2 * PI * t), y0 + a * t * sin(2 * PI * t));
  return p;
}

void ArchimedeanSpiral::initDimension()
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double  a = getVariable("a");

  double w = a * m_param.to() * cos(2 * PI * m_param.to());
  double h = a * m_param.to() * sin(2 * PI * m_param.to());

  if (w < h) { w = h; }

  m_dimension = QRectF(-w + x0, -w + y0, 2*w, 2*w);
}

void ArchimedeanSpiral::updatePoints(const QString& name, double value)
{
  Q_UNUSED(value);

  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");

  if(name.isNull())
  {
    Primitive* item = new GraphicalPoint(Point3D(x0, y0), "P(x0,y0)", QCoreApplication::translate("ArchimedeanSpiral", "The Center point of the circle."));
    item->setColor(QColor(0, 200, 0));
    m_helper.append(item);

    item = new GraphicalLine(Point3D(x0, y0, 0), Point3D(x0 + a, y0, 0), "2*&#x3c0;*a", m_variables.at(2).description());
    item->setColor(QColor(255, 128, 0));
    m_helper.append(item);
  }
  else
  {
    ((GraphicalPoint*)getHelperItem("P(x0,y0)"))->setPoint(Point3D(x0, y0));
    ((GraphicalLine*)getHelperItem("2*&#x3c0;*a"))->setStartPoint(Point3D(x0, y0));
    ((GraphicalLine*)getHelperItem("2*&#x3c0;*a"))->setEndPoint(Point3D(x0 + a, y0));
  }
}

