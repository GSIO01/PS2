#ifndef FUNCTION_H
#define FUNCTION_H

#include <QtCore/QString>
#include <QtCore/QRectF>
#include <QtCore/QList>

#include "Core/Variable"
#include "Core/Parameter"
#include "Core/Point"
#include "Core/Primitive"

/***
 * Represents a (abstract) class for mathmatical functions.
 */
class Function
{
  public:
    Function();
    virtual ~Function();

    /*** Creates a copy of the current function. */
    virtual Function* clone() const = 0;

    /*** Returns parametric form as formula in MathMl. */
    virtual QString toParametricFormula() const = 0;

    /*** Returns the name of the function class. */
    QString name() const { return m_name; }

    bool is2Dimensional() const { return m_is2Dimensional; }

    /*** Returns the parameter. */
    Parameter& parameter() const;

    /*** Replaces the current parameter with a new one. */
    void setParameter(const Parameter& param);

    /*** Returns a list of all variables. */
    QList<Variable> variables() const;

    /*** Returns the value of the specified variable. */
    double getVariable(const QString& name) const;

    void setVariable(const QString& name, double value);

    /*** Returns a list of helper primitves. */
    QList<Primitive*> helperItems() const;

    /*** Returns the boundaries as rectangle. */
    const QRectF& dimension() const;

    virtual Point3D calculatePoint(double t) const = 0;

  protected:
    void setVariable(const QString& name, double value, bool triggerUpdate);
    void setVariable(const Variable& var);

    /*** Helper function to update points after a variable has changed. */
    virtual void updatePoints(const QString& var = QString(), double value = 0);
    /*** Calculates the boundaries. */
    virtual void initDimension() = 0;

    Primitive* getHelperItem(const QString& name) const;

    QString m_name;
    Parameter m_param;
    QList<Variable> m_variables;

    QRectF m_dimension;
    QList<Primitive*> m_helper;

    bool m_is2Dimensional;
};

#endif
