#ifndef CONN_H
#define CONN_H

#include <QObject>
#include <QWebSocketServer>
#include "Model.h"

class Conn: public QObject
{
    Q_OBJECT
public:
    explicit Conn(quint16 port, QObject *parent = nullptr);

    void setModel(Model* newModel) {
        model = newModel;
    }

signals:
    void closed();
    void updateConnections(QStringList conns);

private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void socketDisconnected();

    void changeConnList();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    QStringList clientsList;
    Model *model;
};

#endif // CONN_H
