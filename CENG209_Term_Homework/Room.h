//Mehmet Emre YILDIZ 22050111065
#ifndef ROOM_H
#define ROOM_H

#include <stdbool.h>
#include "Creature.h"
#include "Item.h"

typedef struct{
    
    bool hasRightNeighbour;
    bool hasUpNeighbour;
    bool hasLeftNeighbour;
    bool hasDownNeighbour;
    
    int x;
    int y;
    
    char name[32];

    bool hasCreature;
    Creature *enemy;
    Item *loot;
}Room;


#endif