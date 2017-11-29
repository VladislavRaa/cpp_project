#include "myserver.h"

MyServer::MyServer(int nPort) :m_nNextBlockSize(0)
{
    m_ptcpServer = new QTcpServer(this); // signals


    if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) { //IP, port
       qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(m_ptcpServer->errorString());
       m_ptcpServer->close();
       return;
    }

    qDebug() << QString::fromUtf8("server run!");
    connect(m_ptcpServer, SIGNAL(newConnection()),
            this,         SLOT(slotNewConnection()));


}

/*virtual*/ void MyServer::slotNewConnection() {
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection(); //conect signal with newConnection()
    QObject::connect(pClientSocket, SIGNAL(disconnected()), //отсоединение
            pClientSocket, SLOT(deleteLater()));
    QObject::connect(pClientSocket, SIGNAL(readyRead()),    //готовность
            this,          SLOT(slotReadClient()));

    sendToClient(pClientSocket, "Server Response: Connected!");
}

void MyServer::slotReadClient()
{

    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;) {                                      //чтение пакетов
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        QTime   time;
        QString str;

        in >> time >> str;

        QString strMessage = time.toString() + " " + "Client has sended - " + str;
        qDebug() << QString(strMessage);

        m_nNextBlockSize = 0;
        sendToClient(pClientSocket, "Server Response: Received \"" + str + "\"");
    }
}

void MyServer::sendToClient(QTcpSocket* pSocket, const QString& str)
{

    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}
