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

#include "graphicalpoint.h"

#include <QtGui/QGraphicsRectItem>
#include <QtGui/QPen>

GraphicalPoint::GraphicalPoint(const Point3D& p, const QString& name,
                               const QString& description)
  : Primitive(PT_Point, name, description), m_p(p)
{ }

void GraphicalPoint::setPoint(const Point3D& point)
{ m_p = point; }

QGraphicsItem* GraphicalPoint::toGraphicsItem() const
{
  QGraphicsRectItem* item = new QGraphicsRectItem(m_p.x() - 0.05,
    m_p.y() - 0.05, 0.1, 0.1);

  QString toolTip = QString("<b>%1</b> [%2]").arg(m_name).arg(m_p.toString());
  if (!m_description.isEmpty())
  { toolTip += QString("<br>%1").arg(m_description); }

  //item->setFlags(QGraphicsItem::ItemIgnoresTransformations);
  item->setData(0, m_name);
  item->setToolTip(toolTip);
  item->setZValue(-1);

  if (m_color.isValid())
  {
    QPen pen = item->pen();
    pen.setColor(m_color);
    item->setPen(pen);
  }

  return item;
}

void GraphicalPoint::updateGraphicsItem(QGraphicsItem* item) const
{
  if (item->data(0).toString() == m_name)
  { ((QGraphicsRectItem*)item)->setRect(m_p.x() - 0.05, m_p.y() - 0.05, 0.1, 0.1); }
}