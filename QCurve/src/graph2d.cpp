#include "graph2d.h"

#include <QtCore/QDebug>

#include <QtGui/QApplication>

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsTextItem>
#include <QtGui/QGraphicsItemGroup>

#include <QtGui/QScrollBar>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>

#include "Core/Function"

#include <QtCore/qmath.h> //TODO move
double round(double val) //TODO move
{ return (val > 0.0) ? floor(val + 0.5) : ceil(val - 0.5); }

Graph2D::Graph2D(QWidget* parent) : QGraphicsView(parent)
  ,m_timer(0), m_function(0), m_stepRange(0.01), m_animationDelay(7)
{
  //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  QTimer::singleShot(0, this, SLOT(init()));
}

Graph2D::~Graph2D()
{ }

void Graph2D::init()
{
  m_useAntialiasing = true;
  m_repeat = false;
  m_showGrid = true;
  m_xAngle = 0;
  m_yAngle = 0;

  setScene(new QGraphicsScene(this));

  setRenderHints(QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
  setOptimizationFlags(QGraphicsView::DontSavePainterState | QGraphicsView::DontAdjustForAntialiasing);
  setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
  setCacheMode(QGraphicsView::CacheBackground);
  scale(1, -1);

  setMouseTracking(true);

  m_timer = new QTimer(this);
  m_timer->setInterval(m_animationDelay);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(drawFragment()));
}

void Graph2D::plot(const Function& function)
{
  blockSignals(true);
  if (m_timer->isActive()) { m_timer->stop(); }
  if (m_function)
  {
    delete m_function;
    delete [] m_lastPoints;
  }

  m_xAngle = 0; m_yAngle = 0;

  m_function = function.clone();
  m_lastPoints = new Point2D[m_function->calculations()];

  updateSceneRect();
  fitInView();
  setScaleFactor(100);

  qDeleteAll(m_helperAnimationGroup);
  m_helperAnimationGroup.clear();
  blockSignals(false);

  redraw();
}

void Graph2D::autoRedraw()
{
  //ignore timeout if another redraw request has been occured...
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

  for (int i = 0; i < m_function->calculations(); i++)
  { m_lastPoints[i] = transfromTo2D(m_function->calculate(i, m_t)); }

  if (m_animationDelay > 0) { m_timer->start(); }
  else { drawFragment(); }
}

/*** Draws a connection between the last calculated point and hte new point. **/
void Graph2D::drawFragment()
{
  m_timer->stop();
  blockSignals(true);

  bool finished = (m_t >= m_function->parameter().to());
  m_t += m_stepRange;

  if (!finished)
  {
    for (int i = 0; i < m_function->calculations(); i++)
    {
      Point2D tmp = transfromTo2D(m_function->calculate(i, m_t));;
      addLineToScene(m_functionGroup, m_lastPoints[i].x(), m_lastPoints[i].y(), tmp.x(), tmp.y());
      m_lastPoints[i] = tmp;
    }

    if (m_animationDelay > 0)
    {
      foreach (Primitive* p, m_function->helperItems())//TODO/FIXME apply transformation...
      {
        if (!p->isAnimated()) //ignore static helper items
        { continue; }

        QGraphicsItem* item = 0;
        for (int i = 0; i < m_helperAnimationGroup.size(); i++)
        {
          if (m_helperAnimationGroup.at(i)->data(0).toString() == p->name())
          { item = m_helperAnimationGroup.at(i); }
        }

        if (item)
        { p->updateGraphicsItem(item); }
        else
        {
          QGraphicsItem* newItem = p->toGraphicsItem();
          m_helperAnimationGroup.append(newItem);
          scene()->addItem(newItem);
        }
      }
    }

    if (m_animationDelay > 0) { m_timer->start(); }
    else { drawFragment(); }
  }
  else
  {
    qDeleteAll(m_helperAnimationGroup);
    m_helperAnimationGroup.clear();
    //TODO/FIXME apply transformation...
    foreach (Primitive* p, m_function->helperItems())
    {
      if (p->isAnimated()) //ignore animations
      { continue; }

      QGraphicsItem* item = p->toGraphicsItem();
      m_functionGroup.append(item);
      scene()->addItem(item);

      if (p->type() == Primitive::PT_Point)
      {
        addTextToScene(m_functionGroup, p->color(), p->name(),
                       item->boundingRect().x() + 0.1, item->boundingRect().y());
      }
    }

    if (m_repeat) //repeat the anmation...
    {
      m_ignoreAutoRedraw = false;
      QTimer::singleShot(3000, this, SLOT(autoRedraw()));
    }
  }

  blockSignals(false);
}

