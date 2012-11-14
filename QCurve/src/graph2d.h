#ifndef GRAPH2D_H
#define GRAPH2D_H

#include <QtCore/QTimer>

#include <QtGui/QGraphicsView>

class Function;
/***
 * Implements a widget which can be used to viusalize the graph 
 * of a mathmatical function.
 * 
 * @see Function
 */
class Graph2D : public QGraphicsView
{
  Q_OBJECT
  
  public:
    Graph2D(QWidget* parent = 0);
    virtual ~Graph2D();
    
    /***
     * Returns the animation delay in milliseconds.
     * 
     * @Note A value of zero means the the complete function should be drawn immediately.
     */
    int animationDelay() const { return m_animationDelay; }
    
    /***
     * Sets the animation delay.
     * 
     * The delay is used to determine the time after which 
     * another value should be drawn.
     *
     * @Note: A value of 0 or less turns of the animation. 
     */
    void setAnimationDelay(int delay);
    
    /***
     * Returns the step range which is used to calculate the next parameter value.
     * 
     * @Returns The steprange which will be within the range from 0.01 to 1.
     */
    float stepRange() const { return m_stepRange; }
    
    /***
     * Sets the step range whic is used to calculate the next value of the parameter.
     * 
     * @Note The value should be in range from 0.01 to 1. 
     */
    void setStepRange(float stepRange);
    
    /***
     * Draws the specified function.
     */
    void plot(const Function& function);
    
  protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
 
    QPointF center() { return m_curCenterPoint; }
    void setCenter(const QPointF& centerPoint);
    
  private slots:
    void drawFragment();
    void redraw();
    
  private:
    QTimer* m_timer;
    Function* m_function;
    
    QPointF m_curCenterPoint;
    QPoint m_lastPanPoint;
    
    int m_animationDelay;
    float m_stepRange;
    
    double m_lastX;
    double m_lastY;
    double m_t;
};

#endif
