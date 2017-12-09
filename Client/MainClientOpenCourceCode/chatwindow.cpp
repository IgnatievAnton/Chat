#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "QString"
#include "QColor"
#include "gui.h"




ChatWindow::ChatWindow(Gui* guiPointer) :
    QMainWindow(nullptr),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    chatGui = guiPointer;
    smiley= {happyFace,sadFace,straightFace,xdFace,oFace,astronaut,batman,grandpa,ironman,spiderman,pirate,angry,laurel};

    //Setup default theme
    ui->messageInput->setStyleSheet("white");
    ui->roomTree->setStyleSheet("white");
    ui->messageHistory->setStyleSheet("white");
    this->setStyleSheet("none");
    ui->mainToolBar->setStyleSheet("none");
    
    // Получение директории исполняемого файла
    appdir = QCoreApplication::applicationDirPath();

}



void ChatWindow::receiveMessage(const QString from, const QString to, const QString message, const QString time)
{
    QString tempString = time;
    ui->messageHistory->moveCursor(QTextCursor::End);
    ui->messageHistory->setTextColor(Qt::black);
    ui->messageHistory->insertPlainText(tempString.remove(0,11).remove(5,7)+" | ");

 
    if(to == name && from != name)
    {
        lastWhisper=from;
        ui->messageHistory->setTextColor(Qt::cyan);
        ui->messageHistory->insertPlainText("Oт " + from + " вам ");
        ui->messageHistory->setTextColor(Qt::black);
    }
    else if (from == name && to != "Root" && to !=name)
    {
        ui->messageHistory->setTextColor(Qt::cyan);
        ui->messageHistory->insertPlainText("Oт вас " + to + ": ");
        ui->messageHistory->setTextColor(Qt::black);
    }
    else if (from == name && to == "Root")
    {
        ui->messageHistory->setTextColor(Qt::blue);
        ui->messageHistory->insertPlainText("Вы: ");
        ui->messageHistory->setTextColor(Qt::black);
    }
    else
    {
        ui->messageHistory->setTextColor(Qt::cyan);
        ui->messageHistory->insertPlainText( from + " ");
        ui->messageHistory->setTextColor(Qt::black);
    }
    //Входящие сообщения
    ui->messageHistory->insertHtml(smilieConvert(message));
    ui->messageHistory->insertPlainText("\n");
    ui->messageHistory->moveCursor(QTextCursor::End);
    if(ui->messageHistory->verticalScrollBar()->value() != ui->messageHistory->verticalScrollBar()->maximum())
    {

    }
    else
    {
        ui->messageHistory->verticalScrollBar()->setValue(ui->messageHistory->verticalScrollBar()->maximum());
    }

}



void ChatWindow::setName(QString inName)
{
    name = inName;
    ui->roomTree->setHeaderLabel("Вы зашли как " + name);
}



void ChatWindow::setServer(QString serverName)
{
    server = serverName;

}



void ChatWindow::updateStruct(QVector<QString> treeStruct)
{
    ui->roomTree->clear();
    QTreeWidgetItem *treeParent;
    treeParent=addRoot(treeStruct.at(0));
    for (int i=1; i< treeStruct.size(); i++)
    {
        if (treeStruct.at(i)=="User")
        {
            treeStruct.remove(i);
            while (i < treeStruct.size())
            {
                addLeaf(treeParent,treeStruct.at(i));
                i++;
            }
        }
        else
        {
            treeParent=addSubRoot(treeParent,treeStruct.at(i));
        }
    }
    ui->roomTree->expandAll();
}


//-----------------------------------------------------
//Добавление верхнего уровня (нашей мейн комнаты)
QTreeWidgetItem* ChatWindow::addRoot(const QString rootName)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->roomTree);
    item->setText(0,rootName);
    ui->roomTree->addTopLevelItem(item);
    return item;
}


//-----------------------------------------------------
//Добавление пользователя в нашу комнату как потомка в дерево
QTreeWidgetItem* ChatWindow::addSubRoot(QTreeWidgetItem *parent,const QString subRootName)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,subRootName);
    parent->addChild(item);
    return item;
}


//-------------------------------------------------------
//Добавление пользователя в нашу комнату как потомка в айтем
void ChatWindow::addLeaf(QTreeWidgetItem *parent,const QString leafName)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,leafName);
    parent->addChild(item);
}



ChatWindow::~ChatWindow()
{
    delete ui;
}


//---------------------------
// Отправка сообщения
void ChatWindow::on_sendButton_clicked()
{
    lastMessage=ui->messageInput->text();
    sendMessage();
    ui->messageInput->clear();
    receiver="Share chat";
    ui->sendButton->setText("Отправить");


}



void ChatWindow::on_messageInput_returnPressed()
{
    on_sendButton_clicked();

}



void ChatWindow::sendMessage(){
    if (ui->messageInput->text()=="")
        return;
    else
        chatGui->sendMessage(name,receiver,ui->messageInput->text());
}



void ChatWindow::clearHistory(){
    ui->messageHistory->clear();
}


//---------------------------------
// Темы
void ChatWindow::on_actionBlack_triggered()
{
    ui->messageInput->setStyleSheet("background-color: grey;");
    ui->roomTree->setStyleSheet("background-color: grey;");
    ui->messageHistory->setStyleSheet("background-color: grey;");
    this->setStyleSheet("background-color: black;");
    ui->mainToolBar->setStyleSheet("background-color: none;");
    ui->menuBar->setStyleSheet("background-color: none;");
    ui->sendButton->setStyleSheet("background-color: none;");
}

void ChatWindow::on_actionDefault_triggered()
{
    ui->messageInput->setStyleSheet("white");
    ui->roomTree->setStyleSheet("white");
    ui->messageHistory->setStyleSheet("white");
    this->setStyleSheet("white");
    

}

//----------------------------------------------------
// отправка выбранному пользователю из списка в дереве
void ChatWindow::on_roomTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    receiver = item->text(column);
    ui->sendButton->setText("To " + receiver);
    ui->messageInput->setFocus();
    ui->messageInput->setCursorPosition(0);
}



QString ChatWindow::smilieConvert(const QString inMessage){
    QString messageConv = inMessage.toHtmlEscaped();
    messageConv.replace(":)",smiley.at(0));
    messageConv.replace(":(",smiley.at(1));
    messageConv.replace(":|",smiley.at(2));
    messageConv.replace(":o",smiley.at(3));
    messageConv.replace("xD",smiley.at(4));
    messageConv.replace("astronaut",smiley.at(5));
    messageConv.replace("batman",smiley.at(6));
    messageConv.replace("grandpa",smiley.at(7));
    messageConv.replace("ironman",smiley.at(8));
    messageConv.replace("spiderman",smiley.at(9));
    messageConv.replace("pirate",smiley.at(10));
    messageConv.replace(":@",smiley.at(11));
    messageConv.replace("-+-",smiley.at(12));

    return messageConv;
}


