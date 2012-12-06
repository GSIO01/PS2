#ifndef CYCLOID_H
#define CYCLOID_H

#include "Core/Function"

/*** Represents a cycloid. */
class Cycloid : public Function
{
  public:
    Cycloid(double r = 1, double m = 1, double x0 = 0, double y0 = 0);
    Cycloid(const Cycloid& other);
    
    virtual Function* clone() const;
    
    virtual QString toParametricFormula() const;
    
    virtual double calculateX(double t) const;
    virtual double calculateY(double t) const;
    virtual double calculateZ(double t) const;
};

#endif
