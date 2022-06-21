/* 
 * File:   stack.c
 * Author: Tristen Miller (trkmille@ucsc->edu)
 *
 * Created on April 18, 2022, 7:52AM
 */
#include "BOARD.h"
#include "stack.h"

//Define StackInit ----------------------------------------------------------

void StackInit(struct Stack *stack) {
    stack->currentItemIndex = -1;
    stack->initialized = TRUE;
}
//end StackInit -------------------------------------------------------------
//Define StackPush ----------------------------------------------------------

int StackPush(struct Stack *stack, double value) {
    if (stack->initialized == FALSE || stack->currentItemIndex == STACK_SIZE - 1) {
        return STANDARD_ERROR;
    } else {
        stack->stackItems[stack-> currentItemIndex + 1 ] = value;
        stack->currentItemIndex++;
        return SUCCESS;
    }
}
//end StackPush -------------------------------------------------------------
//Define StackPop -----------------------------------------------------------

int StackPop(struct Stack *stack, double *value) {
    if (stack->initialized == FALSE || stack->currentItemIndex == -1) {
        return STANDARD_ERROR;
    } else {
        * value = stack->stackItems[stack->currentItemIndex];
        stack->stackItems[stack->currentItemIndex--] = 0; //not sure if I need to set it to zero before going down, but couldn't hurt
        return SUCCESS;
    }
}
//End StackPop ---------------------------------------------------------------
//Define StackIsEmpty --------------------------------------------------------

int StackIsEmpty(const struct Stack *stack) {
    if (stack->initialized != TRUE || stack->currentItemIndex != -1) {
        return FALSE;
    } else {
        return TRUE;
    }
}
//End StackIsEmpty ------------------------------------------------------------
//Define StackIsFull ----------------------------------------------------------

int StackIsFull(const struct Stack *stack) {
    if (stack->initialized != TRUE || stack->currentItemIndex != STACK_SIZE - 1) { //I know the lab manual says STACK_SIZE -1, but I don't see how that's true->
        return FALSE;
    } else {
        return TRUE;
    }
}
//End StackIsFull ------------------------------------------------------------
//Define StackGetSize---------------------------------------------------------

int StackGetSize(const struct Stack *stack) {
    if (stack->initialized != TRUE) {
        return SIZE_ERROR;
    } else {
        return stack->currentItemIndex + 1;
    }
}
//End StackGetSize------------------------------------------------------------