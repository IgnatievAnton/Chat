
QMAKE_CXX	= g++
QMAKE_CC	= gcc

QMAKE_CXXFLAGS	+= -g


QT		+= core
QT		+= network
QT		-= gui

TARGET		= ChattYServer


CONFIG		+= console c++11
CONFIG		-= app_bundle

TEMPLATE	= app


SOURCES		+= main.cpp getTime.cpp master/master.cpp room/room.cpp user/User.cpp message/message.cpp serverclass/server.cpp serverclass/thread.cpp

HEADERS		+= master/master.h room/room.h message/message.h serverclass/thread.h serverclass/server.h

