QMAKE_CXX	= g++
QMAKE_CC	= gcc

QT		+= core gui network widgets
ICON		= icon/Camfrog_Video_Chat_icon.ico

TARGET		= OfficeChat
TEMPLATE	= app

CONFIG		+= c++11
CONFIG		+= release

# ---- Files ----

SOURCES += main.cpp\ chatwindow.cpp logindialog.cpp NetClient.cpp \
    gui.cpp \


HEADERS  += chatwindow.h logindialog.h NetClient.h \
    gui.h \

FORMS    += chatwindow.ui logindialog.ui

RESOURCES += \
    myResources.qrc
