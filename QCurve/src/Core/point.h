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
