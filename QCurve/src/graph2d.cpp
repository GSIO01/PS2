#include "graph2d.h"

#include <QtGui/QGraphicsScene>
#include <QtGui/QScrollBar>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>

#include <Core/Function>

Graph2D::Graph2D(QWidget* parent) : QGraphicsView(parent)
{
   QGraphicsScene* scene = new QGraphicsScene(this);
   setScene(scene);
}

Graph2D::~Graph2D()
{ }

void Graph2D::plot(const Function& function)
{
  scene()->clear(); //TODO Don't clear the entire scene, reuse the coordinate system if possible
  
  double x1 = function.calculateX(function.parameter().from());
  double y1 = function.calculateY(function.parameter().from());
  double x2, y2;
  for (double t = function.parameter().from() + 0.05; t <= function.parameter().to() + 0.05; t += 0.05) //TODO
  {
    x2 = function.calculateX(t); y2 = function.calculateY(t);
    scene()->addLine(x1, y1, x2, y2);
    x1 = x2; y1 = y2;
  }
 
  qreal w = function.dimension().right() - function.dimension().left();
  qreal h = function.dimension().top() - function.dimension().bottom();
  qreal wh = w/2; qreal hh = h/2;
  
  if (sceneRect() != function.dimension())
  { setSceneRect(function.dimension()); }
  
  scene()->addLine(function.dimension().left() + wh, -h, function.dimension().left() + wh, h); //TODO Reuse
  scene()->addLine(-w, function.dimension().bottom() + hh, w, function.dimension().bottom() + hh); //TODO Reuse
  //fitInView(function.dimension());
}

void Graph2D::setCenter(const QPointF& centerPoint) 
{
  QRectF visibleArea = mapToScene(rect()).boundingRect();
  QRectF sceneBounds = sceneRect();
 
  double boundX = visibleArea.width() / 2.0;
  double boundY = visibleArea.height() / 2.0;
  double boundWidth = sceneBounds.width() - 2.0 * boundX;
  double boundHeight = sceneBounds.height() - 2.0 * boundY;
 
  QRectF bounds(boundX, boundY, boundWidth, boundHeight);
 
  if (bounds.contains(centerPoint))
  { m_curCenterPoint = centerPoint; }
  else 
  {
    if (visibleArea.contains(sceneBounds))
    { m_curCenterPoint = sceneBounds.center(); }
    else 
    {
      m_curCenterPoint = centerPoint;
 
      if(centerPoint.x() > bounds.x() + bounds.width()) 
      { m_curCenterPoint.setX(bounds.x() + bounds.width()); }
      else if(centerPoint.x() < bounds.x()) 
      { m_curCenterPoint.setX(bounds.x()); }
 
      if(centerPoint.y() > bounds.y() + bounds.height()) 
      { m_curCenterPoint.setY(bounds.y() + bounds.height()); }
      else if(centerPoint.y() < bounds.y()) 
      { m_curCenterPoint.setY(bounds.y()); }
 
    }
  }

  centerOn(m_curCenterPoint);
}
 
void Graph2D::mousePressEvent(QMouseEvent* event) 
{
  m_lastPanPoint = event->pos();
  setCursor(Qt::ClosedHandCursor);
}
 
void Graph2D::mouseReleaseEvent(QMouseEvent* event) 
{
  setCursor(Qt::OpenHandCursor);
  m_lastPanPoint = QPoint();
}
 
void Graph2D::mouseMoveEvent(QMouseEvent* event) 
{
  if(!m_lastPanPoint.isNull()) 
  {
    QPointF delta = mapToScene(m_lastPanPoint) - mapToScene(event->pos());
    m_lastPanPoint = event->pos();
 
    setCenter(center() + delta);
  }
}
 
void Graph2D::wheelEvent(QWheelEvent* event) 
{ 
  QPointF pointBeforeScale(mapToScene(event->pos()));
  QPointF screenCenter = center();
 
  double scaleFactor = 1.15;
  if(event->delta() > 0) 
  { scale(scaleFactor, scaleFactor); }
  else { scale(1.0 / scaleFactor, 1.0 / scaleFactor); }
 
  QPointF pointAfterScale(mapToScene(event->pos()));
  QPointF offset = pointBeforeScale - pointAfterScale;
 
  QPointF newCenter = screenCenter + offset;
  setCenter(newCenter);
}
 
void Graph2D::resizeEvent(QResizeEvent* event) 
{
  QRectF visibleArea = mapToScene(rect()).boundingRect();
  setCenter(visibleArea.center());
 
  QGraphicsView::resizeEvent(event);
}