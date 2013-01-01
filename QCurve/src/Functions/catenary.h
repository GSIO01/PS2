#ifndef CATENARY_H
#define CATENARY_H

#include "Core/Function"

/*** Represents a catenary. */
class Catenary : public Function
{
  public:
    Catenary(double a = 1, double x0 = 0, double y0 = 0);
    Catenary(const Catenary& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void initDimension();
};

#endif
