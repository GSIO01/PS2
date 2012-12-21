#ifndef PARAMETEREDIT_H
#define PARAMETEREDIT_H

#include <QtGui/QWidget>
#include <QtGui/QDoubleSpinBox>

#include "Core/Parameter"

class QtMmlWidget;
class ParameterEdit : public QWidget
{
  Q_OBJECT

  signals:
    void fromValueChanged(double from);
    void toValueChanged(double to);

  public:
    ParameterEdit(QWidget* parent = 0);
    ParameterEdit(const Parameter& param, QWidget* parent = 0);

    QString parameter() const { return m_parameter; }
    void setParameter(const Parameter& param);

    double from() const { return m_from->value(); }
    double to() const { return m_to->value(); }

  private:
    void initComponents();

    QString m_parameter;

    QtMmlWidget* m_formula;
    QDoubleSpinBox* m_from;
    QDoubleSpinBox* m_to;
};

#endif