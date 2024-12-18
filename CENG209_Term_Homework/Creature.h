//Mehmet Emre YILDIZ 22050111065
#ifndef CREATURE_H
#define CREATURE_H

#include <stdbool.h>

typedef struct{
    
    bool isAlive;
    
    char name[16];
    
    int health;
    int attackDamage;
}Creature;


#endif