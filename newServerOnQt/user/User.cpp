#include "../room/room.h"
#include "../serverclass/thread.h"

using namespace std;
//----------------------------------------
// Диструткор
User::~User()
{
    parentRoom->removeRoom(this);
    parentRoom = nullptr;
    masterPointer = nullptr;
}

// ----------------------------------
// Выбор комнаты
void User::chooseRoom(Room* newRoom)
{
    if(this->parentRoom != nullptr)
    {
		parentRoom->removeRoom(this);
	}
    newRoom->addRoom(this);
}


// ----------------------------------
// перессылка сообщений
void User::receiveMessage(Message inMessage)
{
    msgQueueLock.lockForWrite();
    log.push_back(inMessage);
    thread->sendMessage(inMessage);
    msgQueueLock.unlock();
}

// ----------------------------------
// отправка сообщений
void User::sendMessage(Message outMessage)
{
    parentRoom->receiveMessage(outMessage);
    msgQueueLock.lockForWrite();
    log.push_back(outMessage);
    msgQueueLock.unlock();
}

// ----------------------------------
//Инициализация комнаты
void User::initRoom(string name)
{
    parentRoom->addRoom(masterPointer->createRoom(name));
}


// ----------------------------------
void User::setThread(class Thread* inThread)
{
    thread = inThread;
}

// ----------------------------------
void User::requestStruct()
{
    thread->requestStruct();
}

// ----------------------------------

void User::setFilePath()
{

}

// ----------------------------------

void User::readAllFromFile()
{
}

// ----------------------------------

vector<string> User::getStruct()
{
    return parentRoom->getStruct();
}
