#ifndef LIMACON_H
#define LIMACON_H

#include "Core/Function"

/**
 * Represents a limacon. 
 * 
 * @see Function
 */
class Limacon : public Function
{
  public:
    Limacon(double a = 1, double b = 1.0, double x0 = 0, double y1 = 0);
    Limacon(const Limacon& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void updatePoints(const QString& name = QString(), double value = 0);
    virtual void initDimension();
};

#endif
