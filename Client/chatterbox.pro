
TEMPLATE = app

DEPENDPATH += .
INCLUDEPATH += .

QT += \
        widgets \
     network

RESOURCES += .


FORMS   += MainWindow.ui 

HEADERS += MainWindow.h 

SOURCES += \
           main.cpp \
    MainWindow.cpp

