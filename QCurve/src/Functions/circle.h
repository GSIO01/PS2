#ifndef CIRCLE_H
#define CIRCLE_H

#include "Core/Function"

/*** Represents a circle. */
class Circle : public Function
{
  public:
    Circle(double r = 1, double x0 = 0, double y1 = 0);
    Circle(const Circle& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual double calculateX(double t) const;
    virtual double calculateY(double t) const;
    virtual double calculateZ(double t) const;

  protected:
    virtual void initDimension();
};

#endif

