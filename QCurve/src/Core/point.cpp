/*
 * (C) Copyright 2012-2013 QCurve Team
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser General Public License
 * (LGPL) version 2.1 which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl-2.1.html
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 */

#include "point.h"

Point2D::Point2D(double x, double y)
  : m_x(x), m_y(y)
{ }

bool Point2D::operator==(const Point2D& other) const
{ return m_x == other.m_x && m_y == other.m_y; }

QString Point2D::toString() const
{ return QString("%1, %2").arg(QString::number(m_x)).arg(QString::number(m_y)); }

Point3D::Point3D(double x, double y, double z)
  : m_x(x), m_y(y), m_z(z)
{ }

bool Point3D::operator==(const Point3D& other) const
{ return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z; }

QString Point3D::toString() const
{
  if (m_z != 0)
  { return QString("%1, %2, %3").arg(QString::number(m_x)).arg(QString::number(m_y)).arg(QString::number(m_z)); }
  else { return QString("%1, %2").arg(QString::number(m_x)).arg(QString::number(m_y)); }
}