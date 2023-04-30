#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QHostInfo>
#include <QNetworkInterface>
#include <QMessageBox>
#include <QDateTime>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMainWindow();

    //工作类和线程类都不能指定父指针
    pudp = new CUdp;
    pudpThread = new QThread;
    pudp->moveToThread(pudpThread);
    pudpThread->start();

    pfileIO = new CFileIO;
    pfileIOThread = new QThread;
    pfileIO->moveToThread(pfileIOThread);
    pfileIOThread->start();

    //需要注册QAbstractSocket::SocketState类型用于多线程信号传递
    //QObject::connect: Cannot queue arguments of type 'QAbstractSocket::SocketState'
    qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
    qRegisterMetaType<QHostAddress>("QHostAddress");
    connect(pudp, &CUdp::socketStateChanged, this, &MainWindow::onSocketStateChanged);
    connect(this, &MainWindow::udpBindPort, pudp, &CUdp::onBindPort);
    connect(pudp, &CUdp::bindFeedback, this, &MainWindow::onUdpBindFeedback);
    connect(this, &MainWindow::udpAbortPort, pudp, &CUdp::onAbortPort);
    connect(pudp, &CUdp::recvDataRead, this, &MainWindow::onProcessRecvData);
    connect(this, &MainWindow::udpSendData, pudp, &CUdp::onSendData);
    connect(m_ptimer, &QTimer::timeout, this, &MainWindow::onTimeOut);
    connect(this, &MainWindow::getSendFile, pfileIO, &CFileIO::onGetSendFile);
    connect(pfileIO, &CFileIO::readDataFromFile, this, &MainWindow::onReadDataFromFile);
    connect(this, &MainWindow::createRecvFile, pfileIO, &CFileIO::onCreateRecvFile);
    connect(this, &MainWindow::writeRecvMsgToFile, pfileIO, &CFileIO::onWriteRecvMsgToFile);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pudp;
    delete pfileIO;
    delete pudpThread;
    delete pfileIOThread;
}

void MainWindow::on_cmb_protocal_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        m_protocalType = 0;
        ui->le_remoteIP->setEnabled(true);
        break;
    case 1:
        m_protocalType = 1;
        ui->le_remoteIP->clear();
        ui->le_remoteIP->setEnabled(false);
        break;
    default:
        break;
    }
}

void MainWindow::on_btn_connect_clicked()
{
    if(ui->btn_connect->text() == "连接")
    {
        ui->btn_connect->setText("断开连接");
        if(ui->le_localPort->text().isEmpty())
        {
            QMessageBox::warning(this, "警告", "请输入要绑定的端口！");
            return;
        }
        quint16 port = ui->le_localPort->text().toUInt();
        emit udpBindPort(port);
    }
    else
    {
        ui->btn_connect->setText("连接");
        emit udpAbortPort();
        ui->txe_rec->setTextColor(QColor("red"));
        QDateTime dateTime= QDateTime::currentDateTime();
        ui->txe_rec->append(dateTime.toString("[yyyy-MM-dd hh:mm:ss]") + "端口解除绑定！");
    }
}

//选择发送数据源文件
void MainWindow::on_chk_sendFromFile_stateChanged(int arg1)
{
    if(ui->chk_sendFromFile->isChecked())
    {
        ui->btn_send->setText("发送文件");
        QString fileName = QFileDialog::getOpenFileName(this, "选择数据源文件", ".", "(*.txt)");
        if(!fileName.isEmpty())
        {
            readBuffer.clear(); //清空读取缓冲区
            emit getSendFile(fileName);
        }
    }
    else
    {
        ui->btn_send->setText("发送");
    }
}

//发送按钮
void MainWindow::on_btn_send_clicked()
{
    if(m_plblStatus->text() == "状态：UnconnectedState")
    {
        QMessageBox::warning(this, "警告", "请绑定端口后再发送！");
        return;
    }

    if(ui->chk_sendFromFile->isChecked()) //发送数据源文件
    {
        if(!readBuffer.isEmpty())
        {
            sendData(readBuffer);
        }
    }
    else
    {
        if(ui->txe_send->toPlainText().isEmpty())
        {
            QMessageBox::warning(this, "警告", "不能发送空消息！");
            return;
        }

        if(!ui->chk_sendPeriod->isChecked()) //直接发送文本框数据
        {
            QString sendMsg = ui->txe_send->toPlainText();
            sendData(sendMsg);
        }
        else //定时发送文本框数据
        {
            if(ui->btn_send->text() == "发送")
            {
                ui->btn_send->setText("停止发送");
                int interval = ui->le_sendPeriod->text().toInt();
                m_ptimer->setInterval(interval);
                m_ptimer->start();
            }
            else
            {
                ui->btn_send->setText("发送");
                m_ptimer->stop();
            }
        }
    }
}

//选择接收数据保存文件路径
void MainWindow::on_chk_recSaveToFile_stateChanged(int arg1)
{
    if(ui->chk_recSaveToFile->isChecked())
    {
        QString filePath = QFileDialog::getExistingDirectory(this, "选择保存文件路径", ".");
        if(!filePath.isEmpty())
        {
            emit createRecvFile(filePath);
        }
    }
}

//清空接收区
void MainWindow::on_act_clearRecArea_triggered()
{
    ui->txe_rec->clear();
}

//清空发送区
void MainWindow::on_act_clearSendArea_triggered()
{
    ui->txe_send->clear();
}

//退出程序
void MainWindow::on_act_exit_triggered()
{
    this->close();
}

