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
