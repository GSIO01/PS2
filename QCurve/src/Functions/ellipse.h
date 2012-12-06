#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Core/Function"

/*** Represents a ellipse. */
class Ellipse : public Function
{
  public:
    Ellipse(double a = 1, double b = 2, double x0 = 0, double y1 = 0);
    Ellipse(const Ellipse& other);
    
    virtual Function* clone() const;
    
    virtual QString toParametricFormula() const;
    
    virtual double calculateX(double t) const;
    virtual double calculateY(double t) const;
    virtual double calculateZ(double t) const;
};

#endif
