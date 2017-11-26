QT += network
QT -= gui

TARGET = server
CONFIG += c++11 console
CONFIG -= app_bundle


TEMPLATE = app

SOURCES += main.cpp \
    server.cpp

HEADERS += \
    main.h
