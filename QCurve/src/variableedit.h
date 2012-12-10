#ifndef VARIABLEEDIT_H
#define VARIABLEEDIT_H

#include <QtGui/QWidget>
#include <QtGui/QDoubleSpinBox>

#include "Core/variable.h"

class QtMmlWidget;
class QKeyEvent;
class VariableEdit : public QWidget
{
  Q_OBJECT

  signals:
    void valueChanged(const QString& var, double value);

  public:
    VariableEdit(const Variable& var, QWidget* parent = 0);

    QString variable() const { return m_variable; }
    void setVariable(const Variable& var);

  protected:
     virtual void focusOutEvent(QFocusEvent* event);
     virtual void keyPressEvent(QKeyEvent* event);

  private:
    QString m_variable;

    QtMmlWidget* m_variableLbl;
    QDoubleSpinBox* m_value;
}; 

#endif
