//Mehmet Emre YILDIZ 22050111065
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Player.h"
#include "Room.h"
#include "Creature.h"
#include "Item.h"

int progression = 0;

Item steelSword = {"Steel Sword", "+25 Damage"};
Item whetstone = {"Whetstone", "+15 Damage"};
Item beltOfYmir = {"Belt of Ymir", "Doubles Damage"};
Item leftMedallion = {"Left Half of Medallion", "+1 Progression"};
Item rightMedallion = {"Right Half of Medallion", "+1 Progression"};

Creature quarterMaster = {true, "Quartermaster", 100, 20};
Creature executioner = {true, "Executioner", 275, 35};
Creature jeweler = {true, "Jeweler", 125, 35};
Creature student = {true, "Student", 175, 80};

Room derelictShrine = {true, true, true, true, 0, 0, "Derelict Shrine", false, NULL, &steelSword};
Room rCorr = {true, false, true, false, 1, 0, "Right Corridor", true, &quarterMaster};
Room uCorr = {false, true, false, true, 0, 1, "Up Corridor", true, &executioner};
Room lCorr = {true, false, true, false, -1, 0, "Left Corridor", true, &jeweler};
Room dCorr = {false, true, false, true, 0, -1, "Down Corridor", true, &student};
Room armory = {false, false, true, false, 2, 0, "Armory", false, NULL, &whetstone};
Room desecratedAltar = {false, false, false, true, 0, 2, "Desecrated Altar", false, NULL, &leftMedallion};
Room treasureRoom = {true, false, false, false, -2, 0, "Treasure Room", false, NULL, &beltOfYmir};
Room oldMansRest = {false, true, false, false, 0, -2, "Old Man's Rest", false, NULL, &rightMedallion};

Item *inventory[5];
Player playerChar = {true, "Icebreaker", 100, 10, 1, 0, 0, 0, &derelictShrine};

void updateRoom(Player *player) {
    if (player == NULL) {
        printf("Warning! Player not found!\n");
        return;
    }

    if (player->x == 0 && player->y == 0) {
        player->currentRoom = &derelictShrine;
    } else if (player->x == 1 && player->y == 0) {
        player->currentRoom = &rCorr;
    } else if (player->x == 2 && player->y == 0) {
        player->currentRoom = &armory;
    } else if (player->x == 0 && player->y == 1) {
        player->currentRoom = &uCorr;
    } else if (player->x == -1 && player->y == 0) {
        player->currentRoom = &lCorr;
    } else if (player->x == -2 && player->y == 0) {
        player->currentRoom = &treasureRoom;
    } else if (player->x == 0 && player->y == -1) {
        player->currentRoom = &dCorr;
    } else if (player->x == 0 && player->y == -2) {
        player->currentRoom = &oldMansRest;
    } else if (player->x == 0 && player->y == 2) {
        player->currentRoom = &desecratedAltar;
    } else {
        printf("No room found at coordinates (%d, %d)!\n", player->x, player->y);
        player->currentRoom = NULL;
    }

    if (player->currentRoom != NULL) {
        printf("You are now in %s.\n", player->currentRoom->name);
    }
}

void move(Player *player, char direction[]) {
    if (player == NULL) {
        printf("Warning! Player not found!\n");
        return;
    }

    printf("Moving %s from room: %s\n", direction, player->currentRoom->name);

    if (strncmp(direction, "right", 5) == 0) {
        if (player->currentRoom->hasRightNeighbour) {
            player->x += 1;
        } else {
            printf("No room to the right!\n");
        }
    } else if (strncmp(direction, "up", 2) == 0) {
        if (player->currentRoom->hasUpNeighbour) {
            player->y += 1;
        } else {
            printf("No room above!\n");
        }
    } else if (strncmp(direction, "left", 4) == 0) {
        if (player->currentRoom->hasLeftNeighbour) {
            player->x -= 1;
        } else {
            printf("No room to the left!\n");
        }
    } else if (strncmp(direction, "down", 4) == 0) {
        if (player->currentRoom->hasDownNeighbour) {
            player->y -= 1;
        } else {
            printf("No room below!\n");
        }
    } else {
        printf("Invalid direction: %s\n", direction);
        return;
    }

    updateRoom(player);

}


void pickupItem(Player *player){
    if((player->currentRoom)->loot != NULL){
        
        if(strncmp(((player->currentRoom)->loot)->name, "Steel Sword", 11) == 0){
            
            player->attackDamage +=25;
            printf("You have picked up a steel sword.\n");
        
        }else if(strncmp(((player->currentRoom)->loot)->name, "Whetstone", 9) == 0){
            
            player->attackDamage +=15;
            printf("You have picked up a whetstone.\n");
        
        }else if(strncmp(((player->currentRoom)->loot)->name, "Belt of Ymir", 12) == 0){
            
            player->attackDamageMultiplier += 1;
            printf("You have picked up the Belt of Ymir.\n");
        
        }else if(strncmp(((player->currentRoom)->loot)->name, "Left Half of Medallion", 22) == 0){
            
            progression += 1;
            printf("You have picked up the left half of the Medallion.\n");
        
        }else if(strncmp(((player->currentRoom)->loot)->name, "Right Half of Medallion", 23) == 0){
            
            progression += 1;
            printf("You have picked up the right half of the Medallion.\n");
        }

        inventory[player->inventoryCount] = (player->currentRoom)->loot;
        player->inventoryCount += 1;
        (player->currentRoom)->loot = NULL;

    }else{
        printf("No items in the room!\n");
    }
}

