#include "logindialog.h"
#include "ui_logindialog.h"
#include "ui_chatwindow.h"
#include "gui.h"



LoginDialog::LoginDialog(ChatWindow* chatPointer,Gui* guiPointer) :QDialog(nullptr),ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    ui->inputServer->setText("127.0.0.1");
    mainWindow = chatPointer;
    chatGui = guiPointer;
}



LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::connected()
{
    mainWindow->setName(ui->inputName->text());
    mainWindow->setServer("Server: " + ui->inputServer->text());
    mainWindow->clearHistory();
    this->close();
}



void LoginDialog::userNameTaken()
{
    ui->errorMessage->setText("That name is taken");
    ui->inputName->clear();
}



void LoginDialog::noConnection()
{
    ui->errorMessage->setText("Server timout. The server is down or invalid address!");
}



void LoginDialog::disconnectedFromServer()
{
}


//------------------------------------------------------------------
//обработка отмены на модальном окне для логина
void LoginDialog::on_buttonBox_rejected()
{
    this->close();
    mainWindow->close();
}


void LoginDialog::on_buttonBox_accepted()
{   ui->errorMessage->setText("");
    if (ui->inputName->text()=="User" or not(ui->inputName->isModified()))
    {
        ui->errorMessage->setText("Name not allowed");
    }
    else if (ui->inputServer->text().contains(" ") or ui->inputServer->text()=="")
    {
        ui->errorMessage->setText("Invalid server name");
    }
    else
    {
        chatGui->createClient(ui->inputName->text(),ui->inputServer->text());
    }
}