Point2D Graph2D::transfromTo2D(const Point3D& p)
{
  static const double degToRad = 3.141592653589793/180;

  if (m_function->is2Dimensional())
  { return Point2D(p.x(), p.y()); }

  double a = m_xAngle * degToRad;
  //double b = 0;
  double c = m_yAngle * degToRad;

  // x-axis
  double y = p.y() * cos(a) - p.z() * sin(a);
  double z = p.y() * sin(a) + p.z() * cos(a);
  double x = p.x();

  // y-axis
  //z = z * cos(b) - x * sin(b); // z = z * 1 - x * 0;
  //x = z * sin(b) + x * cos(b); // x = z * 0 + x * 1;
  //y = y;

  //z-axis
  x = x * cos(c) - y * sin(c);
  y = x * sin(c) + y * cos(c);
  //z = z;

  return Point2D(x, z); //x = 1*x+0; y = 1*z+0;
}

/*** Draws the entire coordinate system. **/
void Graph2D::drawCoordinateSystem()
{
  QColor nColor = QApplication::palette().color(QPalette::Disabled, QPalette::WindowText);
  QColor color = QApplication::palette().color(QPalette::WindowText);

  blockSignals(true);

  qDeleteAll(m_coordSysGroup);
  m_coordSysGroup.clear();

  QRectF rect = QRectF(mapToScene(0, 0), mapToScene(viewport()->width(), viewport()->height()));

  if (rect.left() > sceneRect().left()) { rect.setLeft(sceneRect().left()); }
  if (rect.right() < sceneRect().right()) { rect.setRight(sceneRect().right()); }

  //NOTE y axis is inverted...
  if (rect.bottom() > sceneRect().top()) { rect.setBottom(sceneRect().top()); }
  if (rect.top() < sceneRect().bottom()) { rect.setTop(sceneRect().bottom()); }

  double l = rect.left(); double r = rect.right();
  double b = rect.bottom(); double t = rect.top();

  int psf = (r + t) / 2; //arrow head calculation is based upon this size

  //y-axis
  addLineToScene(m_coordSysGroup, color, 0, t, psf *  0.01, t - psf * 0.04);
  addLineToScene(m_coordSysGroup, color, 0, t, psf * -0.01, t - psf * 0.04);
  addTextToScene(m_coordSysGroup, color, tr("Y"), psf * 0.015, t - psf * 0.01);
  addLineToScene(m_coordSysGroup, color, 0, b, 0, t);

  //x-axis
  addLineToScene(m_coordSysGroup, color, r, 0, r - psf * 0.04, psf * -0.01);
  addLineToScene(m_coordSysGroup, color, r, 0, r - psf * 0.04, psf *  0.01);
  addTextToScene(m_coordSysGroup, color, tr("X"), r - psf * 0.035, -psf * 0.01);
  addLineToScene(m_coordSysGroup, color, l, 0, r, 0);

  if (m_showGrid)
  {
    int h = t - b; int w = r - l;
    int wRange = (w < 10) ? 1 : w / 10;
    int hRange = (h < 10) ? 1 : h / 10;
    int range = (wRange < hRange) ? wRange : hRange;

    //horizontal lines
    int cells = h / range;
    if (cells > 10) { cells = 5; }
    else if (cells > 6) { cells = 2; }
    else { cells = 1; }
    for (int i = -range; i >= b; i -= range)
    {
      addLineToScene(m_coordSysGroup, nColor, l, i, r, i);
      if (i % (range * cells) == 0)
      { addTextToScene(m_coordSysGroup, nColor, QString::number(i), 0, i); }
    }
    for (int i = range; i <= t; i += range)
    {
      addLineToScene(m_coordSysGroup, nColor, l, i, r, i);
      if (i % (range * cells) == 0)
      { addTextToScene(m_coordSysGroup, nColor, QString::number(i), 0, i); }
    }

    //vertical lines
    cells = w / range;
    if (cells > 10) { cells = 5; }
    else if (cells > 5) { cells = 2; }
    else { cells = 1; }
    for (int i = -range; i >= l; i -= range)
    {
      addLineToScene(m_coordSysGroup, nColor, i, b, i, t);
      if (i % (range * cells) == 0)
      { addTextToScene(m_coordSysGroup, nColor, QString::number(i), i, 0); }
    }
    for (int i = range; i <= r; i += range)
    {
      addLineToScene(m_coordSysGroup, nColor, i, b, i, t);
      if (i % (range * cells) == 0)
      { addTextToScene(m_coordSysGroup, nColor, QString::number(i), i, 0); }
    }
  }

  for (int i = m_coordSysGroup.size() - 1; i >= 0; i--)
  {
    if (i < 8) { m_coordSysGroup[i]->setZValue(-2); }
    else { m_coordSysGroup[i]->setZValue(-3); }
  }

  blockSignals(false);
  update();
}

