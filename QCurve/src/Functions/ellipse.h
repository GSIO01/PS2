#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Core/Function"

/**
 * Represents a ellipse.
 *
 * @see Function 
 */
class Ellipse : public Function
{
  public:
    Ellipse(double a = 3, double b = 2, double x0 = 0, double y1 = 0);
    Ellipse(const Ellipse& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void updatePoints(const QString& name = QString(), double value = 0);
    virtual void initDimension();
};

#endif
