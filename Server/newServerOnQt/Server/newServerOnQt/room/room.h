#ifndef room_H
#define room_H

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <stdexcept>
#include <QDir>
#include <QDate>
#include <QString>
#include <QReadWriteLock>
#include "../getTime.h"
#include "../message/message.h"
#include "../master/master.h"

class Room {
public:

    Room(std::string,class Master*);
    virtual ~Room();

    virtual void receiveMessage(Message);
    virtual void sendMessage(Message);
    void createRoom(std::string);
    void addRoom(Room*);
    void removeRoom(Room*);
    virtual void chooseRoom(Room*);
    std::string getName();
    Room* getParentRoom();
    Room* getRoom(std::string);
    Message getMessage(unsigned int i);
    virtual std::vector<std::string> getStruct();
    virtual void requestStruct();
    void listUsers();
    std::vector<Message> log;
    
protected:

    friend void throwUp(Room* inRoom);
    friend void ifRoomRemove(Room* inRoom);
    unsigned int getPosOfRoom(std::string name) const;
    void sendMessageAll(Message);
    
    
    std::string filepath="";
    std::string date="";
    std::string name;

    std::vector<Room*> rooms;
    Room* parentRoom = nullptr;
    Master* masterPointer = nullptr;

    QReadWriteLock msgQueueLock;
};



class Thread;

class User : public Room
{
public:
    User(std::string inName, Master* master) : Room(inName,master) {};
    ~User();
    std::string name;
    void sendMessage(Message);
    void receiveMessage(Message);

    void setFilePath();
    void readAllFromFile();
    void chooseRoom(Room*);
    void initRoom(std::string);
    void setThread(Thread*);
    std::vector<std::string> getStruct();
    void requestStruct();
    
protected:
    Thread* thread;
    
};

#endif
