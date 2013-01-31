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

#ifndef INTERVAL_H
#define INTERVAL_H

#include <QtCore/QString>

/**
 * Implements a mathematical interval.
 */
class Interval
{
  public:
    Interval();
    Interval(double lower, bool isClosed = true);
    Interval(double lower, double upper, bool lowerIsClosed = true, bool upperIsClosed = true);

	/**
	 * Get the lower end of the interval.
	 *
	 * \return lower end of interval.
	 */
    double lowerEnd() const { return m_lower; }
	/**
	 * Set lower end of interval.
	 *
	 * \param value new value of lower end.
	 * \param closed whether the lower end is closed.
	 */
    void setLowerEnd(double value, bool closed = false);

	/**
	 * Checks if the lower end of the intervall is closed.
	 */
    bool lowerEndIsClosed() const { return m_lowerIsClosed; }

	/**
	 * Get the upper end of the interval.
	 *
	 * \return upper end of interval.
	 */
    double upperEnd() const { return m_upper; }
	/**
	 * Set upper end of interval.
	 *
	 * \param value new value of upper end.
	 * \param closed whether the upper end is closed.
	 */
    void setUpperEnd(double value, bool closed = false);

	/**
	 * Checks if the upper end of the interval is closed.
	 */
    bool upperEndIsClosed() const { return m_upperIsClosed; }

	/**
	 * Get a string representation of the Intervall.
	 */
    QString toString() const;

  protected:
    double m_lower;
    bool m_lowerIsClosed;

    double m_upper;
    bool m_upperIsClosed;
};

#endif
