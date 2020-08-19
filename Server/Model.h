// http://doc.crossplatform.ru/qt/4.3.2/model-view-creating-models.html
// https://wiki.qt.io/How_to_use_QAbstractListModel
// https://doc.qt.io/qt-5/qabstractitemmodel.html
// https://stackoverrun.com/ru/q/6634612

#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QList>

#include "Item.h"

class Model : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum MODEL{TIME = Qt::UserRole+1, JSON};
    Model(QList<Item*> data, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const {return 1;}
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex parent(const QModelIndex &index) const {return QModelIndex();}

    QString json();

private:
    QList<Item*> items;
};

#endif // MODEL_H
