#ifndef PARAMETER_H
#define PARAMETER_H

#include <QtCore/QString>
#include <QtCore/QList>

#include "Core/Interval"

/**
 * Represents a mathmatical parameter.
 *
 * A parameter is a kind of variable which has
 * a constant value for a specific case but can be
 * altered for other cases.
 */
class Parameter
{
  public:
    Parameter();
    Parameter(double from, double to, const QString& name, const QString& desc = QString());
    virtual ~Parameter();

    /**
      * The formal name (symbol) of the parameter (usualy 't').
      *
      * \return formal name (symbol) of the parameter
      */
    QString name() const;

    /**
      * Get the description for this parameter.
      *
      * \return description for this parameter
      */
    QString description() const;

    /**
      * Returns the minimum value of the parameter.
      *
      * \return minimum value of the parameter
      */
    double from() const;

    /**
      * Sets the minimum value of the parameter.
      *
      * \param from new minimum value of parameter
      */
    void setFrom(double from);

    /**
      * Returns the maximum value of the parameter.
      *
      * \return maximum value of the parameter
      */
    double to() const;

    /**
      * Sets the maximum value of the parameter
      *
      * \param to new maximum value of parameter
      */
    void setTo(double to);

    //QList<double> excludedValues() const;
    //void setExcludedValues(const QList<double>& excluded);

    /**
     * Get interval of parameter.
     *
     * \return interval of the parameter
     */
    Interval& interval() const { return const_cast<Interval&>(m_interval); }
    /**
     * Set interval for parameter.
     *
     * \param interval new interval
     */
    void setInterval(const Interval& interval);

    /**
      * Get a String representation of the parameter.
      *
      * \return A string representation of the parameter.
      */
    QString toString() const;

  private:
    QString m_name;
    QString m_description;
    QList<double> m_excludedValues;

    double m_to;
    double m_from;
    Interval m_interval;
};

#endif
