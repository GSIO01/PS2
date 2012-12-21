#include "graph2d.h"

#include <QtGui/QApplication>

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsTextItem>
#include <QtGui/QGraphicsItemGroup>

#include <QtGui/QScrollBar>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>

#include <QtCore/qmath.h> //TODO

#include <QtCore/QDebug>

#include "Core/Function"

Graph2D::Graph2D(QWidget* parent) : QGraphicsView(parent)
 , m_animationDelay(1), m_stepRange(0.005), m_function(0)
{
  setMouseTracking(true);

  QTimer::singleShot(0, this, SLOT(init()));
}

Graph2D::~Graph2D()
{ }

void Graph2D::init()
{
  setScene(new QGraphicsScene(this));
  scene()->setSceneRect(-1.5, -1.5, 3, 3);

  //setRenderHints(QPainter::Antialiasing);
  scale(1, -1);

  m_timer = new QTimer(this);
  m_timer->setInterval(m_animationDelay);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(drawFragment()));
}

void Graph2D::setAnimationDelay(int delay)
{
  if (delay < 0) { m_animationDelay = 0; }
  else { m_animationDelay = delay; }

  m_timer->stop();
  m_timer->setInterval(m_animationDelay);

  if (m_animationDelay != 0) { m_timer->start(); }
  else { drawFragment(); }
}

void Graph2D::setStepRange(float step)
{
  if (step < 0.01) { m_stepRange = 0.01; }
  else if (step > 1) { m_stepRange = 1; }
  else { m_stepRange = step; }
}

void Graph2D::plot(const Function& function)
{
  if (m_timer->isActive()) { m_timer->stop(); }

  //TODO/ Reuse if possible
  if (m_function) { delete m_function; }
  m_function = function.clone();

  /*if (m_function->dimension().isNull())
  {
    //precalculate to get boundaries...
    for (double t = m_function->parameter().from(); t < m_function->parameter().to() + m_stepRange; t += m_stepRange)
    {
      m_function->calculateX(t);
      m_function->calculateY(t);
    }
  }*/

  scene()->setSceneRect(m_function->dimension());
  fitInView();
  setScaleFactor(50);

  redraw();
}

void Graph2D::autoRedraw()
{
  //ignore timeout if another redraw request has been handled...
  if (!m_ignoreAutoRedraw)
  { redraw(); }
}

void Graph2D::redraw()
{
  m_ignoreAutoRedraw = true;

  blockSignals(true); //clear all graphical items which belong to the function
  for (int i = m_functionGroup.size() - 1; i >= 0; i--)
  { delete m_functionGroup.takeAt(i); }
  blockSignals(false);
  update();

  m_t = m_function->parameter().from();

  if (m_function->name() != "Helix")  //TODO add identifier for 3D/2D function
  {
    m_lastX = m_function->calculateX(m_t);
    m_lastY = m_function->calculateY(m_t);
  }
  else
  {
    Point p(m_function->calculateX(m_t), m_function->calculateY(m_t), m_function->calculateZ(m_t));
    p = transfromTo2D(p);
    m_lastX = p.X();
    m_lastY = p.Y();
  }

  if (m_animationDelay != 0) { m_timer->start(); }
  else { drawFragment(); }
}

/*** Draws a connection between the last calculated point and a new point. **/
void Graph2D::drawFragment()
{
  m_timer->stop();

  m_t += m_stepRange;
  double x2; double y2;

  if (m_function->name() != "Helix") //TODO add identifier for 3D/2D function
  {
    x2 = m_function->calculateX(m_t);
    y2 = m_function->calculateY(m_t);
  }
  else
  {
    Point p(m_function->calculateX(m_t), m_function->calculateY(m_t), m_function->calculateZ(m_t));
    p = transfromTo2D(p);
    x2 = p.X();
    y2 = p.Y();
  }

  addLineToScene(m_functionGroup, m_lastX, m_lastY, x2, y2);

  m_lastX = x2; m_lastY = y2; //replace old point with the new one

  if (m_t >= m_function->parameter().to() + m_stepRange)
  {
    //mark special points after the complete function is drawn
    foreach (const Point& p, m_function->points())
    {
      addRectToScene(m_functionGroup, p.X()- 0.025, p.Y() - 0.025, 0.05, 0.05);
      addTextToScene(m_functionGroup, p.name(), p.X() - 0.1, p.Y() - 0.1);
    }

    if (m_animationDelay != 0) //repeat the anmation...
    {
      m_ignoreAutoRedraw = false;
      QTimer::singleShot(4000, this, SLOT(autoRedraw()));
    }

    return;
  }

  if (m_animationDelay == 0) { drawFragment(); }
  else { m_timer->start(); }
}

