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
