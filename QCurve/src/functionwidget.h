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

#ifndef FUNCTIONWIDGET_H
#define FUNCTIONWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QLabel>

#include "Core/Function"

class QtMmlWidget;
class QBoxLayout;
class Graph2D;
class ParameterEdit;
/**
 * Represents a complex widget to visualize a function
 * and to change its specification.
 */
class FunctionWidget : public QWidget
{
  Q_OBJECT

  public:
    /**
     * Constructor.
     *
     * \param parent The parent object.
     */
    FunctionWidget(QWidget* parent = 0);
    /**
     * Destructor.
     */
    virtual ~FunctionWidget();

    /**
     * Get the function.
     *
     * \return The function.
     */
    const Function& function() const;
    /**
     * Set the function.
     *
     * \param function New function.
     */
    void setFunction(const Function& function);

    /**
     * Set the animation mode.
     *
     * \param delay Delay animation for this ammount of time.
     * \param repeat Repeat the animation?
     */
    void setAnimationMode(int delay, bool repeat);
    /**
     * Enable/disable the grid.
     *
     * \param isVisible Should the grid be visible?
     */
    void setShowGrid(bool isVisible);
    /**
     * Enable/disable use of Antialiasing.
     *
     * \param useAntialiasing Should Antialiasing be enabled?
     */
    void setUseAntialiasing(bool useAntialiasing);

  private slots:
    /**
     * Update function to be used if the from value has changed.
     *
     * \param value The new value.
     */
    void fromValueChanged(double value);
    /**
     * Update function to be used if the to value has changed.
     *
     * \param value The new value.
     */
    void toValueChanged(double value);
    /**
     * Update function to be used if a variable has been changed.
     *
     * \param var Variable name.
     * \param value The new value.
     */
    void varValueChanged(const QString& var, double value);

    /**
     * Update function to be used if the position has been changed.
     *
     * \param x X coordinate.
     * \param y Y coordinate.
     */
    void positionChanged(double x, double y);

    /**
     * Update the scale factor.
     *
     * \param value new scale factor
     */
    void updateScaleFactor(int value);

  private:
    /**
     * Initializes all components.
     */
    void initComponents();
    /**
     * Updates the formula.
     */
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
    QLabel* m_scaleFactorLbl;
    QPushButton* m_settings;
};

#endif
