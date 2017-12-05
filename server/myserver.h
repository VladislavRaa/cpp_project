#ifndef MYSERVER_H
#define MYSERVER_H
#include <QCommandLineParser>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDataStream>
#include <QTime>
#include <iostream>

class QTcpServer;
class QTcpSocket;

class MyServer : public QObject {
Q_OBJECT

public:
    explicit MyServer(quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);

Q_SIGNALS:
    void closed();

public Q_SLOTS:
    void sendToClient(QTcpSocket* pSocket, const QString& str);
         QString slotReadClient();
    virtual void slotNewConnection();
            void game();


private:
    QTcpServer* m_pTcpSocket;     //main attribute
    quint16     m_nNextBlockSize;  //size of package
    bool m_debug;

};

#endif // MYSERVER_H
