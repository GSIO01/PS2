#ifndef FUNCTION_H
#define FUNCTION_H

#include <QtCore/QString>
#include <QtCore/QRectF>
#include <QtCore/QList>

#include <Core/Variable>
#include <Core/Point>
#include <Core/Parameter>

class Function
{
  public:
    Function(); 
    virtual ~Function();
    
    virtual Function* clone() const = 0;
    
    virtual QString toFormula() const = 0;
    QString name() const { return m_name; }
    
    Parameter& parameter() const;
    void setParameter(const Parameter& param);
    
    QList<Variable> variables() const;
    void setVariable(const Variable& constant);
    void setVariable(const QString& name, double value);
    
    QList<Point> points() const;
    const QRectF& dimension() const;

    virtual double calculateY(double t) const = 0;
    virtual double calculateX(double t) const = 0;
    
  protected:
    QString m_name;
    Parameter m_param;
    QList<Variable> m_variables;
    
    mutable QRectF m_dimension;
    QList<Point> m_points;
};

#endif
 
