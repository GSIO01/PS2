#ifndef LOGARITHMICSPIRAL_H
#define LOGARITHMICSPIRAL_H

#include "Core/Function"

/*** Represents a logarithmic spiral. */
class LogarithmicSpiral : public Function
{
  public:
    LogarithmicSpiral(double a = 0.1, double k = 1, double x0 = 0, double y0 = 0);
    LogarithmicSpiral(const LogarithmicSpiral& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void initDimension();
    virtual void updatePoints(const QString& name = QString(), double value = 0);
};

#endif
