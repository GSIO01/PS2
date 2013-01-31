/*
 * (C) Copyright 2012-2013 QCurve Team
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser General Public License
 * (LGPL) version 2.1 which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl-2.1.html
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 */

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
  m_upper = val;
  m_upperIsClosed = closed;
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
