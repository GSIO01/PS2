#ifndef CISSOID_H
#define CISSOID_H

#include "Core/Function"

/*** Represents a cissoid. */
class Cissoid : public Function
{
  public:
    Cissoid(double a = 1, double x0 = 0, double y0 = 0);
    Cissoid(const Cissoid& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void updatePoints(const QString& name = QString(), double value = 0);
    virtual void initDimension();
};

#endif
