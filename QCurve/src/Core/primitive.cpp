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

#include "primitive.h"

#include <QtGui/QApplication>
#include <QtGui/QPalette>

Primitive::Primitive(PrimitiveType type, const QString& name,
                     const QString& description)
  : m_type(type), m_name(name), m_description(description), m_isAnimated(false)
{ m_color = QApplication::palette().color(QPalette::WindowText); }

void Primitive::setDescription(const QString& description)
{ m_description = description; }

void Primitive::setColor(const QColor& color)
{ m_color = color; }

void Primitive::setIsAnimated(bool isAnimated)
{ m_isAnimated = isAnimated; }

bool Primitive::operator==(const Primitive& other)
{ return m_name == other.m_name; }