/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QAction *actionBlack;
    QAction *actionDefault;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *roomTree;
    QTextBrowser *messageHistory;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *messageInput;
    QPushButton *sendButton;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuCustomize;
    QMenu *menuChange_theme;

    void setupUi(QMainWindow *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName(QStringLiteral("ChatWindow"));
        ChatWindow->resize(972, 793);
        QIcon icon;
        icon.addFile(QStringLiteral("icon/Camfrog_Video_Chat_icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ChatWindow->setWindowIcon(icon);
        actionBlack = new QAction(ChatWindow);
        actionBlack->setObjectName(QStringLiteral("actionBlack"));
        actionDefault = new QAction(ChatWindow);
        actionDefault->setObjectName(QStringLiteral("actionDefault"));
        centralWidget = new QWidget(ChatWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        roomTree = new QTreeWidget(centralWidget);
        roomTree->headerItem()->setText(0, QString());
        roomTree->setObjectName(QStringLiteral("roomTree"));

        horizontalLayout->addWidget(roomTree);

        messageHistory = new QTextBrowser(centralWidget);
        messageHistory->setObjectName(QStringLiteral("messageHistory"));
        QFont font;
        font.setFamily(QStringLiteral("Geeza Pro"));
        font.setPointSize(15);
        messageHistory->setFont(font);
        messageHistory->setMouseTracking(false);
        messageHistory->setAcceptDrops(false);
        messageHistory->setAutoFillBackground(true);
        messageHistory->setAcceptRichText(false);

        horizontalLayout->addWidget(messageHistory);

        horizontalLayout->setStretch(1, 75);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        messageInput = new QLineEdit(centralWidget);
        messageInput->setObjectName(QStringLiteral("messageInput"));

        horizontalLayout_2->addWidget(messageInput);

        sendButton = new QPushButton(centralWidget);
        sendButton->setObjectName(QStringLiteral("sendButton"));

        horizontalLayout_2->addWidget(sendButton);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        ChatWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(ChatWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ChatWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ChatWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ChatWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(ChatWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 972, 21));
        menuCustomize = new QMenu(menuBar);
        menuCustomize->setObjectName(QStringLiteral("menuCustomize"));
        menuChange_theme = new QMenu(menuCustomize);
        menuChange_theme->setObjectName(QStringLiteral("menuChange_theme"));
        ChatWindow->setMenuBar(menuBar);

        menuBar->addAction(menuCustomize->menuAction());
        menuCustomize->addAction(menuChange_theme->menuAction());
        menuChange_theme->addAction(actionBlack);
        menuChange_theme->addAction(actionDefault);

        retranslateUi(ChatWindow);

        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ChatWindow)
    {
        ChatWindow->setWindowTitle(QApplication::translate("ChatWindow", "OfficeChat", Q_NULLPTR));
        actionBlack->setText(QApplication::translate("ChatWindow", "Black", Q_NULLPTR));
        actionDefault->setText(QApplication::translate("ChatWindow", "Default", Q_NULLPTR));
        sendButton->setText(QApplication::translate("ChatWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        menuCustomize->setTitle(QApplication::translate("ChatWindow", "\320\242\320\265\320\274\321\213", Q_NULLPTR));
        menuChange_theme->setTitle(QApplication::translate("ChatWindow", "\320\222\321\213\320\261\320\276\321\200 \321\202\320\265\320\274\321\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
