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

  QString toolTip = QString("<b>%1</b><br/>%2<br/>%3").arg(param.name()).
    arg(param.description()).arg(param.toString());
  setToolTip(toolTip);
}
