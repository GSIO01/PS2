/**
  * Funktion zur Berechnung eines Klothoiden
  *
  * @author Mario Worbs
  *
  */

#ifndef CLOTHOIDS_H
#define CLOTHOIDS_H

#include "Core/Function"

class Clothoids : public Function
{
  public:

    /**
    * Konstruktor
    * @param a Integrationsparameter
    * @param n Integrationsschritte
    * @param x0 Startwert X-Achse
    * @param y0 Startwert Y-Achse
    */
    Clothoids(double a,double n = 30, double x0 = 0, double y0 = 0);

    /**
    * Kopierkonstruktor
    * @param other Referenz auf Klothoidenobjekt
    */
    Clothoids(const Clothoids& other);

    virtual Function* clone() const;

    virtual QString toParametricFormula() const;

    virtual Point3D calculatePoint(double t) const;

  protected:
    void initDimension();
};

#endif // CLOTHOIDS_H