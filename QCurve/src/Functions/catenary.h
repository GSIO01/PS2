#ifndef CATENARY_H
#define CATENARY_H

#include "Core/Function"

/*** Represents a catenary. */
class Catenary : public Function
{
  public:
    Catenary(double x0 = 0, double y0 = 0, double a = 1);
    Catenary(const Catenary& other);
    
    virtual Function* clone() const;
    
    virtual QString toParametricFormula() const;
    
    virtual double calculateX(double t) const;
    virtual double calculateY(double t) const;
    virtual double calculateZ(double t) const;
};

#endif
 
