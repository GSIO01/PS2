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

#ifndef PRIMITIVE_POINT_H
#define PRIMITIVE_POINT_H

#include "Core/Primitive"
#include "Core/Point"

/**
 * Class representing a point primitive.
 *
 * @see Primitive
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
