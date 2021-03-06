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

#include "variable.h"

Variable::Variable(const QString& name, double value)
  : m_name(name), m_value(value)
{ }

Variable::~Variable()
{ }

QString Variable::formula() const
{
  if (m_formula.isEmpty())
  { return QString("<math><mi color=\"%1\">%2</mi></math>").arg(m_color.name()).arg(m_name); }

  return m_formula;
}

void Variable::setFormula(const QString& formula)
{ m_formula = formula; }

void Variable::setDescription(const QString& desc)
{ m_description = desc; }

void Variable::setInterval(const Interval& interval)
{ m_interval = interval; }

void Variable::setValue(double value)
{
  if (value < m_interval.lowerEnd()) { m_value = m_interval.lowerEnd(); }
  else if (value > m_interval.upperEnd()) { m_value = m_interval.upperEnd(); }
  else { m_value = value; }
}

void Variable::setColor(const QColor& color) //replace colors...
{ m_color = color; }

bool Variable::operator==(const Variable& other)
{ return m_name == other.m_name; }

bool operator==(const Variable& variable, const QString& name)
{ return variable.m_name == name; }

bool operator==(const QString& name, const Variable& variable)
{ return variable.m_name == name; }
