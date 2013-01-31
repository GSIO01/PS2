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

#ifndef FUNCTION_H
#define FUNCTION_H

#include <QtCore/QCoreApplication>

#include <QtCore/QString>
#include <QtCore/QRectF>
#include <QtCore/QList>

#include "Core/Variable"
#include "Core/Parameter"
#include "Core/Point"
#include "Core/Primitive"

/**
 * Represents a (abstract) class for mathmatical functions.
 *
 * @see Parameter
 * @see Variable
 * @see Primitive
 */
class Function
{
  public:
    Function();
    virtual ~Function();

    /**
     * Creates a copy of the current function.
     *
     * \return Copy of the current function.
     */
    virtual Function* clone() const = 0;

    /**
     * Returns parametric form as formula in MathMl.
     *
     * \return Parametric form as formula in MathMl.
     */
    virtual QString toParametricFormula() const = 0;

    /**
     * Returns the name of the function class.
     *
     * \return Name of the function class
     */
    QString name() const { return m_name; }

    /**
     * Returns whether this function is a 2D function.
     *
     * \return Is a 2D function?
     */
    bool is2Dimensional() const { return m_is2Dimensional; }

    /**
     * Returns the parameter.
     *
     * \return Parameter.
     */
    Parameter& parameter() const;

    /**
     * Replaces the current parameter with a new one.
     *
     * \param param New Parameter.
     */
    void setParameter(const Parameter& param);

    /**
     * Set the parameter to the given values.
     *
     * \param from new from value
     * \param to new to value
     */
    void setParameter(double from, double to);

    /**
     * Returns a list of all variables.
     *
     * \return List of all variables.
     */
    QList<Variable> variables() const;

    /**
     * Returns the value of the specified variable.
     *
     * \param name Name of variable.
     * \return Value of specified variable.
     */
    double getVariable(const QString& name) const;

    /**
     * Sets value of a specified variable to the specified value.
     *
     * \param name Variable name.
     * \param value New value.
     */
    void setVariable(const QString& name, double value);

    /**
     * Returns a list of helper primitves.
     *
     * \return List of helper primitves.
     */
    QList<Primitive*> helperItems() const;

    /**
     * Returns the boundaries as rectangle.
     *
     * \return Boundaries as rectangle.
     */
    const QRectF& dimension() const;

    /**
     * Returns the number of calculation methods.
     */
    virtual int calculations() const { return 1; }

    /**
     * Caluclate point for a given function index and value t. (Multifunction support)
     *
     * \param idx function index
     * \param t parameter
     */
    Point3D calculate(int idx, double t) const
    { return (this->*m_calculations[idx])(t); }

  protected:
    typedef Point3D (Function::*CalculateMethod)(double) const;
    Function::CalculateMethod* m_calculations;

    /**
     * Calculates and returns the coordinates of the function for the giving parameter value.
     *
     * \param t Parameter value.
     * \return Coordinates.
     */
    virtual Point3D calculatePoint(double t) const = 0;

    /**
     * Set variable.
     *
     * \param name New name.
     * \param value New value.
     * \param triggerUpdate Trigger update?
     */
    void setVariable(const QString& name, double value, bool triggerUpdate);
    /**
     * Set variable.
     *
     * \param var Reference to other variable.
     */
    void setVariable(const Variable& var);

    /**
     * Initialization function.
     */
    void init();

    /**
     * Helper function to update points after a variable has changed.
     *
     * \param var Variable that has changed.
     * \param value New value.
     */
    virtual void updatePoints(const QString& var = QString(), double value = 0);

    /** Calculates the boundaries. */
    virtual void initDimension() = 0;

    /**
     * Returns the specified helper item.
     *
     * \param name Name of helper item.
     */
    Primitive* getHelperItem(const QString& name) const;

    QString m_name;
    Parameter m_param;

    /** @Note Use @link setVariable to add/set a variable since it will
     *  maintain the order,
     *  This makes it saves to assume that e.g x0/y1 is at index 0/1.
     *
     *  Both \c x0 and \c y0 are already defined since all functions use them.
     */
    QList<Variable> m_variables;

    QRectF m_dimension;
    QList<Primitive*> m_helper;

    bool m_is2Dimensional;
};

#endif
