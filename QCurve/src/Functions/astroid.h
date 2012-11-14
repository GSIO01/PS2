#ifndef ASTROID_H
#define ASTROID_H

#include "Core/Function"

/** Represents a cissoid. */
class Astroid : public Function
{
  public:
    Astroid(double a, double x0 = 0, double y0 = 0);
    Astroid(const Astroid& other);
    
    virtual Function* clone() const;
    
    virtual QString toParametricFormula() const;
    
    virtual double calculateX(double t) const;
    virtual double calculateY(double t) const;
    virtual double calculateZ(double t) const;
};

#endif
 