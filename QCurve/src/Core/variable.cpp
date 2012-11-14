#include "variable.h"

Variable::Variable(const QString& name, double value)
  : m_name(name), m_value(value)
{ }

Variable::~Variable()
{ }

QString Variable::name() const
{ return m_name; }

double Variable::value() const
{ return m_value; }

void Variable::setValue(double value)
{ m_value = value; }

bool Variable::operator==(const Variable& other)
{ m_name == other.m_name; }

bool operator==(const Variable& variable, const QString& name)
{ return variable.m_name == name; }

bool operator==(const QString& name, const Variable& variable)
{ return variable.m_name == name; }