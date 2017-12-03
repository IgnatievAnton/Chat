
TEMPLATE = app

DEPENDPATH += .
INCLUDEPATH += .

QT += widgets \
      network

RESOURCES += .


FORMS   += MainWindow.ui 

HEADERS += MainWindow.h \   
           qdynamicbutton.h

SOURCES +=  main.cpp \
            MainWindow.cpp \
            qdynamicbutton.cpp

