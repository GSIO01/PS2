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

#include "epsexporter.h"

#include <Core/Point>
#include <Core/Function>

#include <Primitives/GraphicalCircle>
#include <Primitives/GraphicalLine>

EpsExporter::EpsExporter(const QString& fileName, const QString& author)
  : m_file(fileName), m_writer(&m_file), m_author(author),
    m_showHelpers(true), m_showLabels(false), m_showGrid(false)
{ }

EpsExporter::~EpsExporter()
{ }

void EpsExporter::setShowHelperItems(bool showHelperItems)
{ m_showHelpers = showHelperItems; }

void EpsExporter::setShowLabels(bool showLabels)
{ m_showLabels = showLabels; }

void EpsExporter::setShowGrid(bool showGrid)
{ m_showGrid = showGrid; }

bool EpsExporter::exportToFile(const Function& function)
{
  double stepRange = 0.05;

  if (!m_file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;

  writeHeader();
  writeDefinitions();

  m_writer << "%% coordinate system" << endl;

  //y-axis
  drawLine(0, function.dimension().bottom(),  0.05, function.dimension().bottom() - 0.1);
  drawLine(0, function.dimension().bottom(), -0.05, function.dimension().bottom() - 0.1);
  drawLine(0, function.dimension().bottom(), 0, function.dimension().top());

  //x-axis
  drawLine(function.dimension().right(), 0, function.dimension().right() - 0.1, -0.05);
  drawLine(function.dimension().right(), 0, function.dimension().right() - 0.1,  0.05);
  drawLine(function.dimension().left(),  0, function.dimension().right(), 0);

  m_writer << "%%" << function.name() << endl;

  Point3D* last = new Point3D[function.calculations()];
  for (int i = 0; i < function.calculations(); i++)
  { last[i] = function.calculate(i, function.parameter().from()); }

  for (double t = function.parameter().from() + stepRange; t < function.parameter().to() + stepRange; t += stepRange)
  {
    Point3D tmp;
    for (int i = 0; i < function.calculations(); i++)
    {
      tmp = function.calculate(i, t); //TODO transform
      drawLine(tmp, last[i]);
      last[i] = tmp;
    }
  }

  delete [] last;

  if (m_showHelpers)
  {
    m_writer << "%% helper items / descriptions" << endl;
    foreach (Primitive* p, function.helperItems())
    {
      if (p->isAnimated()) //ignore animations
      { continue; }

      if (p->type() == Primitive::PT_Circle)
      { drawCircle(((GraphicalCircle*)p)->midPoint(), ((GraphicalCircle*)p)->radius()); }
      else if (p->type() == Primitive::PT_Line)
      { drawLine(((GraphicalLine*)p)->start(), ((GraphicalLine*)p)->end()); }
      else if (p->type() == Primitive::PT_Point)
      {
        //addTextToScene(m_functionGroup, p->color(), p->name(),
        //               item->boundingRect().x() + 0.1, item->boundingRect().y());
      }
    }
  }

  writeFooter(function.dimension());

  return false;
}

void EpsExporter::drawLine(double x1, double y1, double x2, double y2)
{
  m_writer << fixed << x1 << " " << fixed << y1 << " m ";
  m_writer << fixed << x2 << " " << fixed << y2 << " l s" << endl;
}

void EpsExporter::drawCircle(const Point3D& p, double r)
{
  m_writer << fixed << p.x() << " " << fixed << p.y() << " " << fixed << r << " a s" << endl;
}

void EpsExporter::drawLine(const Point3D& start, const Point3D& end)
{
  m_writer << fixed << start.x() << " " << fixed << start.y() << " m ";
  m_writer << fixed << end.x()   << " " << fixed << end.y()   << " l s" << endl;
}

void EpsExporter::writeHeader()
{
  m_writer << "%!PS-Adobe-3.0 EPSF-2.0" << endl;
  m_writer << "%%Creator: " << m_author << endl;
  m_writer << "%%Title: " << m_file.fileName() << endl;
  m_writer << "%%BoundingBox: (atend)" << endl;
  m_writer << "%%DocumentFonts: Helvetica" << endl;
  m_writer << "%%EndComments" << endl;
}

void EpsExporter::writeDefinitions()
{
  m_writer << "/RE { 1 index 0 rlineto 0 exch rlineto neg 0 rlineto closepath stroke } def" << endl;
  m_writer << "/TR { /Helvetica findfont exch scalefont setfont } def" << endl;
  m_writer << "/SC { 1 1 div } def" << endl;
  m_writer << "/m { moveto } def" << endl;
  m_writer << "/l { lineto } def" << endl;
  m_writer << "/s { stroke } def" << endl;
  m_writer << "/n { newpath } def" << endl;
  m_writer << "/c { closepath } def" << endl;
  m_writer << "/f { fill } def" << endl;
  m_writer << "/w { setlinewidth } def" << endl;
  m_writer << "/a { 0 360 arc } def" << endl;
  m_writer << "/sc { setrgbcolor } def" << endl;
  m_writer << "/sg { setgray } def" << endl;
  m_writer << "/sgn { 0.0 setgray } def" << endl;
  m_writer << "/gs { gsave } def" << endl;
  m_writer << "/gr { grestore } def" << endl;
  m_writer << "/tr { translate } def" << endl;
  m_writer << "/Orig { 30 150 tr } def" << endl;
  m_writer << "/CL { } def" << endl;
  m_writer << "/NewPr { gr gs Orig SC SC scale CL } def" << endl;
  m_writer << "/Red { 1.0 0.0 0.0 sc } def" << endl;
  m_writer << "/Grn { 0.7 1.0 0.7 sc } def" << endl;
  m_writer << "/Blu { 0.0 0.0 1.0 sc } def" << endl;
  m_writer << "/Blk { 0 sg } def" << endl;
  m_writer << "/Wht { 1 sg } def" << endl;
  m_writer << "SC SC scale" << endl;
  m_writer << "0 0 translate" << endl;
  m_writer << "0.0 0.0 0.0 sc" << endl;
  m_writer << "0.01 w" << endl; //TODO
}

void EpsExporter::writeFooter(const QRectF& dimension)
{
  m_writer << "showpage" << endl;
  m_writer << "%%Trailer" << endl;
  m_writer << "%%BoundingBox: " << fixed << dimension.left() << " "
                                << fixed << dimension.top() << " "
                                << fixed << dimension.right() << " "
                                << fixed << dimension.bottom() << endl;
  m_writer << "%%EOF" << endl;
}
