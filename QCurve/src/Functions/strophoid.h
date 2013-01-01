#ifndef STROPHOID_H
#define STROPHOID_H

#include "Core/Function"

/** Represents a ellipse. */
class Strophoid : public Function
{
  public:
    Strophoid(double a = 1, double x0 = 0, double y0 = 0);
    Strophoid(const Strophoid& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void initDimension();
};

#endif
