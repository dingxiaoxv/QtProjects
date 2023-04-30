#ifndef CUDP_H
#define CUDP_H

#include <QObject>
#include <QUdpSocket>
#include "global.h"

extern char g_szReadBuffer[BufferSize];
extern QSemaphore freeBytes;
extern QSemaphore usedBytes;


class CUdp : public QObject
{
    Q_OBJECT
public:
    explicit CUdp(QObject *parent = nullptr);
    ~CUdp();
    void onBindPort(quint16 port);
    void onAbortPort();
    void onSendData(QByteArray datagram, QHostAddress tarAddr, quint16 tarPort);

private slots:
    void onDataReceived();

signals:
    void socketStateChanged(QAbstractSocket::SocketState socketState);
    void bindFeedback(bool res, quint16 port);
    void recvDataRead(QByteArray datagram, QHostAddress peerAddr, quint16 peerPort);
    void sendFeedback(quint64 res);

private:
    QUdpSocket *m_precvSocket = nullptr;

};

#endif // CUDP_H
