#include "master.h"

using namespace std;


bool Master::userOrNot(Room* inRoom)
{
    User* userTemp = dynamic_cast<User*>(inRoom);
    if (userTemp == nullptr)
        return false;
    else
        return true; 
}



Master::Master()
{
    topRoom = new Room("Share chat",this);
    rooms.push_back(topRoom);
}


Master::~Master()
{
    removeRoom("root");
    topRoom = nullptr;
}


unsigned int Master::getPosOfRoom(string name)
{
    roomLock.lockForRead();
    unsigned int p = this->rooms.size();
    for( unsigned int i = 0 ; i < p ; i++)
    {
        if(this->rooms.at(i)->getName() == name)
        {
            roomLock.unlock();
            return i;
        }
    }
    roomLock.unlock();
    throw logic_error("No such user in Rooms");
    return 0;
}


Room* Master::createRoom(string name)
{
    try
    {
        getRoom(name);
    }
    catch(...)
    {
        Room* temp = new Room(name,this);
        roomLock.lockForWrite();
        rooms.push_back(temp);
        roomLock.unlock(); 
        return temp;
    }
    throw logic_error("Trying to create room, but name is taken ");
}


void Master::removeRoom(string name)
{
    unsigned int pos = getPosOfRoom(name);
    roomLock.lockForWrite();
    delete rooms.at(pos);
    rooms.erase(rooms.begin() + pos);
    roomLock.unlock();
}


void Master::removeUser(string name)
{
    removeRoom(name);
}


// ---------------------------------------
// создание пользователя и обновление дерева
User* Master::createUser(string name)
{
    try
    {
        getRoom(name);
    }
    catch (...)
    {
        User* temp = new User(name,this);
        temp->chooseRoom(topRoom);

        roomLock.lockForWrite();
        rooms.push_back(temp);
        roomLock.unlock();

        // Обновление дерева для все пользователей
        roomLock.lockForRead();
        for (unsigned int i = 0; i < rooms.size(); i++)
        {
                    if ( rooms.at(i)->getName() != name and userOrNot(rooms.at(i)) )
                    {
                        rooms.at(i)->requestStruct();
                    }
        }
        roomLock.unlock();
        return temp;
    }
    throw logic_error{"Already user by that name"};
}



Room* Master::getTop(){
    return topRoom;
}

Room* Master::getRoom(string name)
{
    roomLock.lockForRead();
    for( unsigned int i = 0 ; i < rooms.size() ; i++)
    {
        if(rooms.at(i)->getName() == name)
        {
            roomLock.unlock();
            return rooms.at(i);
        }
    }
    roomLock.unlock();
    throw logic_error("Trying to find room that does not exist");
}

void Master::printVector()
{
    roomLock.lockForRead();
    for( unsigned int i = 0 ; i < rooms.size() ; i++)
    {
        cout << rooms.at(i)->getName() << endl;
    }
    roomLock.unlock();
}



void Master::updateStructForAll() {
    roomLock.lockForRead();
    for (unsigned int i = 0; i < rooms.size(); i++)
    {
        if ( userOrNot(rooms.at(i)) ) {
                rooms.at(i)->requestStruct();
            }
    }
    roomLock.unlock();
}




