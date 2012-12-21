#ifndef GRAPH2D_H
#define GRAPH2D_H

#include <QtCore/QTimer>
#include <QtCore/QTimer>

#include <QtGui/QGraphicsView>

class Function;
class Point;
/***
 * Implements a widget which can be used to viusalize the graph
 * of a mathmatical function.
 *
 * @see Function
 */
class Graph2D : public QGraphicsView
{
  Q_OBJECT

  signals:
    void scaleFactorChanged(int factor);
    void currentPositionChanged(double x, double y);

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
     * Returns the scale factor as normalized value between 50 and 400.
     */
    int scaleFactor() const;

    /***
     * Returns a reference to the current function.
     * TODO/FIXME Should only be accessible by friends
     */
    Function& function() const { return *m_function; }

    void setVariable(const QString& var, double value);

    /***
     * Draws the specified function.
     */
    void plot(const Function& function);


  public slots:
    void setScaleFactor(int factor);

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
    void autoRedraw();
    void init();

  private:
    void redraw();
    Point transfromTo2D(const Point& p);
    void fitInView();
    void drawCoordinateSystem();

    void addTextToScene(QList<QGraphicsItem*>& group, const QString& text, double x, double y);
    void addTextToScene(QList<QGraphicsItem*>& group, const QColor& color, const QString& text, double x, double y);
    void addRectToScene(QList<QGraphicsItem*>& group, double x1, double y1, double x2, double y2);
    void addLineToScene(QList<QGraphicsItem*>& group, double x1, double y1, double x2, double y2);
    void addLineToScene(QList<QGraphicsItem*>& group, const QColor& color, double x1, double y1, double x2, double y2);

    QList<QGraphicsItem*> m_coordSysGroup;
    QList<QGraphicsItem*> m_functionGroup;

    QTimer* m_timer;
    Function* m_function;

    QPointF m_curCenterPoint;
    QPoint m_lastPanPoint;

    double m_scaleBase;

    int m_animationDelay;
    float m_stepRange;

    double m_lastX;
    double m_lastY;
    double m_t;

    bool m_ignoreAutoRedraw;
};

#endif
