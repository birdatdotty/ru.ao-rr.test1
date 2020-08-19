#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QJsonObject>

class Item
{
public:
    Item(QString name, QString time);
    Item(QJsonObject obj);
    QString getName() const;
    QString getTime() const;
    QJsonObject getJson() const;
    QString json() const;

private:
    QString name;
    QString time;
};

#endif // ITEM_H
