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

#ifndef VARIABLE_H
#define VARIABLE_H

#include <QtCore/QString>
#include <QtGui/QColor>

#include "Core/Interval"

/**
 * Represents a mathmatical variable.
 *
 * A variable is a value that may change within the calculation.
 */
class Variable
{
  public:
    Variable(const QString& name, double value = 0);
    virtual ~Variable();

    /**
      * Get the name of the variable.
      *
      * \return name of variable
      */
    QString name() const { return m_name; }

    /**
      * Get color of variable.
      *
      * \return color of variable
      */
    QColor color() const { return m_color; }
    /**
      * Set color of variable.
      *
      * \param color new color
      */
    void setColor(const QColor& color);

    /**
      * Get formula for the variable.
      *
      * \return formala for variable
      */
    QString formula() const;
    /**
      * Set formula for variable.
      *
      * \param formula new formula
      */
    void setFormula(const QString& formula);

    /**
      * Get description for variable.
      *
      * \return description for variable
      */
    QString description() const { return m_description; }
    /**
      * Set description for variable.
      *
      * \param desc new description
      */
    void setDescription(const QString& desc);

    /**
      * Get interval of variable.
      *
      * \return interval of variable
      */
    Interval& interval() const { return const_cast<Interval&>(m_interval); }
    /**
    * Set interval for variable.
    *
    * \param interval new interval
    */
    void setInterval(const Interval& interval);

    /**
      * Get value of variable.
      *
      * \return value of variable.
      */
    double value() const { return m_value; }
    /**
      * Set value of variable.
      *
      * \param value new value
      */
    void setValue(double value);

    bool operator==(const Variable& constant);

    friend bool operator==(const Variable& constant, const QString& name);
    friend bool operator==(const QString& name, const Variable& constant);

  private:
    QString m_name;
    QString m_formula;
    QString m_description;
    QColor m_color;

    double m_value;

    Interval m_interval;
};

#endif
