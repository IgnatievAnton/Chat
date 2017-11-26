#ifndef MAIN_H
#define MAIN_H

#include <QStringList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QSet>

class QTcpSocket;

class Server: public QTcpServer
{
  Q_OBJECT
public:
    Server(QObject *parent=0);
    ~Server();
private slots:
    void readyRead();
    void disconnected();
    void sendUserList();

protected:
    void incomingConnection(int socketfd);

private:
    QSet<QTcpSocket*> clients;
    QMap<QTcpSocket*,QString> users;
};
#endif // MAIN_H
