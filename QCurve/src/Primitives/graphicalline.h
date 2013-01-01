#ifndef PRIMITIVE_LINE_H
#define PRIMITIVE_LINE_H

#include "Core/Point"
#include "Core/Primitive"

class GraphicalLine : public Primitive
{
  public:
    GraphicalLine(const Point3D& start, const Point3D& end, const QString& name,
         const QString& description = QString());

    const Point3D& start() const { return m_start; }
    void setStartPoint(const Point3D& p);

    const Point3D& end() const { return m_end; }
    void setEndPoint(const Point3D& p);

    virtual QGraphicsItem* toGraphicsItem() const;

  protected:
    Point3D m_start;
    Point3D m_end;
};

#endif
