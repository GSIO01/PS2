#ifndef TRACTRIX_H
#define TRACTRIX_H

#include "Core/Function"

/*** Represents a tractrix. */
class Tractrix : public Function
{
  public:
    Tractrix(double x0, double y0, double a);
    Tractrix(const Tractrix& other);
    
    virtual Function* clone() const;
    
    virtual QString toParametricFormula() const;
    
    virtual double calculateX(double t) const;
    virtual double calculateY(double t) const;
    virtual double calculateZ(double t) const;
};

#endif
 
