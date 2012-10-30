#ifndef POINT_H
#define POINT_h

#include <QtCore/QString>

class Point
{
  public:
    Point(double x, double y, const QString& name = QString());

    double X() const; 
    double Y() const; 
    QString name() const;

    bool operator==(const Point& other);
    
  private:
    double m_x;
    double m_y;
    QString m_name;
};

#endif