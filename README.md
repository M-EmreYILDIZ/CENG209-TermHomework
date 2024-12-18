Commands:

look    : Looks around at the surrounding area.
moveDirection    : Moves according to the given direction. (There are four directions. Right, Up, Left and Down.)
                                                           (moveRight , moveUp , moveLeft , moveDown)
attack    : Attacks enemy if present in the room.
inventory    : Lists the current items within inventory.
pickup    : Picks up an item if there is one present in the current room.

I used structs and typdef to define the "classes" for this assignment.
I implemented many methods to change the values within these structs.
I included standart libraries such as <stdbool.h> <stdio.h> and <string.h> to make it easier for me to code and to make it more readable.
I utilized helper methods to make things seem less crowded, to make it more readable.

The game takes place in a dungeon and the rooms are positioned on the x and y axis respectively.
As the player moves these values change and get updated.

Each room has 4 boolean values to indicate whether or not they have a neighbour in a specific direction and also x and y values to place them
on the analytical plane.

The goal of the game is to collect the two halves of the Medallion and finish the game.
