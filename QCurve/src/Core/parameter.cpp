#include "parameter.h"

#include <limits>

#define INF std::numeric_limits<double>::infinity()

Parameter::Parameter()
{ }

Parameter::Parameter(double from, double to, const QString& name, const QString& desc)
  : m_name(name), m_description(desc), m_to(to), m_from(from)
{ }

Parameter::~Parameter()
{ }

QString Parameter::name() const
{ return m_name; }

QString Parameter::description() const
{ return m_description; }

double Parameter::from() const
{ return m_from; }

void Parameter::setFrom(double from)
{ m_from = from; }

double Parameter::to() const
{ return m_to; }

void Parameter::setTo(double to)
{ m_to = to; }

QString Parameter::toString() const
{
  QString result;

  result += m_name + " " + QChar(0x2208) + " (";
  result += (m_from != -INF) ? QString::number(m_from) : QString("-%1").arg(QChar(0x221E));
  result += ", ";
  result += (m_to != INF) ? QString::number(m_to) : QChar(0x221E);
  result += ")";

  return result;
}

/*QList<double> Parameter::excludedValues() const
{ return m_excludedValues; }

void Parameter::setExcludedValues(const QList<double>& excluded)
{ m_excludedValues = excluded; }*/