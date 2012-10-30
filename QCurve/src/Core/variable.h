#ifndef VARIABLE_H
#define VARIABLE_H

#include <QtCore/QString>

class Variable
{
  public:
    Variable(const QString& name, double value = 0);
    virtual ~Variable();
    
    QString name() const;
    
    double value() const;
    void setValue(double value);
  
    bool operator==(const Variable& other) const;
    
    friend bool operator==(const Variable& constant, const QString& name);
    friend bool operator==(const QString& name, const Variable& constant);
    
  private:
    QString m_name;
    double m_value;
};

#endif