//socket状态实时显示
void MainWindow::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
    case QAbstractSocket::UnconnectedState:
        m_plblStatus->setText("状态：UnconnectedState");
        break;
    case QAbstractSocket::HostLookupState:
        m_plblStatus->setText("状态：HostLookupState");
        break;
    case QAbstractSocket::ConnectingState:
        m_plblStatus->setText("状态：ConnectingState");
        break;
    case QAbstractSocket::ConnectedState:
        m_plblStatus->setText("状态：ConnectedState");
        break;
    case QAbstractSocket::BoundState:
        m_plblStatus->setText("状态：BoundState");
        break;
    case QAbstractSocket::ClosingState:
        m_plblStatus->setText("状态：ClosingState");
        break;
    case QAbstractSocket::ListeningState:
        m_plblStatus->setText("状态：ListeningState");
        break;
    default:
        break;
    }
}

//udp连接反馈
void MainWindow::onUdpBindFeedback(bool res, quint16 port)
{
    QDateTime dateTime= QDateTime::currentDateTime();
    if(res)
    {
        ui->txe_rec->setTextColor(QColor("green"));
        ui->txe_rec->append(dateTime.toString("[yyyy-MM-dd hh:mm:ss]") + "端口绑定成功: " + QString::number(port));
    }
    else
    {
        ui->txe_rec->setTextColor(QColor("red"));
        ui->txe_rec->append(dateTime.toString("[yyyy-MM-dd hh:mm:ss]") + "端口绑定失败！");
    }
}

//处理接收数据
void MainWindow::onProcessRecvData(QByteArray datagram, QHostAddress peerAddr, quint16 peerPort)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString recMsg;
    if(ui->rdo_recAscii->isChecked())
    {
        recMsg = QString::fromUtf8(datagram);
    }
    else
    {
        for (int i = 0; i < datagram.size(); ++i)
        {
            recMsg += QString("%1 ").arg((quint8)datagram[i],2,16,QLatin1Char('0'));
        }
    }
    ui->txe_rec->setTextColor(QColor("blue"));
    ui->txe_rec->append(QString("%1接收来自(%2:%3)的消息>").arg(dateTime.toString("[yyyy-MM-dd hh:mm:ss]"), peerAddr.toString(), QString::number(peerPort)));
    ui->txe_rec->append(recMsg);
    emit writeRecvMsgToFile(recMsg);
}

//计时器到时
void MainWindow::onTimeOut()
{
    QString sendMsg = ui->txe_send->toPlainText();
    sendData(sendMsg);
}

//文件IO反馈
void MainWindow::onIOFeedback(quint8 feedback)
{
    switch (feedback)
    {
    case 0:
        QMessageBox::warning(this, "警告", "文件打开失败，请检查！");
        break;
    case 1:
        QMessageBox::warning(this, "警告", "创建保存文件失败！");
        break;
    case 2:
        QMessageBox::warning(this, "警告", "写入文件不存在，请检查！");
        break;
    default:
        break;
    }
}

//读取文件数据到缓冲区
void MainWindow::onReadDataFromFile(QString data)
{
    readBuffer = data;
}

void MainWindow::initMainWindow()
{
    //获取本机主机名
    QString strlocalHostName = QHostInfo::localHostName();
    this->setWindowTitle("网络通讯助手：" + strlocalHostName);

    try
    {
        ui->cmb_localIP->addItems(getLocalIP());
    }
    catch (int err)
    {
        if(err == -1)
        {
            QMessageBox::warning(this, "警告", "未找到有效IP，请检查本机网络设置");
        }
    }

    QStringList listProtocal;
    listProtocal << "udp单播" << "udp广播" << "tcp客户端" << "tcp服务端";
    ui->cmb_protocal->addItems(listProtocal);

    //把2个radio button放在一个widget里可实现单选按钮组的功能
    ui->rdo_recAscii->setChecked(true);
    ui->rdo_sendAscii->setChecked(true);

    m_plblStatus = new QLabel("准备");
    ui->statusbar->addWidget(m_plblStatus);

    m_ptimer = new QTimer(this);
}

//获取本机IP地址列表
QStringList MainWindow::getLocalIP()
{
    QList<QHostAddress> listAddress = QNetworkInterface::allAddresses();
    QStringList listLocalIP;
    if (!listAddress.isEmpty())
    {
        foreach (QHostAddress addr, listAddress)
        {
            if (addr.protocol() == QAbstractSocket::IPv4Protocol &&
                    addr != QHostAddress::Null &&
                    addr != QHostAddress::LocalHost)
            {
                listLocalIP.push_back(addr.toString());
            }
        }
    }
    if(!listLocalIP.isEmpty())
    {
        return listLocalIP;
    }
    else
    {
        throw -1;
    }
}

//发送数据
void MainWindow::sendData(const QString &sendMsg)
{
    QByteArray datagram;
    if(ui->rdo_sendAscii->isChecked())
    {
        datagram = sendMsg.toUtf8();
    }
    else
    {
        QString strTemp = sendMsg;
        strTemp.replace(" ", "");
        if((strTemp.size()%2) != 0)
        {
            strTemp += "0";
        }
        for(int i = 0; i < (strTemp.size()/2); ++i)
        {
            datagram.push_back(static_cast<char>(strTemp.midRef(i*2, 2).toShort(nullptr, 16)));
        }
    }

    QString tarIP = ui->le_remoteIP->text();
    QHostAddress tarAddr(tarIP); //目标Ip地址
    quint16 tarPort = ui->le_remotePort->text().toUShort(); //目标端口

    switch (m_protocalType)
    {
    case 0:
        emit udpSendData(datagram, tarAddr, tarPort);
        break;
    case 1:
        emit udpSendData(datagram, QHostAddress::Broadcast, tarPort);
        break;
    default:
        break;
    }
}

