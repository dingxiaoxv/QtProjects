#ifndef CTCPSERVER_H
#define CTCPSERVER_H

#include <QObject>

class CTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit CTcpServer(QObject *parent = nullptr);

signals:

};

#endif // CTCPSERVER_H
