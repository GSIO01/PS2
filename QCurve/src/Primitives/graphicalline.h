#ifndef PRIMITIVE_LINE_H
#define PRIMITIVE_LINE_H

#include "Core/Point"
#include "Core/Primitive"

/**
 * Class representing a line primitive.
 * 
 * @see Primitive
 */
class GraphicalLine : public Primitive
{
  public:
    /**
     * Constructor.
     *
     * \param start The start point.
     * \param end The end point.
     * \param name Name of the line.
     * \param description Optional description.
     */
    GraphicalLine(const Point3D& start, const Point3D& end, const QString& name,
         const QString& description = QString());

    /**
     * Get the start point of the line.
     *
     * \return The start point.
     */
    const Point3D& start() const { return m_start; }
    /**
     * Set the start point of the line.
     *
     * \param p New start point.
     */
    void setStartPoint(const Point3D& p);

    /**
     * Get the end point of the line.
     *
     * \return The end point.
     */
    const Point3D& end() const { return m_end; }
    /**
     * Set the end point of the line.
     *
     * \param p New end point.
     */
    void setEndPoint(const Point3D& p);

    /**
     * Create a QGraphicsItem for the line.
     *
     * \return QGraphicsItem for the line.
     */
    virtual QGraphicsItem* toGraphicsItem() const;
    
    /**
     * Update the QGraphicsItem.
     * 
     * \param item item to update
     */
    virtual void updateGraphicsItem(QGraphicsItem* item) const;

  protected:
    Point3D m_start; /**< The lines start point. */
    Point3D m_end; /**< The lines end point. */
};

#endif
