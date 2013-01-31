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

#include "limacon.h"

#include "Primitives/GraphicalPoint"
#include "Primitives/GraphicalLine"
#include "Primitives/GraphicalCircle"

#include <QtCore/qmath.h> //TODO

#define PI 3.141592653589793

Limacon::Limacon(double a, double b, double x0, double y0)
{
  init();

  m_name = QCoreApplication::translate("Limacon", "Limacon");
  m_param = Parameter(0, 2 * PI, "t");
  m_param.interval().setLowerEnd(0, true);
  m_param.interval().setUpperEnd(2 * PI, true);

  Variable var("a", a);
  var.interval().setLowerEnd(0);
  var.setColor(QColor(255, 128, 0));
  setVariable(var);

  var = Variable("b", b);
  var.interval().setLowerEnd(0);
  var.setColor(QColor(0, 128, 255));
  setVariable(var);

  setVariable("x0", x0, false);
  setVariable("y0", y0, false);

  updatePoints();
  initDimension();
}

Limacon::Limacon(const Limacon& other)
{ *this = other; }

Function* Limacon::clone() const
{ return new Limacon(getVariable("a"), getVariable("b"), getVariable("x0"), getVariable("y0")); }

QString Limacon::toParametricFormula() const
{
  static QString genFormula = QString("<math> <mrow> <mi>x</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow> <mo stretchy=\"false\">=</mo> <mi>x0</mi><mo>+</mo> </mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mn>2</mn><mo>&middot;</mo><mi>a</mi> <mi>cos</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mo stretchy=\"false\">+</mo> <mi>t</mi> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mi>cos</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow>"\
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>"\
    "<mi>y</mi> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mrow> <mo stretchy=\"false\">=</mo> <mi>y0</mi><mo>+</mo> </mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mn>2</mn><mo>&middot;</mo><mi>a</mi> <mi>cos</mi> <mrow> <mrow> <mo stretchy=\"false\">(</mo> <mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mo stretchy=\"false\">+</mo> <mi>b</mi> </mrow> </mrow> <mo stretchy=\"false\">)</mo> </mrow> <mi>sin</mi> <mrow> <mo stretchy=\"false\">(</mo><mrow> <mi>t</mi> </mrow> <mo stretchy=\"false\">)</mo> </mrow> "\
    "<mo>&InvisibleTimes;</mo><mo>&InvisibleTimes;</mo>"\
    "<mi>t</mi> <mo stretchy=\"false\">&isin;</mo> <mo stretchy=\"false\">R</mo> </mrow></math>");

  QString curFormula = genFormula;
  foreach (const Variable& var, m_variables)
  {
    QString replace = QString("<mi color=\"%1\">%2</mi>").arg(var.color().name()).arg(var.name());
    curFormula.replace(QString("<mi>%1</mi>").arg(var.name()), replace);
  }

  return curFormula;
}

Point3D Limacon::calculatePoint(double t) const
{
  double a = getVariable("a");
  double b = getVariable("b");
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");

  double tmp = 2 * a * cos(t) + b;

  return Point3D(x0 + tmp * cos(t), y0 + tmp * sin(t), 0);
}

void Limacon::initDimension()
{
  double x0 = getVariable("x0");
  double y0 = getVariable("y0");
  double a = getVariable("a");
  double b = getVariable("b");

  double h = 2 * a + b * sin(0.3);

  m_dimension = QRectF(-a + x0, -h + y0, 4 * a, 2 * h);
}

