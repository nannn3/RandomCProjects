/* 
 * File:   Game.c
 * Author: Tristen Miller (trkmille@ucsc.edu)
 *
 * Created on May 2, 2022, 8:02 AM
 */
#include <stdio.h>
#include <string.h>

#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"


#define FILE_NAME_SIZE 22 //"RoomFiles/room##.txt" has 20 characters in it. the extra 2 are a buffer
#define DIRECTIONS 4 //We're only dealing with N,E,S,W, so there's only 4 total possible directions
#define FILE_START 3 //The File really starts at the fourth character.
enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

typedef struct {
    char *Title;
    char *Description;
    uint8_t Exits;
    uint8_t ExitsWhere[DIRECTIONS];
} RoomData;

static RoomData roomData;
//HELPER FUNCTIONS:

//This is a helper function to open,read,update the struct, and close the file:

int readAndUpdate(char *fileToOpen)
{
    char Title[GAME_MAX_ROOM_TITLE_LENGTH];
    char Desc[GAME_MAX_ROOM_DESC_LENGTH];
    FILE *fp;
    int c;
    fp = fopen(fileToOpen, "r");
    if (fp == NULL) {
        FATAL_ERROR();
    }

    //GET THE ROOM TITLE VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
    fseek(fp, FILE_START, SEEK_SET); //The length of the title is always the fourth character.
    c = fgetc(fp);
    fgets(Title, c + 1, fp);
    roomData.Title = Title;

    //GET THE ROOM DESCRIPTION VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
    int itemReq = fgetc(fp);
    if (itemReq == 0) { //if there is not an item required
        c = fgetc(fp); //Length of description 1
        fgets(Desc, c, fp);

    } else {//if there's an item required
        int itemNeeded = fgetc(fp); //find out what item it is
        if (FindInInventory(itemNeeded)) {//if we have the item
            c = fgetc(fp); //length of description 1
            fgets(Desc, c + 1, fp);

        } else {//We don't have the item required
            c = fgetc(fp); //Length of description 1
            fseek(fp, c, SEEK_CUR); //Skip the first description 
            c = fgetc(fp); //Item contained
            if (c == 0) {//there's no item to pick up in the first version room (that's being skipped)
                fseek(fp, DIRECTIONS, SEEK_CUR); //Skip the exit options from the 1st version
            } else {//There is an item to pick up in the skipped desc
                fseek(fp, DIRECTIONS + 1, SEEK_CUR); //Skip the item and the exits
            }
            itemReq = fgetc(fp); //See if there's an item to see the 2nd description
            //itemReq for 2nd description should always be 0
            c = fgetc(fp); //Length of 2nd Description
            fgets(Desc, c + 1, fp);
        }

    }

    //GET THE ROOM EXITS VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
    int itemsPresent = fgetc(fp);
    if (itemsPresent == 0) { //If there's no item to pick up
        for (int i = 0; i < DIRECTIONS; i++) {
            roomData.ExitsWhere[i] = fgetc(fp); //Find out where the exits lead
        }
    } else { //If there is an item to pick up
        c = fgetc(fp);
        if(!AddToInventory(c)){
			printf("\nCould not add to Inventory\n");
		}
        for (int i = 0; i < DIRECTIONS; i++) {
            roomData.ExitsWhere[i] = fgetc(fp);
        }
    }

    if (roomData.ExitsWhere[NORTH]) { //If there's a location to the north, then we can go north
        roomData.Exits |= GAME_ROOM_EXIT_NORTH_EXISTS;
    } else if (roomData.Exits & GAME_ROOM_EXIT_NORTH_EXISTS) { //if we can go north, but no 
                                               //location, turn off the option to go north.
        roomData.Exits &= ~GAME_ROOM_EXIT_NORTH_EXISTS;
    }
    if (roomData.ExitsWhere[EAST]) {
        roomData.Exits |= GAME_ROOM_EXIT_EAST_EXISTS;
    } else if (roomData.Exits & GAME_ROOM_EXIT_EAST_EXISTS) {
        roomData.Exits &= ~GAME_ROOM_EXIT_EAST_EXISTS;
    }
    if (roomData.ExitsWhere[SOUTH]) {
        roomData.Exits |= GAME_ROOM_EXIT_SOUTH_EXISTS;
    } else if (roomData.Exits & GAME_ROOM_EXIT_SOUTH_EXISTS) {
        roomData.Exits &= ~GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
    if (roomData.ExitsWhere[WEST]) {
        roomData.Exits |= GAME_ROOM_EXIT_WEST_EXISTS;
    } else if (roomData.Exits & GAME_ROOM_EXIT_WEST_EXISTS) {
        roomData.Exits &= ~GAME_ROOM_EXIT_WEST_EXISTS;
    }

    roomData.Description = Desc;
    roomData.Title = Title;
    fclose(fp);
    return SUCCESS;


}//END readAndUpdate()

//takes the roomNumber and sets string to be a file in the RoomFiles folder

void fileName(int roomNumber, char *string)
{
    sprintf(string, "RoomFiles/room%d.txt", roomNumber);
}//End fileName()

//Define GameInit
int GameInit(void)
{
    roomData.Exits = 0;
    char str[FILE_NAME_SIZE];
    fileName(STARTING_ROOM, str);
    if (readAndUpdate(str)) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }

}//End GameInit()

