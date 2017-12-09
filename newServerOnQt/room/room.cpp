#include "room.h"
#include <QDir>
#include <QString>
#include <QDebug>


using namespace std;


Room::Room(string inName,Master* master)
{
    masterPointer = master;
    name = inName;
}



void ifRoomRemove(Room* inRoom)
{
    User* userTemp = dynamic_cast<User*>(inRoom);
    if (userTemp == nullptr)
    {
        inRoom->masterPointer->removeRoom(inRoom->getName());
    }
}

void throwUp(Room* inRoom)
{
    inRoom->chooseRoom(inRoom->parentRoom->parentRoom);
}



Room::~Room()
{
    for_each(rooms.begin(), rooms.end(), ifRoomRemove);
    if ( parentRoom == nullptr)
    {
        rooms.clear();
    }
    else
    {
        parentRoom->removeRoom(this);
        for_each(rooms.begin(), rooms.end(), throwUp);
        parentRoom = nullptr;
    }
    masterPointer = nullptr;
}



unsigned int Room::getPosOfRoom(string name) const
{
    for( unsigned int i = 0 ; i < rooms.size() ; i++)
    {
        if(rooms.at(i)->getName() == name)
        {
            return i;
        }
    }
    throw logic_error("Error ");
    return 0;
}
void Room::removeRoom(Room* inRoom)
{
    unsigned int pos = getPosOfRoom(inRoom->getName());
    rooms.at(pos) = nullptr;
    rooms.erase(rooms.begin() + pos);
}



void Room::sendMessage(Message inMessage)
{
    string to = inMessage.getTo();
    string from = inMessage.getFrom();    
    if (inMessage.getTo() == inMessage.getFrom())
    {
        string temp = "Вы пишете сами себе, вы нормальный?";
        Message errorMessage(temp,name,from);
        getRoom(from)->receiveMessage(errorMessage);
    }
    else
    {
        try
        {
            getRoom(to)->receiveMessage(inMessage);
            getRoom(from)->receiveMessage(inMessage);
        }
        catch (...)
        {
            string temp = "Такого имени нет ";
            temp += to;
            temp += " в этой комнате!";
            Message errorMessage(temp,name,from);
            getRoom(from)->receiveMessage(errorMessage);
        }
    }
}





void Room::listUsers()
{
    for (unsigned int it = 0; it < rooms.size() ; it++)
    {
        User* userTemp = dynamic_cast<User*>(rooms.at(it));
        if( userTemp == nullptr )
            continue;
        else
            cout << rooms.at(it)->getName() << endl;
    }
    return;
}



void Room::receiveMessage(Message inMessage)
{
    string to = inMessage.getTo();
    if(to == name)
    {
        msgQueueLock.lockForWrite();
        log.push_back(inMessage);
        sendMessageAll(inMessage);
        msgQueueLock.unlock();
    }

    else
    {
        sendMessage(inMessage);
    }
}


void Room::sendMessageAll(Message inMessage)
{
    for (unsigned int i = 0; i < rooms.size(); i++)
    {
        User* userTemp = dynamic_cast<User*>(rooms.at(i));
        if ( userTemp == nullptr )
        {
            continue;
        }
        rooms.at(i)->receiveMessage(inMessage);
    }
}



void Room::addRoom(Room* inRoom)
{
    this->rooms.push_back(inRoom);
    inRoom->parentRoom = this;
}


string Room::getName()
{
    return name;
}


void Room::createRoom(std::string inName)
{
	addRoom(masterPointer->createRoom(inName));
}


Room* Room::getRoom(std::string name)
{
    for( unsigned int i = 0 ; i < rooms.size() ; i++)
    {
        if(rooms.at(i)->getName() == name)
        {
            return rooms.at(i);
        }
    }
    throw logic_error("No such room in Rooms");
    return nullptr;
}


Message Room::getMessage(unsigned int i)
{
    if (log.size() < i)
    {
        throw logic_error{"Error "};
    }
    return log.at(i);
}


void Room::chooseRoom(Room*)
{
    throw logic_error{"fail room."};
}



Room* Room::getParentRoom()
{
    return parentRoom;
}


vector<string> Room::getStruct()
{
    vector<string> structure;
    if ( parentRoom != nullptr )
    {
        structure.push_back(parentRoom->getName());
    }
    structure.push_back(name);
    structure.push_back("User");
    for (unsigned int i = 0; i < rooms.size() ; i++)
    {
        User* userTemp = dynamic_cast<User*>(rooms.at(i));
        if ( userTemp == nullptr )
        {
            structure.insert(structure.begin(),rooms.at(i)->getName());
        }
        else
        {
            structure.push_back(rooms.at(i)->getName());
        }
    }
    return structure;
}

void Room::requestStruct()
{
    throw logic_error{"Error!"};
}

