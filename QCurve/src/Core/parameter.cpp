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
{
  if (from < m_interval.lowerEnd()) { m_from = m_interval.lowerEnd(); }
  else if (from > m_interval.upperEnd()) { m_from = m_interval.upperEnd(); }
  else { m_from = from; }
}

void Parameter::setInterval(const Interval& interval)
{ m_interval = interval; }

double Parameter::to() const
{ return m_to; }

void Parameter::setTo(double to)
{
  if (to < m_interval.lowerEnd()) { m_to = m_interval.lowerEnd(); }
  else if (to > m_interval.upperEnd()) { m_to = m_interval.upperEnd(); }
  else { m_to = to; }
}

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