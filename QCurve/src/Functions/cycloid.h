#ifndef CYCLOID_H
#define CYCLOID_H

#include "Core/Function"

/**
 * Represents a cycloid. 
 * 
 * @see Function
 */
class Cycloid : public Function
{
  public:
    Cycloid(double r = 1, double m = 1, double x0 = 0, double y0 = 0);
    Cycloid(const Cycloid& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void updatePoints(const QString& name = QString(), double value = 0);
    virtual void initDimension();
};

#endif
