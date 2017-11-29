#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTime>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDataStream>

class QTcpServer;

class MyServer : public QTcpServer {
Q_OBJECT
private:
    QTcpServer* m_ptcpServer; //main attribute
    quint16     m_nNextBlockSize; //size of package
private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);

public:
    MyServer(int nPort);

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();
};

#endif // MYSERVER_H
