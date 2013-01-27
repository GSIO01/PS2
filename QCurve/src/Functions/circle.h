#ifndef CIRCLE_H
#define CIRCLE_H

#include "Core/Function"

/**
 * Represents a circle. 
 * 
 * @see Function
 */
class Circle : public Function
{
  public:
    Circle(double r = 1, double x0 = 0, double y1 = 0);
    Circle(const Circle& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void updatePoints(const QString& name = QString(), double value = 0);
    virtual void initDimension();
};

#endif

