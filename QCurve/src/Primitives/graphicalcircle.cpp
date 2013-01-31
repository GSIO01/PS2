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

#include "graphicalcircle.h"

#include <QtGui/QGraphicsEllipseItem>
#include <QtGui/QPen>

GraphicalCircle::GraphicalCircle(const Point3D& p, double r,
  const QString& name, const QString& description)
  : Primitive(PT_Circle, name, description), m_p(p), m_r(r)
{ }

void GraphicalCircle::setMidPoint(const Point3D& p)
{ m_p = p; }

void GraphicalCircle::setRadius(double r)
{ m_r = r; }

QGraphicsItem* GraphicalCircle::toGraphicsItem() const
{
  QGraphicsEllipseItem* item = new QGraphicsEllipseItem(m_p.x() - m_r,
    m_p.y() - m_r, m_r * 2, m_r * 2);

  item->setData(0, m_name);
  item->setToolTip(QString("<b>%1</b><br>%2").arg(m_name).arg(m_description));
  item->setZValue(-1);

  if (m_color.isValid())
  {
    QPen pen = item->pen();
    pen.setColor(m_color);
    item->setPen(pen);
  }

  return item;
}

void GraphicalCircle::updateGraphicsItem(QGraphicsItem* item) const
{
  if (item->data(0).toString() == m_name)
  { ((QGraphicsEllipseItem*)item)->setRect(m_p.x() - m_r, m_p.y() - m_r, m_r * 2, m_r * 2); }
}