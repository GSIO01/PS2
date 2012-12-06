#ifndef HYPERBOLA_H
#define HYPERBOLA_H

#include "Core/Function"

/** Represents a hyperpolic curve. */
class Hyperbola : public Function
{
  public:
    Hyperbola(double a = 1, double b = 1, double x0 = 0, double y1 = 0);
    Hyperbola(const Hyperbola& other);
    
    virtual Function* clone() const;
    
    virtual QString toParametricFormula() const;
    
    virtual double calculateX(double t) const;
    virtual double calculateY(double t) const;
    virtual double calculateZ(double t) const;
};

#endif
 
