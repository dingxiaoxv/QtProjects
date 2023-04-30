# NetworkComAssistant
Qt-网络通讯助手

![image-20221108144806123](/home/dyx/snap/typora/76/.config/Typora/typora-user-images/image-20221108144806123.png)

# 1. 获取本地主机名和IP

```c++
void MainWindow::getHostInfo()
{
    //获取本机主机名
    QString strlocalHostName = QHostInfo::localHostName();
    this->setWindowTitle("网络通讯助手：" + strlocalHostName);
    //获取本机所有IP地址列表
    QList<QHostAddress> listAddress = QNetworkInterface::allAddresses();
    if (!listAddress.isEmpty())
    {
        foreach (QHostAddress addr, listAddress)
        {
            if (addr.protocol() == QAbstractSocket::IPv4Protocol &&
                    addr != QHostAddress::Null &&
                    addr != QHostAddress::LocalHost)
            {
                ui->le_localIP->setText(addr.toString());
                break;
            }
        }
    }
}
```

