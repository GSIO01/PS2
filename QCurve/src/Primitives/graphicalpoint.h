#ifndef PRIMITIVE_POINT_H
#define PRIMITIVE_POINT_H

#include "Core/Primitive"
#include "Core/Point"

/**
 * Class representing a point primitive.
 */
class GraphicalPoint : public Primitive
{
  public:
    /**
     * Constructor.
     *
     * \param p The point.
     * \param name The points name.
     * \param description Optional description.
     */
    GraphicalPoint(const Point3D& p, const QString& name,
                   const QString& description = QString());

    /**
     * Get the point.
     *
     * \return The point.
     */
    const Point3D& point() const { return m_p; }
    /**
     * Set the point to new coordinates.
     *
     * \param point New point.
     */
    void setPoint(const Point3D& point);

    /**
     * Create a QGraphicsItem for the point.
     *
     * \return QGraphicsItem for the point.
     */
    virtual QGraphicsItem* toGraphicsItem() const;
    
    /**
     * Update the QGraphicsItem.
     * 
     * \param item item to update
     */
    virtual void updateGraphicsItem(QGraphicsItem* item) const;

  protected:
    Point3D m_p; /**< The point. */
};

#endif
