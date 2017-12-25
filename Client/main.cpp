#include "logindialog.h"
#include <QApplication>
#include "chatwindow.h"
#include "gui.h"


int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    Gui chatGui;
    return app.exec();
}