void Graph2D::drawCoordinateSystem3D()
{
  QColor color = QApplication::palette().color(QPalette::WindowText);

  blockSignals(true);

  for (int i = m_coordSysGroup.size() - 1; i >= 0; i--)
  { delete m_coordSysGroup.takeAt(i); }

  QRectF rect = QRectF(mapToScene(0, 0),
                       mapToScene(viewport()->width(), viewport()->height()));

  if (rect.left() > sceneRect().left()) { rect.setLeft(sceneRect().left()); }
  if (rect.right() < sceneRect().right()) { rect.setRight(sceneRect().right()); }
  if (rect.bottom() > sceneRect().bottom()) { rect.setBottom(sceneRect().bottom()); }
  if (rect.top() < sceneRect().top()) { rect.setTop(sceneRect().top()); }

  double l = rect.left(); double r = rect.right();
  double b = rect.bottom(); double t = rect.top();

  Point2D start = transfromTo2D(Point3D(l, 0, 0));
  Point2D end = transfromTo2D(Point3D(r, 0, 0));
  addLineToScene(m_coordSysGroup, color, start.x(), start.y(), end.x(), end.y());

  start = transfromTo2D(Point3D(0, b, 0));
  end = transfromTo2D(Point3D(0, t, 0));
  addLineToScene(m_coordSysGroup, color, start.x(), start.y(), end.x(), end.y());

  start = transfromTo2D(Point3D(0, 0, -6));
  end = transfromTo2D(Point3D(0, 0, 6));
  addLineToScene(m_coordSysGroup, color, start.x(), start.y(), end.x(), end.y());

  //show angles
  addTextToScene(m_coordSysGroup, QString(" %1=%2%3\n %4=%5%3")
    .arg(QChar(0x03B1)).arg(QString::number(m_xAngle)).arg(QChar(0xB0))
    .arg(QChar(0x03B2)).arg(QString::number(m_yAngle)),
    l, t);

  for (int i = m_coordSysGroup.size() - 1; i >= 0; i--)
  { m_coordSysGroup[i]->setZValue(-2); }

  blockSignals(false);
  update();
}

void Graph2D::updateSceneRect()
{
  QRectF rect = m_function->dimension();
  //rect.setLeft(rect.left() - 0.5);
  //rect.setRight(rect.right() + 0.5);

  /*if (rect.top() < rect.bottom())
  {
    double top = rect.bottom() + 0.5;
    rect.setBottom(rect.top() - 0.5);
    rect.setTop(top);
  }
  else
  {
    rect.setBottom(rect.bottom() - 0.5);
    rect.setTop(rect.top() + 0.5);
  }*/

  scene()->setSceneRect(rect);
}

void Graph2D::fitInView()
{
  QGraphicsView::fitInView(sceneRect(), Qt::KeepAspectRatio); //ByExpanding
  m_scaleBase = transform().m11();
}

void Graph2D::addLineToScene(QList<QGraphicsItem*>& group,
                             double x1, double y1, double x2, double y2)
{
  QGraphicsLineItem* item = scene()->addLine(x1, y1, x2, y2);
  item->setPen(QPen(QApplication::palette().color(QPalette::WindowText)));

  group.append(item);
}

void Graph2D::addLineToScene(QList<QGraphicsItem*>& group, const QColor& color,
                             double x1, double y1, double x2, double y2, bool scale)
{
  QGraphicsLineItem* item = scene()->addLine(x1, y1, x2, y2);
  if (!scale) { item->setFlags(QGraphicsItem::ItemIgnoresTransformations); }
  //if (x1 == x2 || y1 == y2) { } TODO ignore antialiasing
  item->setPen(QPen(color));

  group.append(item);
}

QGraphicsItem* Graph2D::addRectToScene(QList<QGraphicsItem*>& group, double x1,
                                       double y1, double x2, double y2)
{
  QGraphicsRectItem* item = scene()->addRect(x1, y1, x2, y2);
  item->setPen(QPen(QApplication::palette().color(QPalette::WindowText)));

  group.append(item);

  return item;
}

void Graph2D::addTextToScene(QList<QGraphicsItem*>& group, const QString& text,
                             double x, double y)
{
  //non rich text is sufficient
  QGraphicsSimpleTextItem* item = scene()->addSimpleText(text);
  item->setFlags(QGraphicsItem::ItemIgnoresTransformations);
  item->setPen(QPen(QApplication::palette().color(QPalette::WindowText)));
  item->setPos(x, y);

  group.append(item);
}

