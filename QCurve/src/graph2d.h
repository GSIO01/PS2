#ifndef GRAPH2D_H
#define GRAPH2D_H

#include <QtCore/QTimer>
#include <QtCore/QTimer>

#include <QtGui/QGraphicsView>

#include "Core/Point"

class Function;
/**
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

    /**
     * Returns the animation delay in milliseconds.
     *
     * @Note A value of zero means the the complete function should be drawn immediately.
     */
    int animationDelay() const { return m_animationDelay; }
    /**
     * Sets the animation delay.
     *
     * The delay is used to determine the time after which
     * the next value should be drawn.
     *
     * @Note: A value of 0 or less turns off the animation.
     */
    void setAnimationDelay(int delay, bool repeat = false);

    /** Returns true if the grid is visible otherwise false. */
    bool showGrid() const { return m_showGrid; }
    /** Sets a value which indicates if the grid should be visible or not. */
    void setShowGrid(bool isVisible);

    /**
     * Returns the step range which is used to calculate the next parameter value.
     *
     * @Returns The steprange which will be within the range from 0.01 to 1.
     */
    float stepRange() const { return m_stepRange; }
    /**
     * Sets the step range whic is used to calculate the next value of the parameter.
     *
     * @Note The value should be in range from 0.01 to 1.
     */
    void setStepRange(float stepRange);

    /*** Returns the scale factor as normalized value between 50 and 400. */
    int scaleFactor() const { return transform().m11()/m_scaleBase * 100; }

    void setUseAntialiasing(bool useAntialiasing);
    /** Returns a value indicating whether the graph should be antialised or not.*/
    bool useAntialiasing() const { m_useAntialiasing; }

    /**
     * Returns a reference to the current function.
     * TODO/FIXME Should only be accessible by friends
     */
    Function& function() const { return *m_function; }

    /** Updates both the variable and the view. */
    void setVariable(const QString& var, double value);

    /*** Draws the specified function. */
    void plot(const Function& function);

  public slots:
    /**
     * Sets the scale factor of the scene.
     *
     * @Note the value should be between 50 and 400.
     */
    void setScaleFactor(int factor);

  protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void resizeEvent(QResizeEvent* event);

    QPointF center() const { return m_curCenterPoint; }
    void setCenter(const QPointF& centerPoint);

  private slots:
    void drawFragment();
    void autoRedraw();
    void init();

  private:
    double gridRange();
    double labelRange();

    void redraw();
    void drawCoordinateSystem();

    void fitInView();
    void updateSceneRect();

    Point2D transfromTo2D(const Point3D& p);

    void addTextToScene(QList<QGraphicsItem*>& group, const QString& text, double x, double y);
    void addTextToScene(QList<QGraphicsItem*>& group, const QColor& color, const QString& text, double x, double y);
    QGraphicsItem* addRectToScene(QList<QGraphicsItem*>& group, double x1, double y1, double x2, double y2);
    void addLineToScene(QList<QGraphicsItem*>& group, double x1, double y1, double x2, double y2);
    void addLineToScene(QList<QGraphicsItem*>& group, const QColor& color, double x1, double y1, double x2, double y2);

    QList<QGraphicsItem*> m_coordSysGroup;
    QList<QGraphicsItem*> m_functionGroup;
    QList<QGraphicsItem*> m_helperAnimationGroup;

    QTimer* m_timer;
    Function* m_function;

    QPointF m_curCenterPoint;
    QPoint m_lastPanPoint;

    double m_scaleBase;
    double m_stepRange;

    Point2D m_lastPoint;
    double m_t;

    int m_xAngle;
    int m_yAngle;

    int m_animationDelay;
    bool m_repeat;
    bool m_showGrid;
    bool m_ignoreAutoRedraw;
    bool m_useAntialiasing;
};

#endif
