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

FunctionWidget::FunctionWidget(QWidget* parent) : QWidget(parent)
{
  initComponents();

  connect(m_paramEdit, SIGNAL(fromValueChanged(double)), this, SLOT(fromValueChanged(double)));
  connect(m_paramEdit, SIGNAL(toValueChanged(double)), this, SLOT(toValueChanged(double)));

  connect(m_plotter, SIGNAL(scaleFactorChanged(int)), m_scaleFactor, SLOT(setValue(int)));
  connect(m_scaleFactor, SIGNAL(valueChanged(int)), m_plotter, SLOT(setScaleFactor(int)));

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

  m_statusBar = new QStatusBar();
  m_statusBar->addPermanentWidget(m_scaleFactor);

  lyt = new QVBoxLayout(this);
  lyt->addWidget(splitter);
  lyt->addWidget(m_statusBar);
}

void FunctionWidget::fromValueChanged(double value)
{
  m_plotter->function().parameter().setFrom(value);

  updateFormula();
}

void FunctionWidget::toValueChanged(double value)
{
  m_plotter->function().parameter().setTo(value);

  updateFormula();
}

void FunctionWidget::varValueChanged(const QString& var, double value)
{
  m_plotter->setVariable(var, value);

  updateFormula();
}

void FunctionWidget::positionChanged(double x, double y)
{
  m_statusBar->clearMessage();
  m_statusBar->showMessage(tr("Mouse Position(%1, %2)").arg(QString::number(x, 'f', 2)).arg(QString::number(y, 'f', 2)));
}

void FunctionWidget::setShowGrid(bool isVisible)
{ m_plotter->setShowGrid(isVisible); }

void FunctionWidget::setAnimationMode(int delay, bool repeat)
{ m_plotter->setAnimationDelay(delay, repeat); }

void FunctionWidget::updateFormula()
{
  QString error_msg;
  int error_line, error_column;
  bool result = m_formula->setContent(m_plotter->function().toParametricFormula());
  if (!result)
  {
    qDebug() << "Parse error: " + error_msg +
      "(line " + QString::number(error_line) +
      ", col " + QString::number(error_column) + ")";
  }
}
