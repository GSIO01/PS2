#include "point.h"

#define PI 3.141592653589793

Point::Point(double x, double y, const QString& name, const QString& desc)
  : m_x(x), m_y(y), m_z(0), m_name(name), m_description(desc)
{ }

Point::Point(double x, double y, double z, const QString& name, const QString& desc)
  : m_x(x), m_y(y), m_z(z), m_name(name), m_description(desc)
{ }

double Point::X() const
{ return m_x; }

double Point::Y() const
{ return m_y; }

double Point::Z() const
{ return m_z; }

QString Point::name() const
{ return m_name; }

QString Point::description() const
{ return m_description; }

bool Point::operator==(const Point& other)
{ return (m_x == other.m_x && m_y == other.m_y && m_z == other.m_z) || (!m_name.isEmpty() && m_name == other.m_name); }

Point Point::toRadial() const
{ return Point(m_x * 180 / PI, m_y * 180 / PI, m_z * 180 / PI); }

Point Point::toDegree() const
{ return Point(m_x * PI / 180, m_y * PI / 180, m_z * PI / 180); }

QString Point::toString() const
{
  return QString("<b>%1</b> [%2, %3, %4]<br/>%5").arg(m_name).
    arg(QString::number(m_x)).arg(QString::number(m_y)).
    arg(QString::number(m_z)).arg(m_description);
}