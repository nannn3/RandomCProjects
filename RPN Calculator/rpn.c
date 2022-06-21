/* 
 * File:   rpn.c
 * Author: Tristen Miller (trkmille@ucsc->edu)
 *
 * Created on April 18, 2022, 7:52AM
 */
#include<stdio.h>
#include<string.h>

#include "rpn.h"
#include "stack.h"

int RPN_Evaluate(char * rpn_string, double * result) {
    struct Stack stack = {};
    StackInit(&stack);
    char *token;
    double o1;
    double o2;
    int errorTest;
    token = strtok(rpn_string, " ");
    while (token != NULL) {
        double temp = atof(token);
        if (temp == 0 && *token != '0') {
            if (*token == '+') {
                errorTest = StackPop(&stack, &o1);
                if (errorTest == STANDARD_ERROR) {
                    return RPN_ERROR_STACK_UNDERFLOW; // trying to take a number when stack is empty
                }
                errorTest = StackPop(&stack, &o2);
                if (errorTest == STANDARD_ERROR) {
                    return RPN_ERROR_STACK_UNDERFLOW;
                }
                *result = o1 + o2;
                StackPush(&stack, *result);
            } else if (*token == '-') {
                errorTest = StackPop(&stack, &o1);
                if (errorTest == STANDARD_ERROR) {
                    return RPN_ERROR_STACK_UNDERFLOW; 
                }
                errorTest = StackPop(&stack, &o2);
                if (errorTest == STANDARD_ERROR) {
                    return RPN_ERROR_STACK_UNDERFLOW;
                }
                *result = o2 - o1;
                StackPush(&stack, *result);
            } else if (*token == '*') {
                errorTest = StackPop(&stack, &o1);
                if (errorTest == STANDARD_ERROR) {
                    return RPN_ERROR_STACK_UNDERFLOW;
                }
                errorTest = StackPop(&stack, &o2);
                if (errorTest == STANDARD_ERROR) {
                    return RPN_ERROR_STACK_UNDERFLOW;
                }
                *result = o1 * o2;
                StackPush(&stack, *result);
            } else if (*token == '/') {
                errorTest = StackPop(&stack, &o1);
                if (errorTest == STANDARD_ERROR) {
                    return RPN_ERROR_STACK_UNDERFLOW;
                }
                errorTest = StackPop(&stack, &o2);
                if (o1 == 0) {
                    return RPN_ERROR_DIVIDE_BY_ZERO;
                } else if (errorTest == STANDARD_ERROR) {
                    return RPN_ERROR_STACK_UNDERFLOW;
                }
                *result = o2 / o1;
                StackPush(&stack, *result);
            } else {
                return RPN_ERROR_INVALID_TOKEN; //Anything that's not a number or +,-,*,/
            }
        } else {
            errorTest = StackPush(&stack, temp);
            if (errorTest == STANDARD_ERROR) {
                return RPN_ERROR_STACK_OVERFLOW; //this is the only error I can see happening with just pushing
            }

        }

        token = strtok(NULL, " ");
    }
    if (stack.currentItemIndex != 0) {
        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    } else {
        return RPN_NO_ERROR;
    }
}

int ProcessBackspaces(char *rpn_sentence) {

    char *reading;
    char *writing;

    for (reading = writing = rpn_sentence; *reading != '\0'; reading++) {

        if (*reading == '\b') {

            if (writing != rpn_sentence) { //I wish I could say that I came up with this, but I couldn't 
                //figure out how to iterate through a string. 
                //I followed an example on stack overflow
                //(https://stackoverflow.com/questions/21034365/how-to-do-backspace-processing-in-c)
                //I understand how it works, but I feel I should note the orignial code isn't 100% mine

                writing--;
            }
            continue;
        }
        *writing++ = *reading;
    }
    *writing = '\0';
    return RPN_NO_ERROR;
}

//This is how I orignially tried to do it
/* int ProcessBackspaces(char *rpn_sentence){
    char test[strlen(rpn_sentence)]=rpn_sentence
    for(int i =0;i<strlen(rpn_sentence);i++){
        if (test[i]='\b'){
            test[i-1]=test[i+1]
            continue;
        }
    }
    rpn_sentence=test;
}
 */