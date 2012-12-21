#ifndef VARIABLEEDIT_H
#define VARIABLEEDIT_H

#include <QtGui/QWidget>
#include <QtGui/QDoubleSpinBox>

#include "Core/Variable"

class QtMmlWidget;
class QKeyEvent;
class VariableEdit : public QWidget
{
  Q_OBJECT

  signals:
    void valueChanged(const QString& var, double value);

  public:
    VariableEdit(const Variable& var, QWidget* parent = 0);

    double value() { return m_value->value(); }

    QString variable() const { return m_variable; }
    void setVariable(const Variable& var);

  private slots:
    void valueChanged(double value);

  private:
    QString m_variable;

    QtMmlWidget* m_variableLbl;
    QDoubleSpinBox* m_value;
};

#endif
