/* 
 * File:   Player.c
 * Author: Tristen Miller
 *
 * Created on May 16, 2022, 8:02 AM
 */
#include <stdio.h>
#include "Player.h"
#include "UNIXBOARD.h"

static uint8_t Inventory[INVENTORY_SIZE];
static uint8_t currentInv = 0;

int AddToInventory(uint8_t item)
{
    if (currentInv < INVENTORY_SIZE) {
        Inventory[currentInv] = item;
        currentInv++;
        return SUCCESS;
    } else {
		 //I feel like this shouldn't happen, as there's only 3 items and 4
        //spaces to put items
        return STANDARD_ERROR;
    }
}

int FindInInventory(uint8_t item)
{
    for (int i = 0; i <= INVENTORY_SIZE; i++) {
        if (Inventory[i] == item) {
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}
