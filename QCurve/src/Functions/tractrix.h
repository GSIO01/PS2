#ifndef TRACTRIX_H
#define TRACTRIX_H

#include "Core/Function"

/**
 * Represents a tractrix. 
 * 
 * @see Function
 */
class Tractrix : public Function
{
  public:
    Tractrix(double a = 1, double x0 = 0, double y0 = 0);
    Tractrix(const Tractrix& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void initDimension();
};

#endif