//TODO transform changes movement on xy-plane
Point Graph2D::transfromTo2D(const Point& p)
{
  double x0 = m_function->getVariable("x0");
  double y0 = m_function->getVariable("y0");
  double z0 = m_function->getVariable("z0");

  Point viewer(x0, y0, 5 + z0); //TODO
  Point r(0, 0, 0); //TODO
  Point cam(x0, y0, 5 + z0); //TODO

  Point radR = r.toRadial();

  double cosX = qCos(r.X()); double sinX = qSin(r.X());
  double cosY = qCos(r.Y()); double sinY = qSin(r.Y());
  double cosZ = qCos(r.Z()); double sinZ = qSin(r.Z());

  double x = cosY * (sinZ * (p.Y() - cam.Y())
                   + cosZ * (p.X() - cam.X())) - sinY * (p.Z() - cam.Z());
  double y = sinX * (cosY * (p.Z() - cam.Z())
                   + sinY * (sinZ * (p.Y() - cam.Y()) + cosZ * (p.X() - cam.X())))
                   + cosX * (cosZ * (p.Y() - cam.Y()) - sinZ * (p.X() - cam.X()));
  double z = cosX * (cosY * (p.Z() - cam.Z())
                   + sinY * (sinZ * (p.Y() - cam.Y()) + cosZ * (p.X() - cam.X())))
                   - sinX * (cosZ * (p.Y() - cam.Y()) - sinZ * (p.X() - cam.X()));

  x = (x - viewer.X()) * (z / viewer.Z()) + x0;
  y = (y - viewer.Y()) * (z / viewer.Z()) + y0;

  return Point(x, y);
}

/*** Draws the entire coordinate system. **/
void Graph2D::drawCoordinateSystem()
{
  QColor nColor = QApplication::palette().color(QPalette::Disabled, QPalette::WindowText);
  QColor color = QApplication::palette().color(QPalette::WindowText);

  blockSignals(true);

  for (int i = m_coordSysGroup.size() - 1; i >= 0; i--)
  { delete m_coordSysGroup.takeAt(i); }

  double x0 = 0;
  double y0 = 0;
  if (m_function)
  {
    x0 = m_function->getVariable("x0");
    y0 = m_function->getVariable("y0");
  }

  QRectF rect(mapToScene(0, 0), mapToScene(viewport()->width(), viewport()->height()));

  double scale = scaleFactor();
  //coordinate system should always fill the entire visible viewport
  double w = (scale >= 100) ?  rect.width() /2 * scale/100 :  rect.width() /2;
  double h = (scale >= 100) ? -rect.height()/2 * scale/100 : -rect.height()/2;

  //y-axis arrowheads
  addLineToScene(m_coordSysGroup, color, 0, -h + y0,  0.05, -h + y0 + 0.1);
  addLineToScene(m_coordSysGroup, color, 0, -h + y0, -0.05, -h + y0 + 0.1);
  addLineToScene(m_coordSysGroup, color, 0,  h + y0,  0.05,  h + y0 - 0.1);
  addLineToScene(m_coordSysGroup, color, 0,  h + y0, -0.05,  h + y0 - 0.1);

  int range = 0;
  if (h >= 20) { range = 10; }
  else if (h >= 8) { range = 5; }
  else { range = 1; }
  for (int i = -h + y0; i <= (h + y0); i++)
  {
    if (i == -h + y0) continue;

    if (i == 0) { addLineToScene(m_coordSysGroup, color, -w + x0, i, w + x0, i); }
    else { addLineToScene(m_coordSysGroup, nColor, -w + x0, i, w + x0, i); }

    if (!(i % range)) { addTextToScene(m_coordSysGroup, QString::number(i), 0, i); }
  }

  //x-axis arrowheads
  addLineToScene(m_coordSysGroup, color, -w + x0, 0, -w + x0 + 0.1, -0.05);
  addLineToScene(m_coordSysGroup, color, -w + x0, 0, -w + x0 + 0.1,  0.05);
  addLineToScene(m_coordSysGroup, color,  w + x0, 0,  w + x0 - 0.1, -0.05);
  addLineToScene(m_coordSysGroup, color,  w + x0, 0,  w + x0 - 0.1,  0.05);

  if (w >= 20) { range = 10; }
  else if (w >= 8) { range = 5; }
  else { range = 1; }
  for (int i = -w + x0; i <= (w + x0); i++)
  {
    if (i == -w + x0) continue;

    if (i == 0) { addLineToScene(m_coordSysGroup, color, i, -h + y0, i, h + y0); }
    else { addLineToScene(m_coordSysGroup, nColor, i, -h + y0, i, h + y0); }

    if (!(i % range)) { addTextToScene(m_coordSysGroup, QString::number(i), i, 0); }
  }

  for (int i = m_coordSysGroup.size() - 1; i >= 0; i--)
  { m_coordSysGroup[i]->setZValue(-1); }

  blockSignals(false);
  update();
}

