/*
 * (C) Copyright 2012-2013 QCurve Team
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser General Public License
 * (LGPL) version 2.1 which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl-2.1.html
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 */

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
    /**
     * Signal for scale factor changes.
     *
     * \param factor new scale factor
     */
    void scaleFactorChanged(int factor);

    /**
     * Signal for position changes.
     *
     * \param x new x coordinate
     * \param y new y coordinate
     */
    void currentPositionChanged(double x, double y);

  public:
    Graph2D(QWidget* parent = 0);
    virtual ~Graph2D();

    /**
     * Returns the animation delay in milliseconds.
     *
     * @Note A value of zero means the the complete function should be drawn immediately.
     *
     * \return Animation delay in milliseconds.
     */
    int animationDelay() const { return m_animationDelay; }
    /**
     * Sets the animation delay.
     *
     * The delay is used to determine the time after which
     * the next value should be drawn.
     *
     * @Note: A value of 0 or less turns off the animation.
     *
     * \param delaytime Time after which the next value should be drawn.
     * \param repeat Should the animation be repeated?
     */
    void setAnimationDelay(int delay, bool repeat = false);

    /**
     * Returns true if the grid is visible otherwise false.
     *
     * \return Grid visible?
     */
    bool showGrid() const { return m_showGrid; }
    /**
     * Sets a value which indicates if the grid should be visible or not.
     *
     * \param isVisible Whether to enable or disable the grid.
     */
    void setShowGrid(bool isVisible);

    /**
     * Returns the step range which is used to calculate the next parameter value.
     *
     * \return The steprange which will be within the range from 0.01 to 1.
     */
    float stepRange() const { return m_stepRange; }
    /**
     * Sets the step range whic is used to calculate the next value of the parameter.
     *
     * @Note The value should be in range from 0.01 to 1.
     *
     * \param stepRange The stepRange (value from 0.01 to 1).
     */
    void setStepRange(float stepRange);

    /**
     * Returns the scale factor as normalized value between 50 and 400.
     *
     * \return Scale factor.
     */
    int scaleFactor() const { return transform().m11()/m_scaleBase * 100; }

    /**
     * Enable/disable Antialiasing.
     *
     * \param useAntialiasing Whether the Antialiasing should be enabled or disabled.
     */
    void setUseAntialiasing(bool useAntialiasing);
    /**
     * Returns a value indicating whether the graph should be antialised or not.
     *
     * \return Antialiasing enabled?
     */
    bool useAntialiasing() const { return m_useAntialiasing; }

    /**
     * Returns a reference to the current function.
     * TODO/FIXME Should only be accessible by friends
     *
     * \return A reference to the current function
     */
    Function& function() const { return *m_function; }

    /**
     * Updates both the variable and the view.
     *
     * \param var Variable name.
     * \param value New value.
     */
    void setVariable(const QString& var, double value);

    /**
     * Updates parameter and the view.
     *
     * \param from new from value
     * \param to new to value
     */
    void setParameter(double from, double to);

    /**
     * Draws the specified function.
     *
     * \param function Function to draw.
     */
    void plot(const Function& function);
    /**
     * Redraws the graph.
     */
    void redraw();

  public slots:
    /**
     * Sets the scale factor of the scene.
     *
     * @Note the value should be between 50 and 400.
     *
     * \param factor Scale factor.
     */
    void setScaleFactor(int factor);

  protected:
    /**
     * Event handler for mouse press event.
     */
    virtual void mousePressEvent(QMouseEvent* event);
    /**
     * Event handler for mouse release event.
     */
    virtual void mouseReleaseEvent(QMouseEvent* event);
    /**
     * Event handler for mouse move event.
     */
    virtual void mouseMoveEvent(QMouseEvent* event);
    /**
     * Event handler for mouse wheel event.
     */
    virtual void wheelEvent(QWheelEvent* event);
    /**
     *  Event handler for resize event.
     */
    virtual void resizeEvent(QResizeEvent* event);

  private slots:
    /**
     * Draw a fragment.
     */
    void drawFragment();
    /**
     * Auto redraw.
     */
    void autoRedraw();
    /**
     * Initialize.
     */
    void init();

  private:
    /**
     * Get the grid range.
     *
     * \return Grid range.
     */
    double gridRange();
    /**
     * Get the lable range.
     */
    double labelRange();

    /**
     * Draw the 2D coordinate system.
     */
    void drawCoordinateSystem();
    /**
     * Draw the 3D coordinate system.
     */
    void drawCoordinateSystem3D();

    /**
     * Fit into view.
     */
    void fitInView();
    /**
     * Update the scene rectangle.
     */
    void updateSceneRect();

    /**
     * Transform a Point3D to Point2D using perspective or parallel projection.
     *
     * \param p 3D point to transform.
     * \return 2D point.
     */
    Point2D transfromTo2D(const Point3D& p);

    /**
     * Add text to the scene.
     *
     * \param group List of QGraphicsItems.
     * \param text Text.
     * \param x X coordinate.
     * \param y Y coordinate.
     */
    void addTextToScene(QList<QGraphicsItem*>& group, const QString& text, double x, double y);
     /**
     * Add text to the scene.
     *
     * \param group List of QGraphicsItems.
     * \param text Text.
     * \param x X coordinate.
     * \param y Y coordinate.
     * \param color Color to use.
     */
    void addTextToScene(QList<QGraphicsItem*>& group, const QColor& color, const QString& text, double x, double y);
    /**
     * Add a rectangle to scene.
     *
     * \param group List of QGraphicsItems.
     * \param x1 First x coordinate.
     * \param x2 Second x coordinate.
     * \param y1 First y coordinate.
     * \param y2 Second y coordinate.
     *
     * \return QGraphicsItem
     */
    QGraphicsItem* addRectToScene(QList<QGraphicsItem*>& group, double x1, double y1, double x2, double y2);
    /**
     * Add a line to the scene.
     *
     * \param group List of QGraphicsItems.
     * \param x1 X coordinate of start point.
     * \param y1 Y coordinate of start point.
     * \param x2 X coordinate of end point.
     * \param y2 Y coordinate of end point.
     */
    void addLineToScene(QList<QGraphicsItem*>& group, double x1, double y1, double x2, double y2);
    /**
     * Add a line to the scene.
     *
     * \param group List of QGraphicsItems.
     * \param x1 X coordinate of start point.
     * \param y1 Y coordinate of start point.
     * \param x2 X coordinate of end point.
     * \param y2 Y coordinate of end point.
     * \param color Color to use.
     */
    void addLineToScene(QList<QGraphicsItem*>& group, const QColor& color, double x1,
                        double y1, double x2, double y2, bool scale = true);

    QList<QGraphicsItem*> m_coordSysGroup;
    QList<QGraphicsItem*> m_functionGroup;
    QList<QGraphicsItem*> m_helperAnimationGroup;

    QTimer* m_timer;
    Function* m_function;

    QPoint m_lastPanPoint;

    double m_scaleBase;
    double m_stepRange;

    Point2D* m_lastPoints;
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
