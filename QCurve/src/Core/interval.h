#ifndef INTERVAL_H
#define INTERVAL_H

#include <QtCore/QString>

class Interval
{
  public:
    Interval();
    Interval(double lower, bool isClosed = true);
    Interval(double lower, double upper, bool lowerIsClosed = true, bool upperIsClosed = true);

    double lowerEnd() const { return m_lower; }
    void setLowerEnd(double value, bool closed = false);

    bool lowerEndIsClosed() const { return m_lowerIsClosed; }

    double upperEnd() const { return m_upper; }
    void setUpperEnd(double value, bool closed = false);

    bool upperEndIsClosed() const { return m_upperIsClosed; }

    QString toString() const;

  protected:
    double m_lower;
    bool m_lowerIsClosed;

    double m_upper;
    bool m_upperIsClosed;
};

#endif
