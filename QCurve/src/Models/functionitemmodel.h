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

#ifndef FUNCTIONITEMMODEL_H
#define FUNCTIONITEMMODEL_H

#include <QtCore/QAbstractItemModel>

class TreeItem;
class Function;
class FunctionItemModel : public QAbstractItemModel
{
  public:
    explicit FunctionItemModel(QObject* parent = 0);
    virtual ~FunctionItemModel();

    void addCategory(const QString& name, const QString& parent = QString());
    void addFunction(const Function& function, const QString& parent);

    Function* functionAt(const QModelIndex& idx);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& child) const;
    bool hasChildren(const QModelIndex& parent = QModelIndex()) const;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;

  private:
    TreeItem* m_root;
};

#endif
