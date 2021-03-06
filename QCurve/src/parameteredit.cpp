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

#include "parameteredit.h"

#include <QtGui/QKeyEvent>
#include <QtGui/QHBoxLayout>

#include "Widgets/QtMmlWidget"

#include <limits>

#define INF std::numeric_limits<double>::infinity()

ParameterEdit::ParameterEdit(QWidget* parent) : QWidget(parent)
{
  initComponents();

  connect(m_from, SIGNAL(valueChanged(double)), this, SIGNAL(fromValueChanged(double)));
  connect(m_to, SIGNAL(valueChanged(double)), this, SIGNAL(toValueChanged(double)));
}

ParameterEdit::ParameterEdit(const Parameter& param, QWidget* parent)
  : QWidget(parent), m_parameter(param.name())
{
  initComponents();
  setParameter(param);

  connect(m_from, SIGNAL(valueChanged(double)), this, SIGNAL(fromValueChanged(double)));
  connect(m_to, SIGNAL(valueChanged(double)), this, SIGNAL(toValueChanged(double)));
}

void ParameterEdit::initComponents()
{
  m_formula = new QtMmlWidget();

  m_from = new QDoubleSpinBox();
  m_from->setMinimum(-INF);
  m_from->setMaximum(INF);
  m_to = new QDoubleSpinBox();
  m_to->setMinimum(-INF);
  m_to->setMaximum(INF);

  m_from->setKeyboardTracking(false);
  m_to->setKeyboardTracking(false);

  QHBoxLayout* lyt = new QHBoxLayout(this);
  lyt->addWidget(m_from);
  lyt->addWidget(m_formula);
  lyt->addWidget(m_to);
}

void ParameterEdit::setParameter(const Parameter& param)
{
  m_parameter = param.name();

  m_formula->setContent("<math><mo>&lt;</mo><mi>" + m_parameter + "</mi><mo>&gt;</mo></math>");

  m_from->setValue(param.from());
  m_to->setValue(param.to());

  if (!param.interval().lowerEndIsClosed())
  {
    m_from->setMinimum(param.interval().lowerEnd() + 0.01);
    m_to->setMinimum(param.interval().lowerEnd() + 0.01);
  }
  else
  {
    m_from->setMinimum(param.interval().lowerEnd());
    m_to->setMinimum(param.interval().lowerEnd());
  }
  if (!param.interval().upperEndIsClosed())
  {
    m_to->setMaximum(param.interval().upperEnd() - 0.01);
    m_from->setMaximum(param.interval().upperEnd() - 0.01);
  }
  else
  {
    m_to->setMaximum(param.interval().upperEnd());
    m_from->setMaximum(param.interval().upperEnd());
  }

  QString toolTip = QString("<b>%1</b><br/>%2<br/>%3").arg(param.name()).
    arg(param.description()).arg(param.toString());
  setToolTip(toolTip);
}
