#include <QtCore/QCoreApplication>
#include "myserver.h"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets server");
    parser.addHelpOption();
    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));

    parser.addOption(dbgOption);

    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for echoserver [default: 3425]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("3425"));
    parser.addOption(portOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);
    int port = parser.value(portOption).toInt();
    //connect
    MyServer *server = new MyServer(port, debug);
    QObject::connect(server, &MyServer::closed, &a, &QCoreApplication::quit);

    return a.exec();
}
