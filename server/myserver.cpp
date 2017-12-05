#include "myserver.h"

QT_USE_NAMESPACE

MyServer::MyServer(quint16 port, bool debug, QObject *parent) :
    QObject(parent), m_nNextBlockSize(0), m_debug(debug)
{

    m_pTcpSocket = new QTcpServer(this);

    if (m_pTcpSocket->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "Echoserver listening on port" << port;
            connect(m_pTcpSocket, SIGNAL(newConnection()),
                    this,         SLOT(slotNewConnection()));

    }
}
//QObject::connect(&Отправитель,SIGNAL(mysignal()),&Адресат,SLOT(myslot()));

void MyServer::slotNewConnection() {
    QTcpSocket* pClientSocket = m_pTcpSocket->nextPendingConnection(); //conect signal with newConnection()


    QObject::connect(pClientSocket, SIGNAL(disconnected()), //отсоединение
                     pClientSocket, SLOT(deleteLater()));

    QObject::connect(pClientSocket, SIGNAL(readyRead()),    //готовность
                     this,          SLOT  (game()));

}

QString MyServer::slotReadClient() {
    QTcpSocket* pClientSocket = (QTcpSocket*)sender(); //преобразование типов
    QDataStream in(pClientSocket);                     //преобразование типов

    //in.setVersion(QDataStream::Qt_4_2);
    QString str;

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


        in >> time >> str; //time to str

        QString strMessage = time.toString() + " " + "Client has sended - " + str;
        qDebug() << QString(strMessage);

        m_nNextBlockSize = 0;
        sendToClient(pClientSocket, "Chlen Server Response: Received \"" + str + "\"");
    }
    return str;
}

void MyServer::sendToClient(QTcpSocket* pSocket, const QString& str)
{

    std::cout << "MyServer::sendToClient()" << std::endl;
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}

void MyServer::game() {
    QString strMessage = "smile";
    std::cout << "MyServer::game()" << std::endl;
    qDebug() << slotReadClient();

    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);

    sendToClient(pClientSocket, "Server Response: Received" + strMessage);
}
