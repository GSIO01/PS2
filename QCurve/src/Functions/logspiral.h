#ifndef LOGARITHMICSPIRAL_H
#define LOGARITHMICSPIRAL_H

#include "Core/Function"

/*** Represents a logarithmic spiral. */
class LogarithmicSpiral : public Function
{
  public:
    LogarithmicSpiral(double a = 1.1, double x0 = 0, double y0 = 0);
    LogarithmicSpiral(const LogarithmicSpiral& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual double calculateX(double t) const;
    virtual double calculateY(double t) const;
    virtual double calculateZ(double t) const;

  protected:
    virtual void initDimension();
};

#endif
