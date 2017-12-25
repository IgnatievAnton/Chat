/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QVBoxLayout *verticalLayout;
    QLineEdit *inputServer;
    QLineEdit *inputName;
    QVBoxLayout *verticalLayout_2;
    QLabel *name;
    QLabel *adress;
    QLabel *errorMessage;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->setWindowModality(Qt::ApplicationModal);
        LoginDialog->resize(400, 185);
        LoginDialog->setModal(true);
        gridLayout = new QGridLayout(LoginDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        buttonBox = new QDialogButtonBox(LoginDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        inputServer = new QLineEdit(LoginDialog);
        inputServer->setObjectName(QStringLiteral("inputServer"));
        inputServer->setAcceptDrops(true);

        verticalLayout->addWidget(inputServer);

        inputName = new QLineEdit(LoginDialog);
        inputName->setObjectName(QStringLiteral("inputName"));

        verticalLayout->addWidget(inputName);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        name = new QLabel(LoginDialog);
        name->setObjectName(QStringLiteral("name"));

        verticalLayout_2->addWidget(name);

        adress = new QLabel(LoginDialog);
        adress->setObjectName(QStringLiteral("adress"));

        verticalLayout_2->addWidget(adress);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        errorMessage = new QLabel(LoginDialog);
        errorMessage->setObjectName(QStringLiteral("errorMessage"));

        gridLayout->addWidget(errorMessage, 2, 0, 1, 2);

        QWidget::setTabOrder(inputServer, inputName);
        QWidget::setTabOrder(inputName, buttonBox);

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Login", 0));
        inputServer->setText(QString());
        name->setText(QApplication::translate("LoginDialog", "Server adress:", 0));
        adress->setText(QApplication::translate("LoginDialog", "User name:", 0));
        errorMessage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
