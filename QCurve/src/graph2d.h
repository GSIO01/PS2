#ifndef GRAPH2D_H
#define GRAPH2D_H

#include <QtGui/QGraphicsView>

class Function;
class Graph2D : public QGraphicsView
{
  Q_OBJECT
  
  public:
    Graph2D(QWidget* parent = 0);
    virtual ~Graph2D();
    
    void plot(const Function& function);
  
  protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
 
    QPointF center() { return m_curCenterPoint; }
    void setCenter(const QPointF& centerPoint);
    
  private:
    QPointF m_curCenterPoint;
    QPoint m_lastPanPoint;
};

#endif
