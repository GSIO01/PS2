#ifndef FUNCTION_H
#define FUNCTION_H

#include <QtCore/QString>
#include <QtCore/QRectF>
#include <QtCore/QList>

#include "Core/Variable"
#include "Core/Point"
#include "Core/Parameter"

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
    
    /*** Returns the parameter. */
    Parameter& parameter() const;
    
    /*** Replaces the current parameter with a new one. */
    void setParameter(const Parameter& param);
    
    /*** Returns a list of all variables. */
    QList<Variable> variables() const;

    /*** Returns the value of the specified variable. */
    double getVariable(const QString& name) const;
    
    void setVariable(const Variable& var);
    void setVariable(const QString& name, double value);
    
    /*** Returns a list of prominent points. */
    QList<Point> points() const;
    
    /*** Returns the boundaries as rectangle. */
    const QRectF& dimension() const;

    virtual double calculateY(double t) const = 0;
    virtual double calculateX(double t) const = 0;
    virtual double calculateZ(double t) const = 0;
    
  protected:
    QString m_name;
    Parameter m_param;
    QList<Variable> m_variables;
    
    mutable QRectF m_dimension;
    QList<Point> m_points;
};

#endif
 
