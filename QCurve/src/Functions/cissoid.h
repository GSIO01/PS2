#ifndef CISSOID_H
#define CISSOID_H

#include "Core/Function"

/** Represents a cissoid. */
class Cissoid : public Function
{
  public:
    Cissoid(double a, double x0 = 0, double y0 = 0);
    Cissoid(const Cissoid& other);
    
    virtual Function* clone() const;
    
    virtual QString toParametricFormula() const;
    
    virtual double calculateX(double t) const;
    virtual double calculateY(double t) const;
    virtual double calculateZ(double t) const;
};

#endif
