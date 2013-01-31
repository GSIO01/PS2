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

#ifndef PARABOLA_H
#define PARABOLA_H

#include "Core/Function"

/**
 * Represents a parabola.
 *
 * @see Function
 */
class Parabola : public Function
{
  public:
    Parabola(double p = 1, double x0 = 0, double y0 = 0);
    Parabola(const Parabola& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void initDimension();
    virtual void updatePoints(const QString& name = QString(), double value = 0);
};

#endif
