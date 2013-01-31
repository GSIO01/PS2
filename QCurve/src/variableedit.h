/*
 * (C) Copyright 2012-2013 QCurve Team
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser General Public License
 * (LGPL) version 2.1 which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl-2.1.html
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 */

#ifndef VARIABLEEDIT_H
#define VARIABLEEDIT_H

#include <QtGui/QWidget>
#include <QtGui/QDoubleSpinBox>

#include "Core/Variable"

class QtMmlWidget;
class QKeyEvent;

/**
 * Implements a widget to handle variable editing.
 */
class VariableEdit : public QWidget
{
  Q_OBJECT

  signals:
    /**
     * Signal for value changes.
     *
     * \param var Variable name.
     * \param value New value.
     */
    void valueChanged(const QString& var, double value);

  public:
    /**
     * Copy Constructor.
     *
     * \param var Other variable.
     * \param parent Parent object.
     */
    VariableEdit(const Variable& var, QWidget* parent = 0);

    /**
     * Get the value.
     *
     * \return Value of the variable.
     */
    double value() { return m_value->value(); }

    /**
     * Get variable.
     *
     * \return variable.
     */
    QString variable() const { return m_variable; }
    /**
     * Set variable.
     *
     * \param var Reference to another Variable.
     */
    void setVariable(const Variable& var);

  private slots:
    /**
     * Slot for value changes.
     *
     * \param value New value.
     */
    void valueChanged(double value);

  private:
    QString m_variable;

    QtMmlWidget* m_variableLbl;
    QDoubleSpinBox* m_value;
};

#endif
