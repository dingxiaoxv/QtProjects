#ifndef CFILEIO_H
#define CFILEIO_H

#include <QObject>
#include <QFile>

class CFileIO : public QObject
{
    Q_OBJECT
public:
    explicit CFileIO(QObject *parent = nullptr);
    void onGetSendFile(QString fileName);
    void onCreateRecvFile(QString filePath);
    void onWriteRecvMsgToFile(QString recvMsg);

signals:
    //0：文件读取错误
    //1: 创建保存文件失败
    //2: 写入文件不存在
    void IOFeedback(quint8 feedback);
    void readDataFromFile(QString data);

private:
    QFile m_recvFile, m_sendFile;

};

#endif // CFILEIO_H
