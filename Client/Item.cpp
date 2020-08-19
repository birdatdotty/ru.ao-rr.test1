#include "Item.h"
#include <QJsonDocument>

Item::Item(QString name, QString time) :name(name),time(time) {}

Item::Item(QJsonObject obj)
    : name(obj["name"].toString()),
      time(obj["time"].toString())
{}

QString Item::getName() const {return name;}

QString Item::getTime() const {return time;}

QJsonObject Item::getJson() const
{
    QJsonObject obj;
    obj["name"] = name;
    obj["time"] = time;

    return obj;
}

QString Item::json() const
{
        QJsonDocument doc(getJson());
        return doc.toJson(QJsonDocument::Indented);
}
