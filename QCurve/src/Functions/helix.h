#ifndef HELIX_H
#define HELIX_H

#include "Core/Function"

/*** Represents a helix. */
class Helix : public Function
{
  public:
    Helix(double r = 1, double h = 1, double x0 = 0, double y0 = 0, double z0 = 0);
    Helix(const Helix& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual double calculateX(double t) const;
    virtual double calculateY(double t) const;
    virtual double calculateZ(double t) const;

  protected:
    virtual void initDimension();
};

#endif 
