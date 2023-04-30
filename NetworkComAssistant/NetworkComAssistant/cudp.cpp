#include "cudp.h"

CUdp::CUdp(QObject *parent)
    : QObject{parent}
{
    //QUdpSocket需要指定父指针this,否则QUdpSocket的信号会产生线程冲突
    //QObject: Cannot create children for a parent that is in a different thread.
    m_precvSocket = new QUdpSocket(this);
    connect(m_precvSocket, &QUdpSocket::stateChanged, this, &CUdp::socketStateChanged);
    connect(m_precvSocket, &QUdpSocket::readyRead, this, &CUdp::onDataReceived);
}

CUdp::~CUdp()
{
    if(m_precvSocket != nullptr)
    {
        delete m_precvSocket;
    }
}

void CUdp::onBindPort(quint16 port)
{
    bool res = m_precvSocket->bind(port);
    emit bindFeedback(res, m_precvSocket->localPort());
}

void CUdp::onAbortPort()
{
    m_precvSocket->abort();
}

void CUdp::onSendData(QByteArray datagram, QHostAddress tarAddr, quint16 tarPort)
{
    QUdpSocket sendSocket;
    qint64 len = sendSocket.writeDatagram(datagram, tarAddr, tarPort);
    emit sendFeedback(len);
}

void CUdp::onDataReceived()
{
    while (m_precvSocket->hasPendingDatagrams())
    {
        freeBytes.acquire();
        QByteArray datagram;
        QHostAddress peerAddr;
        quint16 peerPort;
        datagram.resize(m_precvSocket->pendingDatagramSize());
        m_precvSocket->readDatagram(datagram.data(), datagram.size(), &peerAddr, &peerPort);
        usedBytes.release();
        //emit recvDataRead(datagram, peerAddr, peerPort);
    }
}

