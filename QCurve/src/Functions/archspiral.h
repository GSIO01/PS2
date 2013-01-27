#ifndef ARCHIMEDEANSPIRAL_H
#define ARCHIMEDEANSPIRAL_H

#include "Core/Function"

/*** Represents a archimedean spiral. */
class ArchimedeanSpiral : public Function
{
  public:
    ArchimedeanSpiral(double x0 = 0, double y0 = 0, int a = 1);
    ArchimedeanSpiral(const ArchimedeanSpiral& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void updatePoints(const QString& name = QString(), double value = 0);
    virtual void initDimension();
};

#endif
