#ifndef LEMNISCATE_H
#define LEMNISCATE_H

#include "Core/Function"

/**
 * Represents a lemniscate. 
 * 
 * @see Function
 */
class Lemniscate : public Function
{
  public:
    Lemniscate(double a = 1, double x0 = 0, double y0 = 0);
    Lemniscate(const Lemniscate& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void updatePoints(const QString& name = QString(), double value = 0);
    virtual void initDimension();
};

#endif
