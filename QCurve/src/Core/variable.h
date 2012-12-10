#ifndef VARIABLE_H
#define VARIABLE_H

#include <QtCore/QString>

#include "Core/Interval"

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

    QString name() const { return m_name; }

		QString formula() const { return m_formula; }
    void setFormula(const QString& formula);

		QString description() const { return m_description; }
    void setDescription(const QString& desc);

		Interval& interval() const { return const_cast<Interval&>(m_interval); }
    void setInterval(const Interval& interval);

    double value() const { return m_value; }
    void setValue(double value);

    bool operator==(const Variable& constant);

    friend bool operator==(const Variable& constant, const QString& name);
    friend bool operator==(const QString& name, const Variable& constant);

  private:
    QString m_name;
    QString m_formula;
    QString m_description;

    double m_value;

    Interval m_interval;
};

#endif
