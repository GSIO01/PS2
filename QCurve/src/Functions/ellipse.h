#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <Core/Function>

class Ellipse : public Function
{
  public:
    Ellipse(double r);
    Ellipse(double a, double b);
    Ellipse(const Ellipse& other);
    
    virtual Function* clone() const;
    
    virtual QString toFormula() const;
    
    virtual double calculateX(double t) const;
    virtual double calculateY(double t) const;
  
  private:
    QString m_formula;
};

#endif
