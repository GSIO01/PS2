#include "functionwidget.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QScrollArea>
#include <QtGui/QSplitter>

#include <Widgets/QtMmlWidget>

#include <Graph2D>

#include <Functions/Ellipse> //TODO

FunctionWidget::FunctionWidget(QWidget* parent) : QWidget(parent)
{ 
  initComponents();

  connect(m_paramFrom, SIGNAL(valueChanged(double)), this, SLOT(fromValueChanged(double)));
  connect(m_paramTo, SIGNAL(valueChanged(double)), this, SLOT(toValueChanged(double)));
  
  setFunction(Ellipse(20, 30));
}

FunctionWidget::~FunctionWidget()
{ }

const Function& FunctionWidget::function() const
{ return *m_function; }

void FunctionWidget::setFunction(const Function& function)
{
  if (m_function)
  { delete m_function; }
  
  m_function = function.clone();
  
  QString error_msg;
  int error_line, error_column;
  bool result = m_mmlWgt->setContent(m_function->toFormula());
  
  if (!result)
  {
    qDebug() << "Parse error: " + error_msg +
                "(line " + QString::number(error_line) +
                ", col " + QString::number(error_column) + ")";
  }
  
  m_paramFrom->setValue(m_function->parameter().from());
  m_paramTo->setValue(m_function->parameter().to());
  
  for (int i = m_variablesLyt->count() - 1; i >= 0; i--) //TODO reuse exitings items
  { delete m_variablesLyt->takeAt(i); }
  
  foreach(const Variable& variable, m_function->variables())
  {
    QLabel* name = new QLabel(variable.name());
    QDoubleSpinBox* value = new QDoubleSpinBox();
    value->setObjectName(variable.name());
    value->setValue(variable.value());
    connect(value, SIGNAL(valueChanged(double)), this, SLOT(varValueChanged(double)));
    
    QHBoxLayout* lyt = new QHBoxLayout();
    lyt->addWidget(name);
    lyt->addWidget(value);
    
    m_variablesLyt->addLayout(lyt);
  }
  
  m_plotter->plot(*m_function);
}

void FunctionWidget::initComponents()
{ 
  QGroupBox* specification = new QGroupBox(tr("Function specification"));
  QGroupBox* parameter = new QGroupBox(tr("Parameter"));
  QGroupBox* variables = new QGroupBox(tr("Variables"));
  
  m_paramFrom = new QDoubleSpinBox();
  m_paramTo = new QDoubleSpinBox();
  m_plotter = new Graph2D();
  m_mmlWgt = new QtMmlWidget();
  
  m_variablesLyt = new QVBoxLayout();
  
  QBoxLayout* lyt = new QHBoxLayout(parameter); //Grp 'Parameter' layout
  lyt->addWidget(new QLabel(tr("From: ")));
  lyt->addWidget(m_paramFrom);
  lyt->addWidget(new QLabel(tr("To: ")));
  lyt->addWidget(m_paramTo);
 
  QScrollArea* scrollArea = new QScrollArea(); //Grp 'Variables' (basic) layout
  scrollArea->setWidgetResizable(true);
  QWidget* dummyWgt = new QWidget();
  dummyWgt->setLayout(m_variablesLyt);
  scrollArea->setWidget(dummyWgt);
  
  lyt = new QVBoxLayout(variables);
  lyt->addWidget(scrollArea);
  
  lyt = new QVBoxLayout(specification); //Grp 'Function Specification')
  lyt->addWidget(m_mmlWgt);
  lyt->addWidget(parameter);
  lyt->addWidget(variables);
 
  QSplitter* splitter = new QSplitter();
  splitter->setOrientation(Qt::Vertical);
  splitter->addWidget(specification);
  splitter->addWidget(m_plotter);
  
  lyt = new QHBoxLayout(this);
  lyt->addWidget(splitter);
}

void FunctionWidget::fromValueChanged(double value)
{
  m_function->parameter().setFrom(value);
  
  QString error_msg;
  int error_line, error_column;
  bool result = m_mmlWgt->setContent(m_function->toFormula());
  if (!result)
  {
    qDebug() << "Parse error: " + error_msg +
                "(line " + QString::number(error_line) +
                ", col " + QString::number(error_column) + ")";
  }
  
  m_plotter->plot(*m_function);
}

void FunctionWidget::toValueChanged(double value)
{
  m_function->parameter().setTo(value);
  
  QString error_msg;
  int error_line, error_column;
  bool result = m_mmlWgt->setContent(m_function->toFormula());
  if (!result)
  {
    qDebug() << "Parse error: " + error_msg +
                "(line " + QString::number(error_line) +
                ", col " + QString::number(error_column) + ")";
  }
  
  m_plotter->plot(*m_function);
}

void FunctionWidget::varValueChanged(double value)
{
  m_function->setVariable(sender()->objectName(), value);
  
  QString error_msg;
  int error_line, error_column;
  bool result = m_mmlWgt->setContent(m_function->toFormula());
  if (!result)
  {
    qDebug() << "Parse error: " + error_msg +
                "(line " + QString::number(error_line) +
                ", col " + QString::number(error_column) + ")";
  }
  
  m_plotter->plot(*m_function);
}