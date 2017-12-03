#include "MainWindow.h"
#include <QRegExp>
#include "qdynamicbutton.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);

    stackedWidget->setCurrentWidget(loginPage);
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
}


void MainWindow::on_loginButton_clicked()
{
    stackedWidget->setCurrentWidget(chatPage); //For testing Chat page
    socket->connectToHost("127.0.0.1", 4200);

}


void MainWindow::on_sayButton_clicked()
{
    QString message = sayLineEdit->text().trimmed();

    if(!message.isEmpty())
    {
        socket->write(QString(message + "\n").toUtf8());
    }
    sayLineEdit->clear();

    sayLineEdit->setFocus();
}

void MainWindow::readyRead()
{
    while(socket->canReadLine())
    {
        QString line = QString::fromUtf8(socket->readLine()).trimmed();
        QRegExp messageRegex("^([^:]+):(.*)$");
        QRegExp usersRegex("^/users:(.*)$");
        if(usersRegex.indexIn(line) != -1)
        {
            QStringList users = usersRegex.cap(1).split(",");
            qDebug() <<users;


            QLayoutItem *child;
            while ((child = nameLine->takeAt(0)) != 0)
            {
                delete child->widget();
                delete child;
            }
            foreach(QString user, users)
            {

                QDynamicButton *button = new QDynamicButton(this);
                button ->setText(user);
                button ->setFixedSize(150,50);
                button ->setStyleSheet("background-color: white");
                nameLine->addWidget(button);
            }
        }
        else if(messageRegex.indexIn(line) != -1)
        {
            QString user = messageRegex.cap(1);
            QString message = messageRegex.cap(2);

            roomTextEdit->append("<b>" + user + "</b>: " + message);
        }
    }
}

void MainWindow::connected()
{
    stackedWidget->setCurrentWidget(chatPage);
    socket->write(QString("/me:" + userLineEdit->text() + "\n").toUtf8());
}

void MainWindow::newChat()
{

}
