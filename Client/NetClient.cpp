
#include "NetClient.h"
#include "gui.h"

using namespace std;

NetClient::NetClient(QString username, QString inAddress, Gui* myGui, QObject *parent) : QObject(parent)
{
    guiPointer = myGui;
    name=username;
    address=inAddress;
    compare += 0x1F;//символ рвзделения команд у сокета
    breaker +=0x1E;//концовка команд у сокета
}

// ---------------------------------------------
//Инициализация сокета
void NetClient::start()
{
    TcpSocket = new QTcpSocket(this);
    
    connect(TcpSocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(TcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    //метаинформация о пользователе
    QHostInfo info = QHostInfo::fromName(address);
    
    if (info.addresses().size() == 0)
    {
        guiPointer->noConnection();
    }
    else
    {
        TcpSocket->connectToHost(info.addresses().at(0),quint16(40001));
        if(!TcpSocket->waitForConnected(1000))
        {
            guiPointer->noConnection();
        }
    }
}


void NetClient::connected()
{
    QByteArray array = "/initiate";
    array += compare; //unit separator
    array += name;
    array += breaker;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}



void NetClient::disconnected()
{
    guiPointer->disconnectedFromServer();
    
}


void NetClient::readyRead()
{
    QString inData = "";
    if( not(incompleteCommand.isEmpty()))
    {
        inData = incompleteCommand;
        incompleteCommand = "";
    }
    QByteArray Data = TcpSocket->readAll();
    QString commandName = "";
    inData += Data;
    QString rest = "";
    int n = inData.indexOf(breaker);    //возвращает позицию символа прерывания  если нет то -1
    int i;
    if(inData.indexOf(breaker) == -1 )
    {
        incompleteCommand = inData;
        return;
    }
    
    do
    {
        rest = inData.mid(n+1);       //копирует от н+1 до конца
        inData = inData.left(n);      //возвращает первые н символов
        i = inData.indexOf(compare);
        commandName = inData.left(i);
        
        inData = inData.mid(i+1);
        
        QString temp = inData;
        string stdInData = temp.toStdString();
        
        // Проверка команды на запск
        if (commandName == "/reinitiate")
        {
            guiPointer->userNameTaken();        //повтор пользователя
            break;
        }
        
        else if ( commandName == "/userAccepted")
        {
            guiPointer->connected();            //подключение пользователя
        }

        
        else if (commandName == "/message")
        {
            handleMessage(inData);        // отправка сообщения
        }
        
        else if ( commandName == "/requestStruct")
        {
            handleRequestStruct();
        }
        
        else if ( commandName == "/structure" )
        {
            handleStructure(inData);
        }
        
        else
        {
            cout << "Unknown command: " << endl;
            inData = "";
            commandName = "";
            incompleteCommand = "";
            return;
        }
        
        inData = rest;
        n = inData.indexOf(breaker);
        commandName = "";
        
    }
    while (n != -1 );
}



void NetClient::sendMessage(QString from, QString to, QString message)
{
    QByteArray array = "/message";
    array += compare; //unit separator
    array += from;
    array += compare;
    array += to;
    array += compare;
    array += message;
    array += breaker;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}



void NetClient::setName(QString inName)
{
    name=inName;
}


void NetClient::getStruct()
{
    QByteArray array = "/structure";
    array += compare;
    array += breaker;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}


// ------------------------------------------------
// Парсинг байт кода пришедшего с сервера
void NetClient::handleMessage(QString inData)
{
    int i;
    // От кого
    i = inData.indexOf(compare);
    QString from = inData.left(i);
    inData = inData.mid(i+1);
    
    // кому
    i = inData.indexOf(compare);
    QString to = inData.left(i);
    inData = inData.mid(i+1);
    
    // сообщение
    i = inData.indexOf(compare);
    QString contents = inData.left(i);
    inData = inData.mid(i+1);
    
    // время
    QString dateTime = inData;
    
    //перрессылка сообщения через метод
    guiPointer->receiveMessage(from, to, contents, dateTime);
    
}



void NetClient::handleRequestStruct()
{
    getStruct();
}



void NetClient::handleStructure(QString inData)
{
    QVector<QString> output;
    int i = inData.indexOf(compare);
    
    while(i  != -1)
    {
        QString data = inData.left(i);
        inData = inData.mid(i+1);
        output.push_back(data);
        i = inData.indexOf(compare);
    }
    output.push_back(inData);
    guiPointer->updateStruct(output);
    
}




