#include "point.h"

Point::Point(double x, double y, const QString& name)
  : m_x(x), m_y(y), m_name(name)
{ }

double Point::X() const
{ return m_x; }

double Point::Y() const
{ return m_y; }

QString Point::name() const
{ return m_name; }

bool Point::operator==(const Point& other)
{ return m_x == other.m_x && m_y == other.m_y; }