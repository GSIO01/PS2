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

#ifndef TREEITEM_H
#define TREEITEM_H

#include <QtCore/QString>
#include <QtCore/QList>

class TreeItem
{
  public:
    enum ItemType
    {
      IT_Category,
      IT_Function
    };

    TreeItem(TreeItem* parent = 0);
    virtual ~TreeItem() { };

    TreeItem* parent() const { return m_parent; };
    int row() const;

    virtual QString text() const = 0;
    virtual ItemType type() const = 0;

    virtual bool hasChildren() const = 0;
    virtual const QList<TreeItem*>& children() const = 0;

    virtual void append(TreeItem* item) = 0;
    virtual void remove(TreeItem* item) = 0;
    virtual void clear() = 0;

  //protected:
    TreeItem* m_parent;
};

class CategoryItem : public TreeItem
{
  public:
    CategoryItem(const QString& text, TreeItem* parent = 0) : TreeItem(parent), m_text(text) { }
    virtual ~CategoryItem() { clear(); };

    QString text() const { return m_text; }
    ItemType type() const { return IT_Category; }

    bool hasChildren() const { return !m_children.isEmpty(); }
    const QList<TreeItem*>& children() const { return m_children; }

    void append(TreeItem* item);
    void remove(TreeItem* item);
    void clear();

  private:
    QString m_text;
    QList<TreeItem*> m_children;
};

class Function;
class FunctionItem : public TreeItem
{
  public:
    FunctionItem(const Function& function, TreeItem* parent = 0);
    virtual ~FunctionItem();

    QString text() const;
    ItemType type() const { return IT_Function; }

    Function* function() { return m_function; }

    bool hasChildren() const { return false; }
    const QList<TreeItem*>& children() const { return m_list; }

    void append(TreeItem* item) { Q_UNUSED(item); }
    void remove(TreeItem* item) { Q_UNUSED(item); }
    void clear() { }

  private:
    QList<TreeItem*> m_list; //always empty

    Function* m_function;
};

#endif