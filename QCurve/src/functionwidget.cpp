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

#include "functionwidget.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QSplitter>

#include "Widgets/QtMmlWidget"
#include "Graph2D"
#include "VariableEdit"
#include "ParameterEdit"

/**
 * Implements a widget for mathematical functions.
 */
FunctionWidget::FunctionWidget(QWidget* parent) : QWidget(parent)
{
  initComponents();

  connect(m_paramEdit, SIGNAL(fromValueChanged(double)), this, SLOT(fromValueChanged(double)));
  connect(m_paramEdit, SIGNAL(toValueChanged(double)), this, SLOT(toValueChanged(double)));

  connect(m_plotter, SIGNAL(scaleFactorChanged(int)), this, SLOT(updateScaleFactor(int)));
  connect(m_scaleFactor, SIGNAL(valueChanged(int)), this, SLOT(updateScaleFactor(int)));

  connect(m_plotter, SIGNAL(currentPositionChanged(double,double)), this, SLOT(positionChanged(double, double)));
}

FunctionWidget::~FunctionWidget()
{ }

const Function& FunctionWidget::function() const
{ return m_plotter->function(); }

void FunctionWidget::setFunction(const Function& function)
{
  m_plotter->plot(function);
  m_specification->setTitle(function.name());
  m_paramEdit->setParameter(function.parameter());

  //delete old input fields for variables
  for (int i = m_variablesLyt->count() - 1; i >= 0; i--) //TODO reuse exitings items
  {
    QLayoutItem* item =  m_variablesLyt->takeAt(i);
    delete item->widget();
    delete item;
  }

  int items = 0;
  foreach(const Variable& variable, function.variables())
  {
    VariableEdit* varEdit = new VariableEdit(variable);
    m_variablesLyt->addWidget(varEdit);
    items++;

    connect(varEdit, SIGNAL(valueChanged(QString,double)), this, SLOT(varValueChanged(QString,double)));
  }
  m_varInputPanel->setMaximumHeight(41 * items);//FIXME value should be calculated by using varEdit...

  m_specification->setMaximumHeight(m_specification->sizeHint().height() + (items - 2) * 41);

  updateFormula();
}

void FunctionWidget::initComponents()
{
  m_specification = new QGroupBox("Function"); //is replaced with function name at runtime
  m_specification->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  m_paramVar = new QGroupBox(tr("Parameter && Variables"));
  m_paramVar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  m_formula = new QtMmlWidget();
  m_formula->setMinimumSize(QSize(m_specification->maximumSize().width(), 90));

  m_paramEdit = new ParameterEdit();

  m_variablesLyt = new QVBoxLayout();
  m_variablesLyt->setSizeConstraint(QLayout::SetMinAndMaxSize);
  m_varInputPanel = new QScrollArea(); //Grp 'Variables' (basic) layout
  m_varInputPanel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  m_varInputPanel->setFrameShadow(QFrame::Plain);
  m_varInputPanel->setWidgetResizable(true);
  QWidget* tmp = new QWidget();
  tmp->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  tmp->setLayout(m_variablesLyt);
  m_varInputPanel->setWidget(tmp);

  QBoxLayout* lyt = new QVBoxLayout(m_paramVar);
  lyt->addWidget(m_paramEdit);
  lyt->addWidget(m_varInputPanel);

  lyt = new QVBoxLayout(m_specification);
  lyt->addWidget(m_formula);
  lyt->addWidget(m_paramVar);

  m_plotter = new Graph2D();

  QSplitter* splitter = new QSplitter();
  splitter->setOrientation(Qt::Vertical);
  splitter->addWidget(m_specification);
  splitter->addWidget(m_plotter);

  m_scaleFactor = new QSlider();
  m_scaleFactor->setOrientation(Qt::Horizontal);
  m_scaleFactor->setMinimum(50);
  m_scaleFactor->setMaximum(400);

  m_scaleFactorLbl = new QLabel("100%");

  m_statusBar = new QStatusBar();
  m_statusBar->addPermanentWidget(m_scaleFactor);
  m_statusBar->addPermanentWidget(m_scaleFactorLbl);

  lyt = new QVBoxLayout(this);
  lyt->addWidget(splitter);
  lyt->addWidget(m_statusBar);
}

void FunctionWidget::fromValueChanged(double value)
{ m_plotter->setParameter(value, m_paramEdit->to()); }

void FunctionWidget::toValueChanged(double value)
{ m_plotter->setParameter(m_paramEdit->from(), value); }

void FunctionWidget::varValueChanged(const QString& var, double value)
{ m_plotter->setVariable(var, value); }

void FunctionWidget::positionChanged(double x, double y)
{
  m_statusBar->clearMessage();
  m_statusBar->showMessage(tr("Mouse Position(%1, %2)").
    arg(QString::number(x, 'f', 2)).arg(QString::number(y, 'f', 2)));
}

void FunctionWidget::setShowGrid(bool isVisible)
{ m_plotter->setShowGrid(isVisible); }

void FunctionWidget::setAnimationMode(int delay, bool repeat)
{ m_plotter->setAnimationDelay(delay, repeat); }

void FunctionWidget::setUseAntialiasing(bool useAntialiasing)
{ m_plotter->setUseAntialiasing(useAntialiasing); }

void FunctionWidget::updateFormula()
{
  QString errMsg;
  int errLine, errColumn;
  bool result = m_formula->setContent(m_plotter->function().toParametricFormula(),
                                      &errMsg, &errLine, &errColumn);
  if (!result)
  {
    qDebug() << "Parse error: " + errMsg +
      "(line " + QString::number(errLine) +
      ", col " + QString::number(errColumn) + ")";
  }
}

void FunctionWidget::updateScaleFactor(int value)
{
  if (sender() == m_plotter)
  { m_scaleFactor->setValue(value); }
  else if (sender() == m_scaleFactor)
  { m_plotter->setScaleFactor(value); }
  m_scaleFactorLbl->setText(QString("%1%").arg(QString::number(value)));
}
