#ifndef HYPERBOLA_H
#define HYPERBOLA_H

#include "Core/Function"

/**
 * Represents a hyperpolic curve.
 * 
 * @see Function 
 */
class Hyperbola : public Function
{
  public:
    Hyperbola(double a = 1, double b = 1, double x0 = 0, double y1 = 0);
    Hyperbola(const Hyperbola& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;
    virtual Point3D calculatePoint2(double t) const;

    virtual int calculations() const { return 2; }

  protected:
    virtual void initDimension();
    virtual void updatePoints(const QString& name = QString(), double value = 0);
};

#endif
