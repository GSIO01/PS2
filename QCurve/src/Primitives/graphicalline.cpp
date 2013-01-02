#include "graphicalline.h"

#include <QtGui/QGraphicsLineItem>
#include <QtGui/QPen>

GraphicalLine::GraphicalLine(const Point3D& start, const Point3D& end, const QString& name,
  const QString& description)
  : Primitive(PT_Line, name, description), m_start(start), m_end(end)
{ }

void GraphicalLine::setStartPoint(const Point3D& p)
{ m_start = p; }

void GraphicalLine::setEndPoint(const Point3D& p)
{ m_end = p; }

QGraphicsItem* GraphicalLine::toGraphicsItem() const
{
  QGraphicsLineItem* item = new QGraphicsLineItem(m_start.x(), m_start.y(), m_end.x(), m_end.y());
  item->setToolTip(QString("<b>%1</b><br>%2").arg(m_name).arg(m_description));

  if (m_color.isValid())
  {
    QPen pen = item->pen();
    pen.setColor(m_color);
    item->setPen(pen);
  }

  return item;
}