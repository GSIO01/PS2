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

#include "treeitem.h"

#include <QtCore/QAbstractItemModel>

#include "Core/Function"

TreeItem::TreeItem(TreeItem* parent)
{
  m_parent = 0;
  if (parent)
  { parent->append(this); }
}

int TreeItem::row() const
{
  if (m_parent)
  { return m_parent->children().indexOf(const_cast<TreeItem*>(this)); }

  return 0;
};

void CategoryItem::append(TreeItem* item)
{
  if (item && item->m_parent != this)
  {
    item->m_parent = this;
    m_children.append(item);
  }
}

void CategoryItem::remove(TreeItem* item)
{ delete m_children.takeAt(item->row()); }

void CategoryItem::clear()
{
  if (hasChildren())
  {  qDeleteAll(m_children.begin(), m_children.end()); }
}

FunctionItem::FunctionItem(const Function& function, TreeItem* parent) : TreeItem(parent),
  m_function(function.clone())
{ }

FunctionItem::~FunctionItem()
{ delete m_function; };

QString FunctionItem::text() const
{ return m_function->name(); }