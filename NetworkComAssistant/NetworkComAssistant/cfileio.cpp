#include "cfileio.h"
#include <QTextStream>
#include <QDateTime>

CFileIO::CFileIO(QObject *parent)
    : QObject{parent}
{

}

void CFileIO::onGetSendFile(QString fileName)
{
    if(!fileName.isEmpty())
    {
        m_sendFile.setFileName(fileName);
    }
    if(!m_sendFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        emit IOFeedback(0);
    }
    QString data;
    QTextStream in(&m_sendFile);
    while (!in.atEnd())
    {
        data += in.readLine();
    }
    emit readDataFromFile(data);
}

void CFileIO::onCreateRecvFile(QString filePath)
{
    if(!filePath.isEmpty())
    {
        QDateTime dateTime = QDateTime::currentDateTime();
        QString fileName = QString("%1/%2.txt").arg(filePath, dateTime.toString("yyyy_MM_dd_hh:mm"));
        m_recvFile.setFileName(fileName);
    }

    if(!m_recvFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        emit IOFeedback(1);
    }
}

void CFileIO::onWriteRecvMsgToFile(QString recvMsg)
{
    if(!m_recvFile.exists())
    {
        emit IOFeedback(2);
        return;
    }
    QTextStream out(&m_recvFile);
    out << recvMsg << Qt::endl;
}
