#ifndef LEMNISCATE_H
#define LEMNISCATE_H

#include "Core/Function"

/*** Represents a lemniscate. */
class Lemniscate : public Function
{
  public:
    Lemniscate(double a = 1, double x0 = 0, double y0 = 0);
    Lemniscate(const Lemniscate& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void initDimension();
};

#endif
