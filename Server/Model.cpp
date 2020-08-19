#include "Model.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Model::Model(QList<Item *> data, QObject *parent) : QAbstractItemModel(parent), items(data) {}

int Model::rowCount(const QModelIndex &parent) const
{
    return items.count();
}

QModelIndex Model::index(int row, int column, const QModelIndex &parent) const {
    if(!parent.isValid()) // we should return a valid QModelIndex for root elements (whose parent
        return this->createIndex(row,column); // is invalid) only, because our model is flat
    else
        return QModelIndex();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= items.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return items.at(index.row())->getName();
    if (role == JSON)
        return items.at(index.row())->json();
    if (role == TIME)
        return items.at(index.row())->getTime();
    else
        return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

QString Model::json()
{
    QJsonArray retArr;
    for (Item* i: items)
        retArr.append(i->getJson());

    QJsonDocument doc(retArr);
    return doc.toJson(QJsonDocument::Compact);
}
