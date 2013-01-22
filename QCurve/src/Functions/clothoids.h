#ifndef CLOTHOIDS_H
#define CLOTHOIDS_H

#include "Core/Function"

/**
 * Represents a clothoid.
 */
class Clothoids : public Function
{
  public:
    Clothoids(double a, double x0 = 0, double y0 = 0);

    Clothoids(const Clothoids& other);

    virtual Function* clone() const;
    virtual QString toParametricFormula() const;
    virtual Point3D calculatePoint(double t) const;

  protected:
    void initDimension();
};

#endif
