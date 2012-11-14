#ifndef FUNCTIONWIDGET_H
#define FUNCTIONWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QScrollArea>
#include <QtGui/QDoubleSpinBox>

#include "Core/Function"

class QtMmlWidget;
class QBoxLayout;
class Graph2D;
/***
 * Represents a complex widget to visualize a function
 * and to change its specification.
 */
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
    /*** Reacts on the recent change of a variable */
    void varValueChanged(double value);
    
  private:
    void initComponents();
    void updateFormula();
    
    Function* m_function;

    QtMmlWidget* m_mmlWgt;
    Graph2D* m_plotter;

    QDoubleSpinBox* m_paramFrom;
    QDoubleSpinBox* m_paramTo;

    QScrollArea* m_varInputPanel;
    QBoxLayout* m_variablesLyt;
};

#endif
