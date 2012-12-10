#include "interval.h"

#include <limits>

Interval::Interval()
  : m_lower(-std::numeric_limits<double>::infinity()), m_lowerIsClosed(false),
    m_upper(std::numeric_limits<double>::infinity()), m_upperIsClosed(false)
{ }

Interval::Interval(double lower, bool isClosed)
  : m_lower(lower), m_lowerIsClosed(isClosed),
    m_upper(std::numeric_limits<double>::infinity()), m_upperIsClosed(false)
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
  result += QString::number(m_lower) + "," + QString::number(m_upper);
  result += (m_upperIsClosed) ? "]" : ")";

  return result;
} 
