#ifndef master_H
#define master_H

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <QReadWriteLock>
#include "../getTime.h"
#include "../room/room.h"

class Master {
public:
    Master();
    ~Master();
    
    // Комната
    class Room* createRoom(std::string);
    void removeRoom(std::string);
    Room* getRoom(std::string);
    Room* getTop();
    class User* createUser(std::string); // Users (внтури дерева типо листок)
    void removeUser(std::string);
    void updateStructForAll(); // Обновление информации о пользователях в комнате для всех
    void printVector(); // вывод вектора тех кто в комнате
protected:
    bool userOrNot(Room* inRoom);
    unsigned int getPosOfRoom(std::string);
    std::vector<Room*> rooms;
    Room* topRoom;
    QReadWriteLock roomLock;
};

#endif