//Define GameGetCurrentRoomTitle

int GameGetCurrentRoomTitle(char *title)
{
    strcpy(title, roomData.Title);
    //strncat(title, "\0", 1);
    return strlen(roomData.Title);
}//End GameGetCurrentRoomTitle();

//Define GameGetCurrentRoomDescription

int GameGetCurrentRoomDescription(char *desc)
{
    strcpy(desc, roomData.Description);
    //strncat(desc, "\0", 1);
    return strlen(roomData.Description);
}//End GameGetCurrentRoomDescription()

//Define GameGetCurrentRoomExits

uint8_t GameGetCurrentRoomExits(void)
{
    return roomData.Exits;
}//End GameGetCurrnetRoomExits()

//Define GameGoNorth

int GameGoNorth(void)
{
    if (roomData.Exits & GAME_ROOM_EXIT_NORTH_EXISTS) {//If there exists an exit to the north
        char str[FILE_NAME_SIZE];
        fileName(roomData.ExitsWhere[NORTH], str);
        uint8_t temp = roomData.Exits; //I need to clear the Exits before running readAndUpdate,
        //But just in case there's an error, I'd like to keep the info
        roomData.Exits = 0;
        if (readAndUpdate(str)) {
            return SUCCESS;
        } else {
            roomData.Exits = temp;
            return STANDARD_ERROR;
        }
    } else {
        return STANDARD_ERROR;
    }
}//End GameGoNorth()

//Define GameGoEast

int GameGoEast(void)
{
    if (roomData.Exits & GAME_ROOM_EXIT_EAST_EXISTS) {
        char str[FILE_NAME_SIZE];
        fileName(roomData.ExitsWhere[EAST], str);
        uint8_t temp = roomData.Exits;
        roomData.Exits = 0;
        if (readAndUpdate(str)) {
            return SUCCESS;
        } else {
            roomData.Exits = temp;
            return STANDARD_ERROR;
        }
    } else {
        return STANDARD_ERROR;
    }
}//End GameGoEast

//Define GameGoSouth

int GameGoSouth(void)
{
    if (roomData.Exits & GAME_ROOM_EXIT_SOUTH_EXISTS) {
        char str[FILE_NAME_SIZE];
        fileName(roomData.ExitsWhere[SOUTH], str);
        uint8_t temp = roomData.Exits;
        roomData.Exits = 0;
        if (readAndUpdate(str)) {
            return SUCCESS;
        } else {
            roomData.Exits = temp;
            return STANDARD_ERROR;
        }
    } else {
        return STANDARD_ERROR;
    }
}//End GameGoSouth

//Define GameGoWest

int GameGoWest(void)
{
    if (roomData.Exits & GAME_ROOM_EXIT_WEST_EXISTS) {
        char str[FILE_NAME_SIZE];
        fileName(roomData.ExitsWhere[WEST], str);
        uint8_t temp = roomData.Exits;
        roomData.Exits = 0;
        if (readAndUpdate(str)) {
            return SUCCESS;
        } else {
            roomData.Exits = temp;
            return STANDARD_ERROR;
        }
    } else {
        return STANDARD_ERROR;
    }
}//End GameGoWest