void Graph2D::addTextToScene(QList<QGraphicsItem*>& group, const QColor& color,
                             const QString& text, double x, double y)
{
  //non rich text is sufficient
  QGraphicsSimpleTextItem* item = scene()->addSimpleText(text);
  item->setFlags(QGraphicsItem::ItemIgnoresTransformations);
  item->setPen(QPen(color));
  item->setPos(x, y);

  group.append(item);
}

void Graph2D::setAnimationDelay(int delay, bool repeat)
{
  if (delay < 0) { m_animationDelay = 0; }
  else { m_animationDelay = delay; }
  m_repeat = repeat;

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

void Graph2D::setUseAntialiasing(bool useAntialiasing)
{
  m_useAntialiasing = useAntialiasing;
  if (useAntialiasing)
  {
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
  }
  else
  {
    setRenderHints(QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    setOptimizationFlags(QGraphicsView::DontSavePainterState | QGraphicsView::DontAdjustForAntialiasing);
  }

  redraw();
}

void Graph2D::setParameter(double from, double to)
{
  m_function->setParameter(from, to);
  updateSceneRect();

  int scale = scaleFactor();
  fitInView();
  setScaleFactor(scale);

  redraw();
}

void Graph2D::setVariable(const QString& var, double value)
{
  m_function->setVariable(var, value);
  updateSceneRect();

  int scale = scaleFactor();
  fitInView();
  setScaleFactor(scale);

  redraw();
}

void Graph2D::setScaleFactor(int factor)
{
  if (factor < 50) { factor = 50; }
  else if (factor > 400) { factor = 400; }

  //if (scaleFactor() == factor) { return; }

  double val = m_scaleBase * factor/100.0f;
  setTransform(QTransform::fromScale(val, -val));

  if (m_function->is2Dimensional())
  { drawCoordinateSystem(); }
  else { drawCoordinateSystem3D(); }

  emit scaleFactorChanged(factor);
}

void Graph2D::setShowGrid(bool isVisible)
{
  m_showGrid = isVisible;
  if (m_function->is2Dimensional())
  { drawCoordinateSystem(); }
  else { drawCoordinateSystem3D(); }
}

void Graph2D::mousePressEvent(QMouseEvent* event)
{
  m_lastPanPoint = event->pos();
  setCursor(Qt::ClosedHandCursor);
}

void Graph2D::mouseReleaseEvent(QMouseEvent* event)
{
  Q_UNUSED(event);
  setCursor(Qt::ArrowCursor);
}

void Graph2D::mouseMoveEvent(QMouseEvent* event)
{
  QPointF pos = mapToScene(event->pos());
  if (!m_function->is2Dimensional() && event->buttons() != Qt::NoButton)
  {
    QPointF delta = m_lastPanPoint;

    if (delta.x() - event->pos().x() > 0)
    { m_yAngle = (m_yAngle - 5) % 360; }
    else if (delta.x() - event->pos().x() < 0)
    { m_yAngle = (m_yAngle + 5) % 360; }

    if (delta.y() - event->pos().y() > 0) //inverted y axis (scale -1)
    { m_xAngle = (m_xAngle + 5) % 360; }
    else if (delta.y() - event->pos().y() < 0) //inverted y axis (scale -1)
    { m_xAngle = (m_xAngle - 5) % 360; }

    if (m_animationDelay > 0) //ignore delay and redraw entire function...
    {
      int delay = m_animationDelay;
      m_animationDelay = 0;
      redraw();
      drawCoordinateSystem3D();
      m_animationDelay = delay;
    }
    else { redraw(); }
    m_lastPanPoint = event->pos();
  }

  emit currentPositionChanged(pos.x(), pos.y());
}

void Graph2D::wheelEvent(QWheelEvent* event)
{
  QPointF pointBeforeScale(mapToScene(event->pos()));

  if(event->delta() > 0)
  {
    if (scaleFactor() == 400) { return; }
    setScaleFactor(scaleFactor() * 1.1);
  }
  else
  {
    if (scaleFactor() == 50) { return; }
    setScaleFactor(scaleFactor() * 0.9);
  }

  centerOn(pointBeforeScale);
}

void Graph2D::resizeEvent(QResizeEvent* event)
{
  if (m_timer && m_timer->isActive())
  {
    m_timer->stop();
    QTimer::singleShot(1000, this, SLOT(drawFragment()));
  }

  if (scene())
  {
    int scaleFact = scaleFactor();
    fitInView(); //TODO can lead to infinite loop -> see QGraphicsView::fitInView() [Qt docs]
    setScaleFactor(scaleFact);
  }

  QRectF visibleArea = mapToScene(rect()).boundingRect();
  centerOn(visibleArea.center());

  QGraphicsView::resizeEvent(event);
}
