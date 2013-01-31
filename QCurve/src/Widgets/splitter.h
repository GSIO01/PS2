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

#ifndef SPLITTER_H
#define SPLITTER_H

#include <QSplitter>

class QMouseEvent;
/**
 * The Splitter class extends the QSplitter widget.
 *
 * The Splitter widget provides a simple way to collapse/uncollapse widgets.
 *
 * \see QSplitter
 */
class Splitter : public QSplitter
{
  Q_OBJECT

  signals:
    void mouseDoubleClicked();

  public:
    /**
     * Constructs a horizontal splitter with the parent argument.
     */
    Splitter(QWidget* parent = 0);

    /**
     * Constructs a splitter with the given orientation and parent.
     */
    Splitter(Qt::Orientation orientation, QWidget* parent = 0);

    /**
     * Destroys the splitter. All children are deleted.
     */
    ~Splitter();

    /**
     * Returns \c true if the widget at index is collapsed otherwise returns false.
     *
     * \param index
     */
    bool isWidgetCollapsed(int index) const;

    /**
     * Sets whether the child widget at index is collapsed or not.
     *
     * \param index
     * \param collapsed
     */
    void setWidgetCollapsed(int index, bool collapsed);

  protected:
    /**
     * Reimplemented from QWidget::mouseDoubleClickEvent().
     */
    void mouseDoubleClickEvent(QMouseEvent* event);

  private:
    QList<int> m_savedSizes; //TODO should be a list...
};

#endif // SPLITTER_H
