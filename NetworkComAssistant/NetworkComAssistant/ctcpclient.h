#ifndef CTCPCLIENT_H
#define CTCPCLIENT_H

#include <QObject>

class CTcpClient : public QObject
{
    Q_OBJECT
public:
    explicit CTcpClient(QObject *parent = nullptr);

signals:

};

#endif // CTCPCLIENT_H
