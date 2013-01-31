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

#include "catenary.h"

#include "Primitives/GraphicalPoint"
#include "Primitives/GraphicalCircle"
#include "Primitives/GraphicalLine"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Catenary::Catenary(double a, double x0, double y0)
{
  init();

  m_name = QCoreApplication::translate("Catenary", "Catenary");
  m_param = Parameter(-2, 2, "t");

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  Variable var("a", a);
  var.interval().setLowerEnd(0);
  var.setDescription(QCoreApplication::translate("Catenary", "The parameter a \
    describes the height above the reference point and \
    the distans from the tangent to the base-point."));
  var.setColor(QColor(255, 128, 0));
  setVariable(var);

  updatePoints();
  initDimension();
}

Catenary::Catenary(const Catenary& other)
{ *this = other; }

Function* Catenary::clone() const
{ return new Catenary(getVariable("a"), getVariable("x0"), getVariable("y0")); }

QString Catenary::toParametricFormula() const
{
  static QString genFormula = QString("<math><mrow> <mi>x</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mo stretchy=\"false\">=</mo> <mrow> <mi>x0</mi> <mo stretchy=\"false\">+</mo> <mi>t</mi> </mrow> </mrow>" \
  "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
  "<mi>y</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mo stretchy=\"false\">=</mo> <mrow> <mi>y0</mi> <mo stretchy=\"false\">+</mo> <mrow> <mi>a</mi> <mo>&middot;</mo> <mi>cosh</mi> </mrow> </mrow>  <mrow> <mo stretchy=\"false\">(</mo> <mrow>  <mi>t</mi> <mo stretchy=\"false\">/</mo> <mi>a</mi> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow>" \
  "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>" \
  "<mrow> <mi>a</mi> <mo stretchy=\"false\">&gt;</mo> <mn>0</mn> </mrow> </mrow></math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(var.name());
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

Point3D Catenary::calculatePoint(double t) const
{
    double x0 = getVariable("x0");
    double y0 = getVariable("y0");
    double a = getVariable("a");

    double x = x0 + t;
    double y = y0 + a * cosh(t / a);

    Point3D intersectPoint = calculateIntersectionPoint(t);
    Point3D curvePoint     = Point3D(x, y, 0);
    Point3D basePoint      = Point3D(x, y0, 0);

    GraphicalLine *tangent = (GraphicalLine *)getHelperItem("Tangent");
    GraphicalLine *normal  = (GraphicalLine *)getHelperItem("Normal");
    GraphicalLine *height  = (GraphicalLine *)getHelperItem("Baseline");
    tangent->setStartPoint(intersectPoint);
    tangent->setEndPoint(curvePoint);

    normal->setStartPoint(basePoint);
    normal->setEndPoint(intersectPoint);

    height->setStartPoint(basePoint);
    height->setEndPoint(curvePoint);

    return curvePoint;
}

void Catenary::initDimension()
{
    double x0 = getVariable("x0");
    double y0 = getVariable("y0");
    double a = getVariable("a");

    double absFromT = m_param.from() < 0 ? m_param.from() * -1 : m_param.from();
    double absToT   = m_param.to() < 0 ? m_param.to() * -1 : m_param.to();
    double maxT     = absFromT > absToT ? absFromT : absToT;

    double w = m_param.to() - m_param.from();
    double h = a * cosh(maxT / a);

    m_dimension = QRectF(m_param.from() + x0, y0, w, h);
}

void Catenary::updatePoints(const QString& name, double value)
{
    Q_UNUSED(value);

    double y0 = getVariable("y0");
    double x0 = getVariable("x0");
    double a  = getVariable("a");

    double t = m_param.to();

    double x = x0 + t;
    double y = y0 + a * cosh(t / a);

    Point3D refPoint          = Point3D(x0, y0, 0);
    Point3D curvePoint        = Point3D(x, y, 0);
    Point3D intersectionPoint = calculateIntersectionPoint(t);

    if (name.isNull()) // first call -> init
    {
      m_helper.clear();

      GraphicalPoint *graphRefPoint = new GraphicalPoint(refPoint, "(x0,y0)",
        QCoreApplication::translate("Catenary", "Reference point of the Catenary line"));
      graphRefPoint->setColor(QColor("green"));

      GraphicalLine *tangent = new GraphicalLine(Point3D(x, y, 0), intersectionPoint, "Tangent");
      tangent->setIsAnimated(true);
      tangent->setColor(QColor("blue"));

      GraphicalLine *normal = new GraphicalLine(curvePoint, intersectionPoint, "Normal");
      normal->setIsAnimated(true);
      normal->setColor(QColor("red"));

      GraphicalLine *baseLine = new GraphicalLine(Point3D(x, y0, 0), intersectionPoint, "Baseline");
      baseLine->setIsAnimated(true);
      baseLine->setColor(QColor("green"));

      GraphicalLine *aLine = new GraphicalLine(Point3D(x0, y0), Point3D(x0, y0 + a, 0),
        "Parameter a", m_variables.at(2).description());
      aLine->setColor(m_variables.at(2).color());

      m_helper.append(graphRefPoint);
      m_helper.append(normal);
      m_helper.append(tangent);
      m_helper.append(baseLine);
      m_helper.append(aLine);
    }
    else //update helper items
    {
        ((GraphicalPoint*)getHelperItem("(x0,y0)"))->setPoint(refPoint);
      GraphicalLine *aLine = (GraphicalLine *)getHelperItem("Parameter a");
      aLine->setStartPoint(Point3D(x0, y0));
      aLine->setEndPoint(Point3D(x0, y0 + a, 0));
    }
}

Point3D Catenary::calculateIntersectionPoint(double t) const
{
    Point3D intersectionPoint;

    double x0 = getVariable("x0");
    double y0 = getVariable("y0");
    double a = getVariable("a");

    double x = x0 + t;
    double y = y0 + a * cosh(t / a);

    double alpha  = acos(a / (y-y0));
    double deltaX = a * sin(alpha);
    double deltaY = a * cos(alpha);

    if (a > 0)
    {
      if (t > 0)
      { intersectionPoint  = Point3D(x - deltaX, y0 + deltaY); }
      else { intersectionPoint  = Point3D(x + deltaX, y0 + deltaY); }
    }
    else
    {
      if (t > 0)
      { intersectionPoint  = Point3D(x + deltaX, y0 + deltaY); }
      else { intersectionPoint  = Point3D(x - deltaX, y0 + deltaY); }
    }

    return intersectionPoint;
}
