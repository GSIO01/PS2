#ifndef CATENARY_H
#define CATENARY_H

#include "Core/Function"

/**
 * Represents a catenary.
 *
 * @see Function
 */
class Catenary : public Function
{
  public:
    Catenary(double a = 1, double x0 = 0, double y0 = 0);
    Catenary(const Catenary& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void initDimension();
    virtual void updatePoints(const QString& name = QString(), double value = 0);

  private:
    Point3D calculateIntersectionPoint(double t) const;
};

#endif
