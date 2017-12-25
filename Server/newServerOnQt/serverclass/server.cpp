#include "server.h"
using namespace std;

Server::Server(Master* masterptr, QObject *parent) : QTcpServer(parent)
{
    masterPointer=masterptr;
}


void Server::start()
{
    if(!this->listen(QHostAddress::Any,40001))
    {
        qDebug() <<"could not start server";
    }
}


void Server::incomingConnection(qintptr handle) //многопоточность
{
    Thread *currentThread = new Thread(handle, masterPointer, this);
    
    connect(currentThread,SIGNAL(finished()),currentThread,SLOT(deleteLater()));
    currentThread->start();
}
