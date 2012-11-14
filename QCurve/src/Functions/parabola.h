#ifndef PARABOLA_H
#define PARABOLA_H

#include "Core/Function"

/** Represents a parabola. */
class Parabola : public Function
{
  public:
    Parabola(double p, double x0 = 0, double y0 = 0);
    Parabola(const Parabola& other);
    
    virtual Function* clone() const;
    
    virtual QString toParametricFormula() const;
    
    virtual double calculateX(double t) const;
    virtual double calculateY(double t) const;
    virtual double calculateZ(double t) const;
};

#endif
