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

#ifndef PRIMITIVE_CIRCLE_H
#define PRIMITIVE_CIRCLE_H

#include "Core/Point"
#include "Core/Primitive"

/**
 * Class representing a circle primitive.
 *
 * @see Primitive
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

    /**
     * Update the QGraphicsItem.
     *
     * \item item to update
     */
    virtual void updateGraphicsItem(QGraphicsItem* item) const;

  protected:
    Point3D m_p; /**<  The mid point. */
    double m_r; /**< The radius. */
};

#endif
