#ifndef PRIMITIVE_POINT_H
#define PRIMITIVE_POINT_H

#include "Core/Primitive"
#include "Core/Point"

class GraphicalPoint : public Primitive
{
  public:
    GraphicalPoint(const Point3D& p, const QString& name, const QString& description = QString());

    const Point3D& point() const { return m_p; }
    void setPoint(const Point3D& point);

    virtual QGraphicsItem* toGraphicsItem() const;

  protected:
    Point3D m_p;
};

#endif
