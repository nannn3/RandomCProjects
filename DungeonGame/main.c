//Author: Tristen Miller (trkmille@ucsc.edu)

// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CSE013E Support Library
#include "UNIXBOARD.h"



// User libraries
#include "Game.h"

// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****

// **** Declare any function prototypes here ****

int main()
{
    /******************************** Your custom code goes below here ********************************/

    char input;
    char Title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char Desc [GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t passFlag = FALSE;
    if(!GameInit()){
        FATAL_ERROR();
    }
    uint8_t exits;

    while (1) {
        if (passFlag != TRUE) {
            GameGetCurrentRoomTitle(Title);
            GameGetCurrentRoomDescription(Desc);
            exits = GameGetCurrentRoomExits();
            printf("\nRoom Title: %s\n", Title);
            printf("Room Description: %s\n", Desc);
            printf("\nPossible Exits:\n");
            if (exits & GAME_ROOM_EXIT_NORTH_EXISTS) {
                printf("NORTH Exit Exists!\n");
            }
            if (exits & GAME_ROOM_EXIT_EAST_EXISTS) {
                printf("EAST Exit Exists!\n");
            }
            if (exits & GAME_ROOM_EXIT_SOUTH_EXISTS) {
                printf("SOUTH Exit Exists!\n");
            }
            if (exits & GAME_ROOM_EXIT_WEST_EXISTS) {
                printf("WEST Exit Exists!\n");
            }
            printf("\nPick a Direction:\n"
                    "\tn=North\n"
                    "\te=East\n"
                    "\ts=South\n"
                    "\tw=West\n"
                    "\tq=Quit\n");
            passFlag = TRUE;
        }
        printf("\nInput: ");
        input = getchar();
		
            if (getchar() != '\n'){ 
				while (getchar() != '\n');//flush the input buffer if there's leftover.
				continue;
			}

        switch (input) {
        case 'n':case'N':
            //while (getchar() != '\n'); //flush the input buffer if there's leftover.

            if (GameGoNorth()) {
                passFlag = FALSE;
            } else {
                printf("Can't go North\n");
            }
            break;
        case 'e':case'E':	
            //while (getchar() != '\n'); //flush the input buffer if there's leftover.

            if (GameGoEast()) {
                passFlag = FALSE;
            } else {
                printf("Can't go East\n");
            }
            break;
        case 's':case'S':
            //while (getchar() != '\n'); //flush the input buffer if there's leftover.

            if (GameGoSouth()) {
                passFlag = FALSE;
            } else {
                printf("Can't go South\n");
            }
            break;
        case 'w':case 'W':
           // while (getchar() != '\n'); //flush the input buffer if there's leftover.

            if (GameGoWest()) {
                passFlag = FALSE;
            } else {
                printf("Can't go West\n\t");
            }
            break;
        case'q':case 'Q':
            exit(SUCCESS);
        default:
            passFlag = TRUE;
            //while (getchar() != '\n'); //flush the input buffer if there's leftover.
            break;
        }




        /**************************************************************************************************/
    }
}

