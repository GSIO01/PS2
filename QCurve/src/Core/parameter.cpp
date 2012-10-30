#include "parameter.h"

Parameter::Parameter()
{ }

Parameter::Parameter(double from, double to, const QString& name,
                     const QList<double>& excluded)
  : m_name(name), m_to(to), m_from(from), m_excludedValues(excluded)
{ }

Parameter::~Parameter()
{ }

QString Parameter::name() const
{ return m_name; }

double Parameter::from() const
{ return m_from; }

void Parameter::setFrom(double from)
{ m_from = from; }

double Parameter::to() const
{ return m_to; }

void Parameter::setTo(double to)
{ m_to = to; }

QList<double> Parameter::excludedValues() const
{ return m_excludedValues; }

void Parameter::setExcludedValues(const QList<double>& excluded)
{ m_excludedValues = excluded; }