void Graph2D::addLineToScene(QList<QGraphicsItem*>& group, double x1, double y1, double x2, double y2)
{
  QGraphicsLineItem* item = scene()->addLine(x1, y1, x2, y2);
  item->setPen(QPen(QApplication::palette().color(QPalette::WindowText)));

  group.append(item);
}

void Graph2D::addLineToScene(QList<QGraphicsItem*>& group, const QColor& color, double x1, double y1, double x2, double y2)
{
  QGraphicsLineItem* item = scene()->addLine(x1, y1, x2, y2);
  item->setPen(QPen(color));

  group.append(item);
}

void Graph2D::addRectToScene(QList<QGraphicsItem*>& group, double x1, double y1, double x2, double y2)
{
  QGraphicsRectItem* item = scene()->addRect(x1, y1, x2, y2);
  item->setPen(QPen(QApplication::palette().color(QPalette::WindowText)));

  group.append(item);
}

void Graph2D::addTextToScene(QList<QGraphicsItem*>& group, const QString& text, double x, double y)
{
  QGraphicsSimpleTextItem* item = scene()->addSimpleText(text); //non rich text is sufficient
  item->setFlags(QGraphicsItem::ItemIgnoresTransformations);
  item->setPen(QPen(QApplication::palette().color(QPalette::WindowText)));
  item->setPos(x, y);

  group.append(item);
}

void Graph2D::addTextToScene(QList<QGraphicsItem*>& group, const QColor& color, const QString& text, double x, double y)
{
  QGraphicsSimpleTextItem* item = scene()->addSimpleText(text); //non rich text is sufficient
  item->setFlags(QGraphicsItem::ItemIgnoresTransformations);
  item->setPen(QPen(color));
  item->setPos(x, y);

  group.append(item);
}

void Graph2D::fitInView()
{
  QGraphicsView::fitInView(sceneRect(), Qt::KeepAspectRatio);
  m_scaleBase = transform().m11();
}

void Graph2D::setVariable(const QString& var, double value)
{
  m_function->setVariable(var, value);
  scene()->setSceneRect(m_function->dimension());

  int scale = scaleFactor();
  fitInView();
  setScaleFactor(scale);

  redraw();
}

int Graph2D::scaleFactor() const
{ return transform().m11()/m_scaleBase * 100; }

void Graph2D::setScaleFactor(int factor)
{
  if (factor < 50) { factor = 50; }
  else if (factor > 400) { factor = 400; }

  if (scaleFactor() == factor) { return; }

  double val = m_scaleBase * factor/100.0f;
  setTransform(QTransform::fromScale(val, -val));
  drawCoordinateSystem();

  emit scaleFactorChanged(factor);
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
  //if (delta < 0.15)
  //{ emit positionChanged(mapToScene(event->pos().x(), event->pos().y())); }

  setCursor(Qt::ArrowCursor);
  m_lastPanPoint = QPoint();
}

void Graph2D::mouseMoveEvent(QMouseEvent* event)
{
  QPointF pos = mapToScene(event->pos());
  if (event->buttons() != Qt::NoButton && !m_lastPanPoint.isNull()) //TODO
  {
    QPointF delta = mapToScene(m_lastPanPoint) - pos;
    m_lastPanPoint = event->pos();

    setCenter(center() + delta);
  }

  if (m_function)
  {
    QString tooltip;
    foreach (const Point& p, m_function->points())
    {
      if (p.X() == pos.x() && p.Y() == pos.y()) //TODO don't compare double values...
      { tooltip += p.name(); }
    }
    setToolTip(tooltip);
  }

  emit currentPositionChanged(pos.x(), pos.y());
}

void Graph2D::wheelEvent(QWheelEvent* event)
{
  QPointF pointBeforeScale(mapToScene(event->pos()));
  QPointF screenCenter = center();

  if(event->delta() > 0)
  { setScaleFactor(scaleFactor() * 1.1); }
  else { setScaleFactor(scaleFactor() * 0.9); }

  QPointF pointAfterScale(mapToScene(event->pos()));
  QPointF offset = pointBeforeScale - pointAfterScale;

  QPointF newCenter = screenCenter + offset;
  setCenter(newCenter);
}

void Graph2D::resizeEvent(QResizeEvent* event)
{
  if (scene())
  {
    //if (m_timer->isActive()) { m_timer->stop(); }

    int scaleFact = scaleFactor();
    fitInView();
    setScaleFactor(scaleFact);

   // if (m_animationDelay != 0) { m_timer->start(); }
  }

  QRectF visibleArea = mapToScene(rect()).boundingRect();
  setCenter(visibleArea.center());

  QGraphicsView::resizeEvent(event);
}