void stats(Player *player){
    printf("%s    HP:%d    Damage:%d\n",player->name,player->health,(player->attackDamage) * (player->attackDamageMultiplier));
    printf("%s    HP:%d    Damage:%d\n",((player->currentRoom)->enemy)->name, ((player->currentRoom)->enemy)->health, ((player->currentRoom)->enemy)->attackDamage);
}

void getAttacked(Player *player){
    
    player->health -= ((player->currentRoom)->enemy)->attackDamage;
    printf("You have taken %d damage.\n", ((player->currentRoom)->enemy)->attackDamage);
    stats(player);

    if(player->health <= 0){
        player->isAlive = false;
        if(player->isAlive == false){
            printf("You have perished! GAME OVER!!\n");
            exit(0);
        }
    }

}

void attack(Player *player){
    if((player->currentRoom)->hasCreature){
        ((player->currentRoom)->enemy)->health -= (player->attackDamage) * (player->attackDamageMultiplier);
        
        printf("You have dealt %d damage.\n", (player->attackDamage) * (player->attackDamageMultiplier));
        
        if(((player->currentRoom)->enemy)->health <= 0){
            
            ((player->currentRoom)->enemy)->isAlive = false;
            (player->currentRoom)->enemy = NULL;
            (player->currentRoom)->hasCreature = false;

            printf("You have slain the enemy!\n");
            printf("You quickly tend to your wounds and go forward.\n");
            player->health = 100;
        
        }else{
            getAttacked(player);
        }
    }else{
        printf("No enemy within this room!\n");
    }
}

void viewInventory(){
    for(int i = 0; i < 5; i++){
        if(inventory[i] == NULL){
            continue;
        }else{
            printf("%d. %s    %s\n", i+1 , inventory[i]->name, inventory[i]->effect);
        }
    }
}

void look(Player *player){
    
    if((player->currentRoom)->hasCreature){
        printf("There is an enemy. Tread carefully.");
    }else{
        printf("Seems safe. You can relax.");
    }
    
    if((player->currentRoom)->loot != NULL){
        printf(" There is an item on the ground. Seems usable.");
    }else{
        printf(" Nothing of use here.");
    }
    
    if(player->currentRoom == &derelictShrine){
        printf(" A shrine takes place in the center of the room. It has fallen into disrepair.\n");
    }else if(player->currentRoom == &rCorr){
        printf(" You are in the right corridor. The air is damp and reeks of mold.\n");
    }else if(player->currentRoom == &uCorr){
        printf(" You are in the up corridor. The air smells like rotten blood and death.\n");
    }else if(player->currentRoom == &lCorr){
        printf(" You are in the left corridor. A glitter of light from the treasure room catches your eye.\n");
    }else if(player->currentRoom == &dCorr){
        printf(" You are in the down corridor. The air smells like old books.\n");
    }else if(player->currentRoom == &armory){
        printf(" Mostly useless weaponry is scattered across the room.\n");
    }else if(player->currentRoom == &desecratedAltar){
        printf(" Blood and death dwells in this room. Accursed ground... leave while you can.\n");
    }else if(player->currentRoom == &treasureRoom){
        printf(" The room is occupied by chests filled to the brim with gold coins. You have no use for them.\n");
    }else if(player->currentRoom == &oldMansRest){
        printf(" The mummified corpse of a man sits in a chair in the center of the room. He looks like a scholar.\n");
    }
}

void command(char order[]){
    
    if(strncmp(order, "moveRight", 9) == 0){
        move(&playerChar, "right");
    }else if(strncmp(order, "moveUp", 6) == 0){
        move(&playerChar, "up");
    }else if(strncmp(order, "moveLeft", 8) == 0){
        move(&playerChar, "left");
    }else if(strncmp(order, "moveDown", 8) == 0){
        move(&playerChar, "down");
    }else if(strncmp(order, "pickup", 6) == 0){
        pickupItem(&playerChar);
    }else if(strncmp(order, "attack", 6) == 0){
        attack(&playerChar);
    }else if(strncmp(order, "look", 4) == 0){
        look(&playerChar);
    }else if(strncmp(order, "inventory", 9) == 0){
        viewInventory();
    }
}

int main(){
    char line[16];
    printf("As you wake up, you feel the cold stone floor on your cheek. You get up and see the steel sword on the floor. You should take it.\n");
    while(progression < 2){
        scanf("%s" , &line);
        command(line);
    }
    printf("\nYou take the other half of the medallion and remember. You were Icebreaker.\n");
    printf("The Tyrant King of the frigid lands of Vili and Sarkosa.\n");
    printf("These were your men. Your betrayers. Those who trapped you here.\n");
    printf("With them gone you can return to your reign of terror.\n\n");
    printf("Congratulations!!! You have finished the game!!!");
    
    return 0;
}