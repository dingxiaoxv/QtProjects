#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QAbstractSocket>
#include <QThread>
#include <QTimer>
#include "cudp.h"
#include "cfileio.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void udpBindPort(quint16 port);
    void udpAbortPort();
    void udpSendData(QByteArray datagram, QHostAddress tarAddr, quint16 tarPort);
    void getSendFile(QString fileName);
    void createRecvFile(QString filePath);
    void writeRecvMsgToFile(QString recvMsg);

private slots:
    //UI槽函数
    void on_cmb_protocal_currentIndexChanged(int index);
    void on_btn_connect_clicked();
    void on_chk_sendFromFile_stateChanged(int arg1);
    void on_btn_send_clicked();
    void on_chk_recSaveToFile_stateChanged(int arg1);
    void on_act_clearRecArea_triggered();
    void on_act_clearSendArea_triggered();
    void on_act_exit_triggered();

    //自定义槽函数
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onUdpBindFeedback(bool res, quint16 port);
    void onProcessRecvData(QByteArray datagram, QHostAddress peerAddr, quint16 peerPort);
    void onTimeOut();
    void onIOFeedback(quint8 feedback);
    void onReadDataFromFile(QString data);

private:
    Ui::MainWindow *ui;
    QLabel *m_plblStatus = nullptr;
    quint8 m_protocalType = 0; //通讯协议标识符 0:udp单播 1:udp广播 2:tcp客户端 3:tcp服务端
    QTimer *m_ptimer = nullptr;
    CUdp *pudp = nullptr;
    CFileIO *pfileIO = nullptr;
    QThread *pudpThread = nullptr, *pfileIOThread = nullptr;
    QString readBuffer;

    void initMainWindow();
    QStringList getLocalIP();
    void sendData(const QString &sendMsg);
};
#endif // MAINWINDOW_H
