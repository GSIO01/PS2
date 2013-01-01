#ifndef ARCHIMEDEANSPIRAL_H
#define ARCHIMEDEANSPIRAL_H

#include "Core/Function"

/*** Represents a archimedean spiral. */
class ArchimedeanSpiral : public Function
{
  public:
    ArchimedeanSpiral(double x0 = 0, double y0 = 0);
    ArchimedeanSpiral(const ArchimedeanSpiral& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    virtual void initDimension();
};

#endif
