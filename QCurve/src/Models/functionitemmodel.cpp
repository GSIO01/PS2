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

#include "functionitemmodel.h"

#include "Core/Function"

#include "treeitem.h"

#include <QtCore/QDebug>

FunctionItemModel::FunctionItemModel(QObject* parent)
  : QAbstractItemModel(parent)
{ m_root = new CategoryItem(QString()); }

FunctionItemModel::~FunctionItemModel()
{ delete m_root; }

void FunctionItemModel::addCategory(const QString& name, const QString& parent)
{
  if (parent.isEmpty())
  { m_root->append(new CategoryItem(name)); }
  else
  {
    for (int i = 0; i < m_root->children().size(); i++)
    {
      if (m_root->children().at(i)->text() == parent)
      {
	m_root->children().at(i)->append(new CategoryItem(name));
	break;
      }
    }
  }
}

void FunctionItemModel::addFunction(const Function& function, const QString& parent)
{
  if (parent.isEmpty())
  { m_root->append(new FunctionItem(function)); }
  else
  {
    for (int i = 0; i < m_root->children().size(); i++)
    {
      if (m_root->children().at(i)->text() == parent)
      {
	m_root->children().at(i)->append(new FunctionItem(function));
	break;
      }
    }
  }
}

Function* FunctionItemModel::functionAt(const QModelIndex& idx)
{
  if (!idx.isValid())
  { return 0; }

  TreeItem* item = 0;
  if (!idx.parent().isValid())
  { item = m_root->children().at(idx.row()); }
  else {item = m_root->children().at(idx.parent().row())->children().at(idx.row()); }

  if (item->type() == TreeItem::IT_Function)
  { return ((FunctionItem*)item)->function(); }

  return 0;
}

QVariant FunctionItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
  {
    switch (role)
    { default: return tr("Categories"); }

    switch (section)
    { default : tr("Categories"); }
  }

  return QAbstractItemModel::headerData(section, orientation, role);
}

QVariant FunctionItemModel::data(const QModelIndex& idx, int role) const
{
  if (!idx.isValid())
    return QVariant();

  TreeItem* item = static_cast<TreeItem*>(idx.internalPointer());
  switch(role)
  {
    case Qt::EditRole :
    case Qt::DisplayRole :
    { return item->text(); }

    //case Qt::ToolTipRole :;
    //{ return item.description(); }
  }

  return QVariant();
}

Qt::ItemFlags FunctionItemModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
  { return 0; }

  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

int FunctionItemModel::columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return 1;
}

int FunctionItemModel::rowCount(const QModelIndex& parent) const
{
  TreeItem* item;
  if (!parent.isValid())
  { item = m_root; }
  else { item = static_cast<TreeItem*>(parent.internalPointer()); }

  return item->children().count();
}

QModelIndex FunctionItemModel::parent(const QModelIndex& idx) const
{
  if (!idx.isValid())
  { return QModelIndex(); }

  TreeItem* childItem = static_cast<TreeItem*>(idx.internalPointer());
  TreeItem* parentItem = childItem->parent();

  if (parentItem == m_root)
  { return QModelIndex(); }

  return createIndex(parentItem->row(), 0, parentItem);
}

bool FunctionItemModel::hasChildren(const QModelIndex& parent) const
{
  if (!parent.isValid())
  { return true; }

  return static_cast<TreeItem*>(parent.internalPointer())->hasChildren();
}

QModelIndex FunctionItemModel::index(int row, int column, const QModelIndex& parent) const
{
  if (!hasIndex(row, column, parent))
  { return QModelIndex(); }

  TreeItem* parentItem;
  if (!parent.isValid())
  {  parentItem = m_root; }
  else { parentItem = static_cast<TreeItem*>(parent.internalPointer()); }

  TreeItem* childItem = parentItem->children().at(row);
  if (childItem)
  {  return createIndex(row, column, childItem); }

  return QModelIndex();
}
