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