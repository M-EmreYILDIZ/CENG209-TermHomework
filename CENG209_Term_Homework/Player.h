//Mehmet Emre YILDIZ 22050111065
#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "Room.h"

typedef struct
{
    bool isAlive;
    
    char name[16];
    
    int health;
    int attackDamage;
    int attackDamageMultiplier;
    int inventoryCount;
    int x;
    int y;
    
    Room *currentRoom;
}Player;

#endif