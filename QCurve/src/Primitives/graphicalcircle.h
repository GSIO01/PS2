#ifndef PRIMITIVE_CIRCLE_H
#define PRIMITIVE_CIRCLE_H

#include "Core/Point"
#include "Core/Primitive"

class GraphicalCircle : public Primitive
{
  public:
    GraphicalCircle(const Point3D& p, double r,
                    const QString& name, const QString& description = QString());

    const Point3D& midPoint() const { return m_p; }
    void setMidPoint(const Point3D& p);

    double radius() const { return m_r; }
    void setRadius(double r);

    virtual QGraphicsItem* toGraphicsItem() const;

  protected:
    Point3D m_p;
    double m_r;
};

#endif
