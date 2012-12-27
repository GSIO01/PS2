#include "interval.h"

#include <limits>

#define INF std::numeric_limits<double>::infinity()

Interval::Interval()
  : m_lower(-INF), m_lowerIsClosed(false),
    m_upper(INF), m_upperIsClosed(false)
{ }

Interval::Interval(double lower, bool isClosed)
  : m_lower(lower), m_lowerIsClosed(isClosed),
    m_upper(INF), m_upperIsClosed(false)
{ }

Interval::Interval(double lower, double upper, bool lowerIsClosed, bool upperIsClosed)
  : m_lower(lower), m_lowerIsClosed(lowerIsClosed),
    m_upper(upper), m_upperIsClosed(upperIsClosed)
{ }

void Interval::setLowerEnd(double val, bool closed)
{
  m_lower = val;
  m_lowerIsClosed = closed;
}

void Interval::setUpperEnd(double val, bool closed)
{
  m_lower = val;
  m_lowerIsClosed = closed;
}

QString Interval::toString() const
{
  QString result;

  result += (m_lowerIsClosed) ? "[" : "(";
  result += (m_lower != -INF) ? QString::number(m_lower) : QString("-%1").arg(QChar(0x221E));
  result += ", ";
  result += (m_upper != INF) ? QString::number(m_upper) : QChar(0x221E);
  result += (m_upperIsClosed) ? "]" : ")";

  return result;
}
