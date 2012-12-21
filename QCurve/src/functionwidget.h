#ifndef FUNCTIONWIDGET_H
#define FUNCTIONWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>

#include "Core/Function"

class QtMmlWidget;
class QBoxLayout;
class Graph2D;
class ParameterEdit;
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
    void varValueChanged(const QString& var, double value);

    void positionChanged(double x, double y);

  private:
    void initComponents();
    void updateFormula();

    QGroupBox* m_specification;
    QGroupBox* m_paramVar;

    QtMmlWidget* m_formula;
    ParameterEdit* m_paramEdit;
    QScrollArea* m_varInputPanel;
    QBoxLayout* m_variablesLyt;
    Graph2D* m_plotter;

    QStatusBar* m_statusBar;
    QSlider* m_scaleFactor;
    QPushButton* m_settings;
};

#endif
