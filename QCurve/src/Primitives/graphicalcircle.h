#ifndef PRIMITIVE_CIRCLE_H
#define PRIMITIVE_CIRCLE_H

#include "Core/Point"
#include "Core/Primitive"

/**
 * Class representing a circle primitive.
 */
class GraphicalCircle : public Primitive
{
  public:
    /**
     * Constructor.
     * 
     * \param p Center point.
     * \param r Radius of the circle.
     * \param name Name of the circle.
     * \param description Optional description.
     */
    GraphicalCircle(const Point3D& p, double r,
                    const QString& name, const QString& description = QString());

    /**
     * Get the mid point of the circle.
     * 
     * \return The circles mid point.
     */
    const Point3D& midPoint() const { return m_p; }
    /**
     * Set the mid point of the circle.
     * 
     * \param p The new mid point.
     */
    void setMidPoint(const Point3D& p);

    /**
     * Get the radius of the circle.
     * 
     * \return Radius of the circle
     */
    double radius() const { return m_r; }
    /**
     * Set radius of the circle.
     * 
     * \param r New radius.
     */
    void setRadius(double r);

    /**
     * Create a QGraphicsItem for the circle.
     * 
     * \return QGraphicsItem for the circle.
     */
    virtual QGraphicsItem* toGraphicsItem() const;

  protected:
    Point3D m_p; /**<  The mid point. */
    double m_r; /**< The radius. */
};

#endif
