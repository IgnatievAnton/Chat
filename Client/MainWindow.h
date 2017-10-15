
#include <QTcpSocket>

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent=0);

    private slots:
        void on_loginButton_clicked();

        void on_sayButton_clicked();

        void readyRead();
        void connected();

    private:
        QTcpSocket *socket;
};
