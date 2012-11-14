#include "functionwidget.h"

#include <float.h> //TODO

#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QSplitter>

#include "Widgets/QtMmlWidget"
#include "Graph2D"

FunctionWidget::FunctionWidget(QWidget* parent) : QWidget(parent),
  m_function(0)
{ 
  initComponents();

  connect(m_paramFrom, SIGNAL(valueChanged(double)), this, SLOT(fromValueChanged(double)));
  connect(m_paramTo, SIGNAL(valueChanged(double)), this, SLOT(toValueChanged(double)));
}

FunctionWidget::~FunctionWidget()
{ }

const Function& FunctionWidget::function() const
{ return *m_function; }

void FunctionWidget::setFunction(const Function& function)
{
  if (m_function)
  { delete m_function; }
  
  //the copy constructor can't be virtual -> use clone pattern here
  m_function = function.clone();
  
  updateFormula();
  
  m_paramFrom->setValue(m_function->parameter().from());
  m_paramTo->setValue(m_function->parameter().to());
  
  //delete old input fields for variables
  for (int i = m_variablesLyt->count() - 1; i >= 0; i--) //TODO reuse exitings items
  { 
    QLayoutItem* item =  m_variablesLyt->takeAt(i);
    for (int j = item->layout()->count() - 1; j >= 0; j--)
    {
      
      QLayoutItem* subItem = item->layout()->takeAt(j);
      delete subItem->widget();
      delete subItem;
    }
    delete item;
    delete m_variablesLyt->takeAt(i); 
  } 
  
  //construct a label & input field for each variable
  int maxHeight = 0;
  foreach(const Variable& variable, m_function->variables())
  {
    QLabel* name = new QLabel(variable.name());
    QDoubleSpinBox* value = new QDoubleSpinBox();
    value->setRange(-DBL_MAX, DBL_MAX);
    value->setObjectName(variable.name());
    value->setValue(variable.value());
    connect(value, SIGNAL(valueChanged(double)), this, SLOT(varValueChanged(double)));
    
    QHBoxLayout* lyt = new QHBoxLayout(); 
    lyt->addWidget(name);
    lyt->addWidget(value);
    
    m_variablesLyt->addLayout(lyt);
    maxHeight += 48; //TODO
  }
  m_varInputPanel->setMaximumSize(QSize(m_varInputPanel->maximumSize().width(), maxHeight));
  
  m_plotter->plot(*m_function);
}

void FunctionWidget::initComponents()
{ 
  QGroupBox* specification = new QGroupBox(tr("Function specification"));
  specification->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
  QGroupBox* parameter = new QGroupBox(tr("Parameter"));
  parameter->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
  QGroupBox* variables = new QGroupBox(tr("Variables"));
  variables->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
  
  m_paramFrom = new QDoubleSpinBox();
  m_paramFrom->setRange(-DBL_MAX, DBL_MAX);
  m_paramTo = new QDoubleSpinBox();
  m_paramTo->setRange(-DBL_MAX, DBL_MAX);
  m_plotter = new Graph2D();
  m_mmlWgt = new QtMmlWidget();
  
  
  m_variablesLyt = new QVBoxLayout();
  
  QBoxLayout* lyt = new QHBoxLayout(parameter); //Grp 'Parameter' layout
  lyt->addWidget(new QLabel(tr("From: ")));
  lyt->addWidget(m_paramFrom);
  lyt->addWidget(new QLabel(tr("To: ")));
  lyt->addWidget(m_paramTo);
 
  m_varInputPanel = new QScrollArea(); //Grp 'Variables' (basic) layout
  //m_varInputPanel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  m_varInputPanel->setWidgetResizable(true);
  QWidget* tmp = new QWidget();
  tmp->setLayout(m_variablesLyt);
  m_varInputPanel->setWidget(tmp);
  
  lyt = new QVBoxLayout(variables);
  lyt->addWidget(m_varInputPanel);
  
  lyt = new QVBoxLayout(specification); //Grp 'Function Specification')
  lyt->addWidget(m_mmlWgt);
  lyt->addWidget(parameter);
  lyt->addWidget(variables);
 
  //TODO Use a reimplemented splitter which respects the max.size of a widget
  /*QSplitter* splitter = new QSplitter();
  splitter->setOrientation(Qt::Vertical);
  splitter->addWidget(specification);
  splitter->addWidget(m_plotter);*/
  
  lyt = new QVBoxLayout(this);
  //lyt->addWidget(splitter);
  lyt->addWidget(specification);
  lyt->addWidget(m_plotter);
}

void FunctionWidget::fromValueChanged(double value)
{
  m_function->parameter().setFrom(value);
  updateFormula();
  m_plotter->plot(*m_function);
}

void FunctionWidget::toValueChanged(double value)
{
  m_function->parameter().setTo(value);
  updateFormula();
  m_plotter->plot(*m_function);
}

void FunctionWidget::varValueChanged(double value)
{
  m_function->setVariable(sender()->objectName(), value);
  updateFormula();
  m_plotter->plot(*m_function);
}

void FunctionWidget::updateFormula()
{
  QString error_msg;
  int error_line, error_column;
  bool result = m_mmlWgt->setContent(m_function->toParametricFormula());
  if (!result)
  {
    qDebug() << "Parse error: " + error_msg +
                "(line " + QString::number(error_line) +
                ", col " + QString::number(error_column) + ")";
  }
}