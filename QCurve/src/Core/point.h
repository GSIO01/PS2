#ifndef POINT_H
#define POINT_H

#include <QtCore/QString>

/**
 * Implements a 2 dimensional point.
 */
class Point2D
{
  public:
    Point2D(double x = 0, double y = 0);

	/**
	 * Get the x coordinate.
	 *
	 * \return x coordinate.
	 */
    double x() const { return m_x; }
	/**
	 * Get the y coordinate.
	 *
	 * \return y coordinate.
	 */
    double y() const { return m_y; }

	/**
	 * Get a string representation for debuging purposes.
	 *
	 * \return string representation of the point.
	 */
    QString toString() const;

    bool operator==(const Point2D& other) const;

  protected:
    double m_x;
    double m_y;
};

/**
 * Implements a 3 dimensional point.
 */
class Point3D
{
  public:
    Point3D(double x = 0, double y = 0, double z = 0);

	/**
	 * Get the x coordinate.
	 *
	 * \return x coordinate.
	 */
    double x() const { return m_x; }
	/**
	 * Get the y coordinate.
	 *
	 * \return y coordinate.
	 */
	double y() const { return m_y; }
	/**
	 * Get the z coordinate.
	 *
	 * \return z coordinate.
	 */
    double z() const { return m_z; }

	/**
	 * Get a string representation for debuging purposes.
	 *
	 * \return string representation of the point.
	 */
    QString toString() const;

    bool operator==(const Point3D& other) const;

  protected:
    double m_x;
    double m_y;
    double m_z;
};

#endif
