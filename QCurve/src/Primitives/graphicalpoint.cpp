#include "graphicalpoint.h"

#include <QtGui/QGraphicsRectItem>
#include <QtGui/QPen>

GraphicalPoint::GraphicalPoint(const Point3D& p, const QString& name, const QString& description)
  : Primitive(PT_Point, name, description), m_p(p)
{ }

void GraphicalPoint::setPoint(const Point3D& point)
{ m_p = point; }

QGraphicsItem* GraphicalPoint::toGraphicsItem() const
{
  QGraphicsRectItem* item = new QGraphicsRectItem(m_p.x() - 0.025,
    m_p.y() - 0.025, 0.05, 0.05);

  QString toolTip = QString("<b>%1</b> [%2]").arg(m_name).arg(m_p.toString());
  if (!m_description.isEmpty())
  { toolTip += QString("<br>%1").arg(m_description); }

  item->setToolTip(toolTip);

  if (m_color.isValid())
  {
    QPen pen = item->pen();
    pen.setColor(m_color);
    item->setPen(pen);
  }

  return item;
}