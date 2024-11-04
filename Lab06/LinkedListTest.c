#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

// LinkedListNew() Tests

char *ships_of_ww2[]  = {"Bismarck", "Prinz Eugen", "Enterprise", "Yamato"};

char *Red_Fleet_Pac[] = {"Varyag", "Admiral Kuznetsov","Red October","Sovershennyy"};

char *N[] = {NULL};

ListItem* create_LL_test_1 = LinkedListNew(ships_of_ww2[0]);

if(create_LL_test_1->data == ships_of_ww2[0]){

//printf("Yay!\n");

}


ListItem* item = LinkedListNew(ships_of_ww2[2]);

char* add_data[] ={"Hornet"};

ListItem* new_insertion = LinkedListCreateBefore(item,add_data[0]);


//printf("%s %s\n", new_insertion->data, new_insertion->nextItem->data);


ListItem* item_2 = LinkedListNew(ships_of_ww2[2]);

ListItem* item_1 = LinkedListCreateBefore(item_2,add_data[0]); // Hornet <-> Enterprise

char* data_btwn[] = {"PT-109"};

ListItem* item_3 = LinkedListCreateBefore(item_2,data_btwn[0]); // Hornet <-> PT-109 <-> Enterprise


//printf("%s %s %s\n", item_3->previousItem->data, item_3->data, item_3->nextItem->data);


//

ListItem* ship_1 = LinkedListNew(Red_Fleet_Pac[0]); // Varyag

ListItem* ship_2 = LinkedListCreateAfter(ship_1,Red_Fleet_Pac[3]); // Varyag <-> Sovershennyy

//printf("%s %s\n", ship_2->previousItem->data, ship_1->nextItem->data);

char* new_ship[] = {"Chelyabinsk"};

char* new_ship_2[] = {"Peter the Great"};

ListItem* ship_btwn_12 = LinkedListCreateAfter(ship_1, new_ship[0]);  // Varyag <-> Chelyabinsk <-> Sovershennyy

ListItem* forth_ship = LinkedListCreateAfter(ship_btwn_12, new_ship_2[0]); // Varyag <-> Chelyabinsk <-> Peter the Great <-> Sovershennyy


printf("%s, %s, %s, %s\n", ship_btwn_12->previousItem->data, forth_ship->previousItem->data, forth_ship->data, forth_ship->nextItem->data);



















}