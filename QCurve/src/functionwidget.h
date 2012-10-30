#ifndef FUNCTIONWIDGET_H
#define FUNCTIONWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QDoubleSpinBox>

#include <Core/Function>

class QtMmlWidget;
class QBoxLayout;
class Graph2D;
class FunctionWidget : public QWidget
{
  Q_OBJECT
  
  public:
    FunctionWidget(QWidget* parent = 0);
    virtual ~FunctionWidget();
    
    const Function& function() const;
    void setFunction(const Function& function);

  private slots:
    void fromValueChanged(double value);
    void toValueChanged(double value);
    void varValueChanged(double value);
    
  private:
    void initComponents();
    
    Function* m_function;

    QtMmlWidget* m_mmlWgt;
    Graph2D* m_plotter; //TODO

    QDoubleSpinBox* m_paramFrom;
    QDoubleSpinBox* m_paramTo;
    QBoxLayout* m_variablesLyt;
};

#endif