void Limacon::updatePoints(const QString& name, double value)
{
    Q_UNUSED(value);

    double y0   = getVariable("y0");
    double x0   = getVariable("x0");
    double a    = getVariable("a");
    double b    = getVariable("b");

    double t = (m_param.to() - m_param.from()) / 12;
    double c = 2 * a * cos(t) + b;
    double x = x0 + (c * cos(t));
    double y = y0 + (c * sin(t));
    double m = (y - y0) / (x - x0);

    double deltaX = b / (sqrt(1 + pow(m, 2)));
           deltaX = m < 0 ? deltaX : -deltaX;
    double deltaY = deltaX * m;
    double dQ     = sqrt(pow(x + deltaX, 2) + pow(y + deltaY, 2));

    Point3D curvePoint = Point3D(x, y, 0);
    Point3D midPoint   = Point3D(x0 + a, y0, 0);
    Point3D refPoint   = Point3D(x0, y0, 0);
    Point3D pointPosB  = Point3D(x0, y0 + b, 0);
    Point3D pointNegB  = Point3D(x0, y0 - b, 0);
    Point3D pointQ     = Point3D(x + deltaX, y + deltaY, 0);
    Point3D pointP1    = Point3D(x + (2 * deltaX), y + (2 * deltaY), 0);
    Point3D pointH2    = Point3D(x - deltaX, y - deltaY, 0);
    Point3D pointH1;

    if (dQ > b) {
        pointH1 = Point3D(x0 + deltaX, y0 + deltaY, 0);
    } else {
        pointH1 = Point3D(x + (3 * deltaX), y0 + (3 * deltaY), 0);
    }

    GraphicalCircle *gCircle;
    GraphicalPoint  *gMidPoint;
    GraphicalPoint  *gRefPoint;
    GraphicalPoint  *gPointPosB;
    GraphicalPoint  *gPointNegB;
    GraphicalPoint  *gPointQ;
    GraphicalPoint  *gPointP2;
    GraphicalPoint  *gPointP1;
    GraphicalLine   *gLineB;
    GraphicalLine   *gLineA;
    GraphicalLine   *gHelpLine1;
    GraphicalLine   *gHelpLine2;

    if (name.isNull()) // first call -> init
    {
      m_helper.clear();

       QString desc = QCoreApplication::translate("Limacon", "The distance P1-Q = Q-P2 = b for P1 and P2 points of the limacon and Q a point of the circle with the radius a and the middle-point (x0+a,y0).");

      gCircle = new GraphicalCircle(midPoint, a, "Circle", desc);
      gCircle->setColor(QColor("gray"));

      gMidPoint = new GraphicalPoint(midPoint, "a", desc);
      gMidPoint->setColor(m_variables.at(2).color());

      gRefPoint = new GraphicalPoint(refPoint, "(x0,y0)");
      gRefPoint->setColor(QColor("green"));

      gPointPosB = new GraphicalPoint(pointPosB, "b");
      gPointPosB->setColor(m_variables.at(3).color());

      gPointNegB = new GraphicalPoint(pointNegB, "-b");
      gPointNegB->setColor(m_variables.at(3).color());

      gPointP1 = new GraphicalPoint(pointP1, "P1", desc);
      gPointP1->setColor("gray");

      gPointP2 = new GraphicalPoint(curvePoint, "P2", desc);
      gPointP2->setColor(QColor("gray"));

      gPointQ = new GraphicalPoint(pointQ, "Q", desc);
      gPointQ->setColor(QColor("gray"));

      gLineB = new GraphicalLine(pointP1, curvePoint, "2*b", desc);
      gLineB->setColor(m_variables.at(3).color());

      gLineA = new GraphicalLine(refPoint, midPoint, "Radius a", desc);
      gLineA->setColor(m_variables.at(2).color());

      gHelpLine1 = new GraphicalLine(pointH1, pointP1, "h1");
      gHelpLine1->setColor("gray");

      gHelpLine2 = new GraphicalLine(curvePoint, pointH2, "h2");
      gHelpLine2->setColor("gray");

      m_helper.append(gCircle);
      m_helper.append(gMidPoint);
      m_helper.append(gRefPoint);
      m_helper.append(gPointPosB);
      m_helper.append(gPointNegB);
      m_helper.append(gPointQ);
      m_helper.append(gPointP2);
      m_helper.append(gPointP1);
      m_helper.append(gLineB);
      m_helper.append(gLineA);
      m_helper.append(gHelpLine1);
      m_helper.append(gHelpLine2);
    }
    else //update helper items
    {
        gCircle    = (GraphicalCircle *) getHelperItem("Circle");
        gMidPoint  = (GraphicalPoint *) getHelperItem("a");
        gRefPoint  = (GraphicalPoint *) getHelperItem("(x0,y0)");
        gPointPosB = (GraphicalPoint *) getHelperItem("b");
        gPointNegB = (GraphicalPoint *) getHelperItem("-b");
        gPointQ    = (GraphicalPoint *) getHelperItem("Q");
        gPointP2   = (GraphicalPoint *) getHelperItem("P2");
        gPointP1   = (GraphicalPoint *) getHelperItem("P1");
        gLineB     = (GraphicalLine *) getHelperItem("2*b");
        gLineA     = (GraphicalLine *) getHelperItem("Radius a");
        gHelpLine1 = (GraphicalLine *) getHelperItem("h1");
        gHelpLine2 = (GraphicalLine *) getHelperItem("h2");

        gCircle->setMidPoint(midPoint);
        gCircle->setRadius(a);

        gMidPoint->setPoint(midPoint);
        gRefPoint->setPoint(refPoint);
        gPointQ->setPoint(pointQ);
        gPointP2->setPoint(curvePoint);
        gPointP1->setPoint(pointP1);
        gPointPosB->setPoint(pointPosB);
        gPointNegB->setPoint(pointNegB);

        gLineA->setStartPoint(refPoint);
        gLineA->setEndPoint(midPoint);

        gLineB->setStartPoint(pointP1);
        gLineB->setEndPoint(curvePoint);

        gHelpLine1->setStartPoint(pointH1);
        gHelpLine1->setEndPoint(pointP1);

        gHelpLine2->setStartPoint(curvePoint);
        gHelpLine2->setEndPoint(pointH2);
    }
}