/* player_test.c
 * Author: Tristen Miller
 * Created 6/21/2022 @9:08 AM
 */

#include <stdio.h>
#include "Player.h"
#include "UNIXBOARD.h"

int main(){
    uint8_t playerTests = 0; //number of tests passed
    uint8_t playerTestsTotal = 0; //total number of tests run

    //Make sure add to inventory works
    if(AddToInventory(3)){
        playerTests++;
    }
    playerTestsTotal++;
    AddToInventory(3);
    AddToInventory(5);
    AddToInventory(7);
    if(!AddToInventory(9)){
        playerTests++;
    }
    playerTestsTotal++;
    printf("Passed (%d/%d) tests!\n",playerTests,playerTestsTotal);
    exit(0);
}