#ifndef POINT_H
#define POINT_H

#include <QtCore/QString>

class Point2D
{
  public:
    Point2D(double x = 0, double y = 0);

    double x() const { return m_x; }
    double y() const { return m_y; }

    QString toString() const;

    bool operator==(const Point2D& other) const;

  protected:
    double m_x;
    double m_y;
};

class Point3D
{
  public:
    Point3D(double x = 0, double y = 0, double z = 0);

    double x() const { return m_x; }
    double y() const { return m_y; }
    double z() const { return m_z; }

    QString toString() const;

    bool operator==(const Point3D& other) const;

  protected:
    double m_x;
    double m_y;
    double m_z;
};

#endif
