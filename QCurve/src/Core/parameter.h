#ifndef PARAMETER_H
#define PARAMETER_H

#include <QtCore/QString>
#include <QtCore/QList>

/***
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
    Parameter(double from, double to, const QString& name, const QList<double>& excluded = QList<double>());
    virtual ~Parameter();

    /*** The formal name (symbol) of the parameter (usualy 't'). */
    QString name() const;

    /*** Returns the minimum value of the parameter. */
    double from() const;

    /*** Sets the minimum value of the parameter. */
    void setFrom(double from);

    /*** Returns the maximum value of the parameter. */
    double to() const;

    /*** Sets the maximum value of the parameter*/
    void setTo(double to);

    QList<double> excludedValues() const;
    void setExcludedValues(const QList<double>& excluded);

  private:
    QString m_name;
    QList<double> m_excludedValues;

    double m_to;
    double m_from;
};

#endif
