#include "Conn.h"

#include <QWebSocket>

Conn::Conn(quint16 port, QObject *parent)
    : QObject(parent),
      m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Server"),
                                              QWebSocketServer::NonSecureMode,
                                              this))
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &Conn::onNewConnection);
//        connect(m_pWebSocketServer, &QWebSocketServer::closed,
//                this, &Conn::closed);
    }
}

void Conn::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Conn::processTextMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &Conn::socketDisconnected);

    m_clients << pSocket;
//    qInfo() << m_clients;
//    qInfo() <<  pSocket->peerAddress().toString() + ":" + QString::number( pSocket->peerPort() ) << pSocket->peerPort();
    changeConnList();
}
void Conn::processTextMessage(QString message) {
    if (message != "get") return;
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        if (!model)
            pClient->sendTextMessage("[]");
        else
            pClient->sendTextMessage(model->json());
    }
}
void Conn::socketDisconnected() {
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
    changeConnList();
}

void Conn::changeConnList() {
    clientsList.clear();
    for (QWebSocket* c: m_clients) {
        clientsList.append(c->peerAddress().toString() +
                         ":" +
                         QString::number( c->peerPort() ));
    }
//    qInfo() << clientsList;
    updateConnections(clientsList);
}
