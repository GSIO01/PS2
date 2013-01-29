#ifndef CLOTHOIDS_H
#define CLOTHOIDS_H

#include "Core/Function"

/**
 * Represents a clothoid.
 *
 * @see Function
 */
class Clothoids : public Function
{
  public:
    Clothoids(double a, double x0 = 0, double y0 = 0);
    Clothoids(const Clothoids& other);

    virtual Function* clone() const;
    virtual QString toParametricFormula() const;
    virtual Point3D calculatePoint(double t) const;

  protected:

    virtual void updatePoints(const QString& name = QString(), double value = 0);

    virtual void initDimension();
};

#endif // CLOTHOIDS_H
