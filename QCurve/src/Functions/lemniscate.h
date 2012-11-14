#ifndef LEMNISCATE_H
#define LEMNISCATE_H

#include "Core/Function"

/** Represents a lemniscate. */
class Lemniscate : public Function
{
  public:
    Lemniscate(double a, double x0 = 0, double y0 = 0);
    Lemniscate(const Lemniscate& other);
    
    virtual Function* clone() const;
    
    virtual QString toParametricFormula() const;
    
    virtual double calculateX(double t) const;
    virtual double calculateY(double t) const;
    virtual double calculateZ(double t) const;
};

#endif
