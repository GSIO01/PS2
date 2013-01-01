#ifndef PARABOLA_H
#define PARABOLA_H

#include "Core/Function"

/** Represents a parabola. */
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
};

#endif
