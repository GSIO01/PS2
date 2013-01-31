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

#ifndef HYPERBOLA_H
#define HYPERBOLA_H

#include "Core/Function"

/**
 * Represents a hyperpolic curve.
 *
 * @see Function
 */
class Hyperbola : public Function
{
  public:
    Hyperbola(double a = 1, double b = 1, double x0 = 0, double y1 = 0);
    Hyperbola(const Hyperbola& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;
    virtual Point3D calculatePoint2(double t) const;

    virtual int calculations() const { return 2; }

  protected:
    virtual void initDimension();
    virtual void updatePoints(const QString& name = QString(), double value = 0);
};

#endif
