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

#include "splitter.h"

#include <QtGui/QMouseEvent>

Splitter::Splitter(QWidget* parent)
  : QSplitter(parent)
{ }

Splitter::Splitter(Qt::Orientation orientation, QWidget* parent)
  : QSplitter(orientation, parent)
{ }

Splitter::~Splitter()
{ }

bool Splitter::isWidgetCollapsed(int index) const
{
  if (index < 0 || index >= count())
  { return false; }

  int minSize;
  if (orientation() == Qt::Horizontal)
  { minSize = qMax(widget(index)->minimumSizeHint().width(), widget(index)->minimumSize().width()); }
  else { minSize = qMax(widget(index)->minimumSizeHint().height(), widget(index)->minimumSize().height()); }

  return isCollapsible(index) && (sizes().at(index) < minSize);
}

void Splitter::setWidgetCollapsed(int index, bool collapsed)
{
  if (index < 0 || index >= count())
  { return; }

  if (collapsed && isCollapsible(index))
  {
    m_savedSizes = sizes();

    QList<int> tmp = m_savedSizes;
    tmp.replace(index, 0);
    setSizes(tmp);
  }
  else { setSizes(m_savedSizes); }
}

void Splitter::mouseDoubleClickEvent(QMouseEvent* event)
{
  QWidget::mouseDoubleClickEvent(event);

  emit mouseDoubleClicked();
}
