#include "graph2d.h"

#include <QtGui/QGraphicsScene>
#include <QGraphicsTextItem>

#include <QtGui/QScrollBar>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>

#include "Core/Function"

Graph2D::Graph2D(QWidget* parent) : QGraphicsView(parent)
 , m_animationDelay(50), m_stepRange(0.1), m_function(0)
{
  m_timer = new QTimer(this);
  m_timer->setInterval(m_animationDelay);
  
  QGraphicsScene* scene = new QGraphicsScene(this);
  setScene(scene);
  
  connect(m_timer, SIGNAL(timeout()), this, SLOT(drawFragment()));
}

Graph2D::~Graph2D()
{ }

void Graph2D::setAnimationDelay(int delay)
{
  if (delay < 0)
  { m_animationDelay = 0; }
  else { m_animationDelay = delay; }
  
  m_timer->stop();
  m_timer->setInterval(m_animationDelay);
  
  if (m_animationDelay != 0)
  { m_timer->start(); }
  else { drawFragment(); }
}

void Graph2D::setStepRange(float step)
{
  if (step < 0.01)
  { m_stepRange = 0.01; }
  else if (step > 1)
  { m_stepRange = 1; }
  else { m_stepRange = step; }
}

void Graph2D::plot(const Function& function)
{
  if (m_timer->isActive())
  { m_timer->stop(); }

  if (m_function) //TODO/ Reuse if possible
  { delete m_function; }
  
  m_function = function.clone();
  
  scene()->clear(); //TODO Don't clear the entire scene, reuse the coordinate system if possible
  redraw();
}

/***
 * Draws a connection between the last calculated point and a new point
 * which than replace the old one.
 **/
void Graph2D::drawFragment()
{
  m_timer->stop();
  
  double x2, y2;
  
  m_t += m_stepRange;

  x2 = m_function->calculateX(m_t); 
  y2 = m_function->calculateY(m_t);
  scene()->addLine(m_lastX, m_lastY, x2, y2);
  m_lastX = x2; m_lastY = y2;
  
  if (m_t >= m_function->parameter().to() + m_stepRange)
  { 
    foreach (const Point& p, m_function->points())
    {
      scene()->addRect(p.X()-0.5, p.Y()-0.5, 1, 1);
      QGraphicsItem* item = scene()->addText(p.name());
      item->setPos(p.X()-1, p.Y()-1);
    }
    
    if (m_animationDelay != 0)
    { QTimer::singleShot(2000, this, SLOT(redraw())); } //repeat the anmation...
    
    return;
  }
  
  if (m_animationDelay == 0)
  { drawFragment(); }
  else { m_timer->start(); }
}

void Graph2D::redraw()
{ 
  scene()->clear();
  
  for (double t = m_function->parameter().from(); t < m_function->parameter().to() + m_stepRange; t += m_stepRange)
  {
    m_function->calculateX(t);
    m_function->calculateY(t);
  }
  
  qreal w = m_function->dimension().right() - m_function->dimension().left();
  qreal h = m_function->dimension().top() - m_function->dimension().bottom();
  
  scene()->addLine(0, -h, 0, h);
  scene()->addLine(-w, 0, w, 0);
  
  //setSceneRect(m_function->dimension());
  fitInView(sceneRect() ,Qt::KeepAspectRatio); //TODO a sceneRect which is not set never shrinks...
  
  m_t = m_function->parameter().from(); 
  m_lastX = m_function->calculateX(m_t);
  m_lastY = m_function->calculateY(m_t); 
  
  if (m_animationDelay != 0)
  { m_timer->start(); }
  else { drawFragment(); }
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