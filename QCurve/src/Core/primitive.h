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

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QtCore/QString>

#include <QtGui/QColor>
#include <QtGui/QGraphicsItem>

/**
 * Base class for all graphical helper objects of functions (e.g. the
 * rolling circle which generates a cycloid).
 */
class Primitive
{
  public:
    /**
      * Different primitive types.
      */
    enum PrimitiveType
    {
      PT_Point,
      PT_Line,
      PT_Circle
    };

    Primitive(PrimitiveType type, const QString& name,
              const QString& description = QString());

    /**
    * Get name of the primitive.
    *
    * \return name of primitive
    */
    QString name() const { return m_name; }
    /**
      * Get type of the primitive.
      *
      * \return type of primitive
      */
    PrimitiveType type() const { return m_type; }

    /**
      * Get the description for the primitive.
      *
      * \return description of primitive.
      */
    QString description() const { return m_description; }
    /**
    * Set description for the primitive.
    *
    * \param m_description new description
    */
    void setDescription(const QString& m_description);

    /**
      * Get the color of the primitive.
      *
      * \return color of primitive
      */
    QColor color() const { return m_color; }
    /**
      * Set color of primitive.
      *
      * \param color new color
      */
    void setColor(const QColor& color);

    /**
      * Check if primitive is animated.
      *
      * \return whether primitive is animated
      */
    bool isAnimated() const { return m_isAnimated; }
    /**
      * Set if primitive is animated.
      *
      * \param isAnimated true if animated
      */
    void setIsAnimated(bool isAnimated);

    /**
      * Convert to QGraphicsItem.
      *
      * \return QGraphicsItem for the primitive.
      */
    virtual QGraphicsItem* toGraphicsItem() const = 0;
    /**
      * Update graphics item.
      *
      * \param item item to update
      */
    virtual void updateGraphicsItem(QGraphicsItem* item) const = 0;

    bool operator==(const Primitive& other);

  protected:
    PrimitiveType m_type;

    QString m_name;
    QString m_description;
    QColor m_color;

    bool m_isAnimated;
};

#endif
