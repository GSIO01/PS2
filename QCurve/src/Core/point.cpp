#include "point.h"

#define PI 3.141592653589793

Point::Point(double x, double y, const QString& name)
  : m_x(x), m_y(y), m_z(0), m_name(name)
{ }

Point::Point(double x, double y, double z, const QString& name)
  : m_x(x), m_y(y), m_z(z), m_name(name)
{ }

double Point::X() const
{ return m_x; }

double Point::Y() const
{ return m_y; }

double Point::Z() const
{ return m_z; }

QString Point::name() const
{ return m_name; }

bool Point::operator==(const Point& other)
{ return (m_x == other.m_x && m_y == other.m_y && m_z == other.m_z) || (!m_name.isEmpty() && m_name == other.m_name); }

Point Point::toRadial() const
{ return Point(m_x * PI / 180, m_y * PI / 180, m_z * PI / 180); }