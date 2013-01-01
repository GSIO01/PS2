#ifndef HYPOCYCLOID_H
#define HYPOCYCLOID_H

#include "Core/Function"

/*** Represents a hypocycloid. */
class Hypocycloid : public Function
{
  public:
    Hypocycloid(double a = 1, double c = 0.4, double x0 = 0, double y0 = 0);
    Hypocycloid(const Hypocycloid& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void initDimension();
};

#endif
