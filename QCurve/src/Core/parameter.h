#ifndef PARAMETER_H
#define PARAMETER_H

#include <QtCore/QString>
#include <QtCore/QList>

class Parameter
{
  public:
    Parameter();
    Parameter(double from, double to, const QString& name,
	      const QList<double>& excluded = QList<double>());
    virtual ~Parameter();
    
    QString name() const;
    
    double from() const;
    void setFrom(double from);
    
    double to() const;
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
