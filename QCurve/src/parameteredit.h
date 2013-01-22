#ifndef PARAMETEREDIT_H
#define PARAMETEREDIT_H

#include <QtGui/QWidget>
#include <QtGui/QDoubleSpinBox>

#include "Core/Parameter"

class QtMmlWidget;

/**
 * Implements widget to handle parameter editing.
 */
class ParameterEdit : public QWidget
{
  Q_OBJECT

  signals:
    /**
     * Signal for changes of the from value.
     *
     * \param from New value.
     */
    void fromValueChanged(double from);
    /**
     * Signal for changes of the to value.
     *
     * \param to New value.
     */
    void toValueChanged(double to);

  public:
    /**
     * Constructor.
     *
     * \param parent Parent object.
     */
    ParameterEdit(QWidget* parent = 0);
    /**
     * Copy constructor.
     *
     * \param param Other parameter.
     * \param parent Parent object.
     */
    ParameterEdit(const Parameter& param, QWidget* parent = 0);

    /**
     * Get the parameter.
     *
     * \return Parameter.
     */
    QString parameter() const { return m_parameter; }
    /**
     * Set the parameter.
     *
     * \param param Reference to another Parameter.
     */
    void setParameter(const Parameter& param);

    /**
     * Get from value.
     *
     * \return From value.
     */
    double from() const { return m_from->value(); }
    /**
     * Get to value.
     *
     * \return To value.
     */
    double to() const { return m_to->value(); }

  private:
    /**
     * Initialize of components.
     */
    void initComponents();

    QString m_parameter;

    QtMmlWidget* m_formula;
    QDoubleSpinBox* m_from;
    QDoubleSpinBox* m_to;
};

#endif