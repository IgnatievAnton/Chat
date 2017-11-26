#include <QCoreApplication>
#include "main.h"
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    QCoreApplication a(argc, argv);
    Server *server = new Server();
    bool success =server ->listen(QHostAddress::Any, 4200);//Настройка порта и адресса
    if (!success)
        qFatal("Не удалось прослушать порт №4200");
    qDebug() << "Сервер готов к работе";
    return a.exec();
}
