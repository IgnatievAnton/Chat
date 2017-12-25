#ifndef GUI_H
#define GUI_H
#include <QString>
class NetClient;
class LoginDialog;
class ChatWindow;



class Gui
{
public:
    Gui();
    void receiveMessage(QString from, QString to, QString message, QString servertime);
    void userNameTaken();
    void connectionTimeOut();
    void connected();
    void createClient(QString inName, QString inAddress);
    void noConnection();
    void sendMessage(QString from, QString to, QString message);
    void updateStruct(QVector<QString> treeStruct);
    void getStruct();
    void disconnectedFromServer();

    unsigned int historyCounter;
    
protected:
    NetClient* client = nullptr;
    LoginDialog* loginWindow = nullptr;
    ChatWindow* mainWindow = nullptr;

};

#endif
