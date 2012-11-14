#ifndef VARIABLE_H
#define VARIABLE_H

#include <QtCore/QString>

/***
 * Represents a mathmatical variable.
 * 
 * A variable is a value that may change within the calculation.
 */
class Variable
{
  public:
    Variable(const QString& name, double value = 0);
    virtual ~Variable();
    
    /*** Returns the name (symbol) of the variable. */
    QString name() const;
    
    /*** Returns the current value of the variable. */
    double value() const;
    
    /*** Sets the current value of the variable. */
    void setValue(double value);
    
    bool operator==(const Variable& constant);
    
    friend bool operator==(const Variable& constant, const QString& name);
    friend bool operator==(const QString& name, const Variable& constant);
    
  private:
    QString m_name;
    double m_value;
};

#endif
