#ifndef POINT_H
#define POINT_h

#include <QtCore/QString>

/***
 * Represents a point in space.
 *
 * A point is a ordered pair or rather a ordered triplet of numbers.
 */
class Point
{
  public:
    /*** Constructs a new 2 dimensional point. */
    Point(double x, double y, const QString& name = QString(), const QString& desc = QString());
    /*** Constructs a new point in the 3 dimensional space. */
    Point(double x, double y, double z, const QString& name = QString(), const QString& desc = QString());

    /*** Returns the horizontal component of the point. */
    double X() const;
    /*** Returns the vertical component of the point. */
    double Y() const;
    /*** Returns the depth component of the point. */
    double Z() const;

    /*** Returns a descriptive name e.g. the focal point of an ellipse. */
    QString name() const;

    /*** Returns a description for this point. */
    QString description() const;

    bool operator==(const Point& other);

    Point toRadial() const;
    Point toDegree() const;

    QString toString() const;

  private:
    double m_x;
    double m_y;
    double m_z;

    QString m_name;
    QString m_description;
};

#endif