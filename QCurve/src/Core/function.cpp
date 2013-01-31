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

#include "function.h"

#include <QtCore/QDebug>
#include <QtCore/QObject>

Function::Function()
  : m_dimension(QRectF(0, 0, 0, 0)), m_is2Dimensional(true)
{ }

Function::~Function()
{
  //TODO clear/delete helper items -> clone items in copy constructor...
  //for (int i = m_helper.count() - 1; i >= 0; i--)
  //{ delete m_helper.takeAt(i); }
}

void Function::init()
{
  m_calculations = new CalculateMethod[calculations()];
  m_calculations[0] = &Function::calculatePoint;

  Variable var("x0", 0);
  var.setColor(QColor(0, 0, 255));
  var.setFormula("<math><mrow><msub><mi color=\"#0000FF\">x</mi><mr color=\"#00F\">0</mr></msub></mrow></math>");
  var.setDescription(QObject::tr("Moves the function on the x-axis."));
  setVariable(var);

  var = Variable("y0", 0);
  var.setColor(QColor(0, 200, 0));
  var.setFormula("<math><mrow><msub><mi color=\"#00C800\">y</mi><mr color=\"#00C800\">0</mr></msub></mrow></math>");
  var.setDescription(QObject::tr("Moves the function on the y-axis."));
  setVariable(var);
}

Parameter& Function::parameter() const
{ return const_cast<Parameter&>(m_param); }

void Function::setParameter(const Parameter& param)
{
  m_param = param;
  initDimension();
}

void Function::setParameter(double from, double to)
{
  m_param.setFrom(from);
  m_param.setTo(to);
  initDimension();
}

QList<Variable> Function::variables() const
{ return m_variables; }

void Function::updatePoints(const QString& var, double value)
{ Q_UNUSED(var); Q_UNUSED(value); }

double Function::getVariable(const QString& name) const
{
  foreach(const Variable& var, m_variables)
  {
    if (var.name() == name)
    { return var.value(); }
  }

  return 0;
}

void Function::setVariable(const QString& name, double value)
{ setVariable(name, value, true); }

void Function::setVariable(const QString& name, double value, bool triggerUpdate)
{
  Variable tmp(name, value);
  if (m_variables.contains(tmp)) //TODO
  {
    int idx = m_variables.indexOf(tmp);
    Variable c = m_variables.takeAt(idx);
    c.setValue(value);
    m_variables.insert(idx, c);
  }
  else { m_variables.append(Variable(name, value)); }

  if (triggerUpdate)
  {
    initDimension();
    updatePoints(name, value);
  }
}

void Function::setVariable(const Variable& variable)
{
  if (m_variables.contains(variable))
  {
    int idx = m_variables.indexOf(variable);
    m_variables.removeAt(idx);
    m_variables.insert(idx, variable);
  }
  else { m_variables.append(variable); }
}

Primitive* Function::getHelperItem(const QString& name) const
{
  for (int i = 0; i < m_helper.count(); i++)
  {
    Primitive* item = m_helper.at(i);
    if (item->name() == name)
    { return item; }
  }

  return 0;
}

QList<Primitive*> Function::helperItems() const
{ return m_helper; }

const QRectF& Function::dimension() const
{ return m_dimension; }
