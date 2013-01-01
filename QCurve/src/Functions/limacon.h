#ifndef LIMACON_H
#define LIMACON_H

#include "Core/Function"

/** Represents a limacon. */
class Limacon : public Function
{
  public:
    Limacon(double a = 1, double b = 1.5, double x0 = 0, double y1 = 0);
    Limacon(const Limacon& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void initDimension();
};

#endif
