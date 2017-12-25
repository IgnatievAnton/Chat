#include "thread.h"

using namespace std;



void Thread::handleMessage(QString inData)
{
    int i;
    
    QString from;
    i = inData.indexOf(compare);
    from = inData.left(i);
    string stdFrom = from.toStdString();
    inData = inData.mid(i+1);
    
    QString to;
    i = inData.indexOf(compare);
    to = inData.left(i);
    string stdTo = to.toStdString();
    inData = inData.mid(i+1);
    
    QString contents;
    i = inData.indexOf(compare);
    contents = inData.left(i);
    string stdContents = contents.toStdString();
    inData = inData.mid(i+1);
    
    Message message(stdContents, stdFrom, stdTo);
    userPointer->sendMessage(message);
}


void Thread::handleInitiate(string stdInData)
{
    try{
            userPointer = masterPointer->createUser(stdInData);
            userPointer->setThread(this);

            // Все окей если ->
            QByteArray array = "/userAccepted";
            array += compare;
            array+= breaker;

            TcpSocket->write(array);

            if(!TcpSocket->waitForBytesWritten(5000))
            {
                try
                {
                    cout << "Couldn't write to client: " << "userAccepted" << "from: " << userPointer->getName() <<  endl;
                }
                catch(...)
                {
                }
            }
            handleStructure();
        }
        catch (...)
        {
            reinitiate();
        }
}


void Thread::handleStructure()
{
    vector<string> structure = userPointer->getStruct();
    
    QByteArray sendData;
    sendData += "/structure";
    sendData += compare;
    unsigned int i;
    
    for (i = 0; i < (structure.size()-1)  ; i++)
    {
        sendData += QString::fromStdString(structure.at(i));
        sendData += compare;
    }
    sendData += QString::fromStdString(structure.at(i));
    sendData += breaker;
    
    TcpSocket->write(sendData);
    TcpSocket->waitForBytesWritten(5000);
}


Thread::Thread(qintptr ID, Master* masterptr, QObject *parent) : QThread(parent)
{
    masterPointer=masterptr;
    this->socketDescriptor = ID;
    compare += 0x1F;
    breaker += 0x1E;
    userPointer = nullptr;
}

// ---------------------------------------
// run начало работы
void Thread::run()
{
    TcpSocket = new QTcpSocket();
    if(!TcpSocket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(TcpSocket->error());
        return;
    }
    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(TcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
    exec();
    
}


// ---------------------------
// Работа с сокетами
void Thread::readyRead()
{
    
    QByteArray Data = TcpSocket->readAll();
    
    int i;
    
    QString commandName;
    QString inData = Data;
    
    int n = inData.indexOf(breaker);
    QString rest;
    
    
    do {
        rest = inData.mid(n+1);
        inData = inData.left(n);
        i = inData.indexOf(compare);
        
        commandName = inData.left(i);
        
        inData = inData.mid(i+1);
        
        QString temp = inData;
        string stdInData = temp.toStdString();
        
        // проверка поступивших команд
        if (commandName == "/initiate") {
            handleInitiate(stdInData);
        }
        
        else if (commandName == "/message") {
            handleMessage(inData);
        }
        
        else if ( commandName == "/structure" ) {
            handleStructure();
        }
        
        else {
            cout << "Non-valid command: " << commandName.toStdString() << endl;
            TcpSocket->write("Non-valid command!");
            TcpSocket->waitForBytesWritten(5000);
            cout << socketDescriptor << "Data in: "<< stdInData<<endl;
        }
        
        inData = rest;
        n = inData.indexOf(breaker);
        
    }
    while (n != -1 ); // пока есть команды выполняем
}

// ---------------------------------------
void Thread::disconnected()
{
    try {
        if (userPointer != nullptr)
        {
            masterPointer->removeUser(userPointer->getName());
        }
    } catch (...)
    {
        
    }
    
    masterPointer->updateStructForAll();
    
    TcpSocket->deleteLater();
    exit(0);
}


void Thread::sendMessage(Message messageObject)
{
    QByteArray array = "/message";
    array += compare;
    array += QString::fromStdString(messageObject.getFrom());
    array += compare;
    array += QString::fromStdString(messageObject.getTo());
    array += compare;
    array += QString::fromStdString(messageObject.getMessage());
    array += compare;
    array += QString::fromStdString(messageObject.getServerTime());
    array += breaker;
    
    TcpSocket->write(array);
    
    if(!TcpSocket->waitForBytesWritten(5000))
    {
        try
        {
            cout << "Couldn't write to client: " << "message" << "from: " << userPointer->getName() <<  endl;
        }
        catch(...)
        {
        }
    }
}



// -----------------------------------------
// ответ если имя пользователя уже занято и disconnect
void Thread::reinitiate()
{
    QByteArray array = "/reinitiate";
    array += compare;
    array += breaker;
    
    TcpSocket->write(array);
    
    if(!TcpSocket->waitForBytesWritten(5000))
    {
        try
        {
            cout << "Couldn't write to client: " << "reinitiate" << "from: " << userPointer->getName() <<  endl;
        }
        catch(...)
        {

        }
    }
    disconnected();
}


void Thread::requestStruct()
{
    QByteArray array = "/requestStruct";
    array += compare;
    array += breaker;
    
    TcpSocket->write(array);
    
    if(!TcpSocket->waitForBytesWritten(5000))
    {
        try
        {
            cout << "Couldn't write to client: " << "requestStruct" << "from: " << userPointer->getName() <<  endl;
        }catch(...)
        {
        }
    }
}
