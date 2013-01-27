#ifndef ASTROID_H
#define ASTROID_H

#include "Core/Function"

/**
 * Represents a astroid. 
 * 
 * @see Function
 */
class Astroid : public Function
{
  public:
    Astroid(double a = 1, double x0 = 0, double y0 = 0);
    Astroid(const Astroid& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void updatePoints(const QString& name = QString(), double value = 0);
    virtual void initDimension();
};

#endif
