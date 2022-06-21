// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
//#include "BOARD.h"



// User libraries
#include "rpn.h"
#include "stack.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60

int main() {
    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;

    printf("Welcome to trkmille'S RPN calculator.  Compiled on %s %s\n", __DATE__, __TIME__);
    while (1) {
        printf("Enter floats and + - / * in RPN format:\n");
        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);
        if (rpn_sentence[strlen(rpn_sentence) - 1] != '\n') {
            while (getchar() != '\n'); //flush the input buffer if there's leftover.
            printf("Too many characters entered; Max is 60\n");
            continue;
        }
		ProcessBackspaces(rpn_sentence);
        int error = RPN_Evaluate(rpn_sentence, &result);
        if (error) {
            switch (error) {
                case RPN_ERROR_STACK_OVERFLOW:
                    printf("Not enough room on stack\n");
                    break; 
                case RPN_ERROR_STACK_UNDERFLOW:
                    printf("Not enough operands in stack\n");
                    break;
                case RPN_ERROR_INVALID_TOKEN:
                    printf("There was an invalid input\n");
                    break;
                case RPN_ERROR_DIVIDE_BY_ZERO:
                    printf("There was a divide by 0 error\n");
                    break;
                case RPN_ERROR_TOO_FEW_ITEMS_REMAIN: //This error never comes up, but I don't see any reason to not have it in the switch anyway
                    printf("Not enough operands before operator \n");
                    break;
                case RPN_ERROR_TOO_MANY_ITEMS_REMAIN:
                    printf("Too many items remain\n");
                    break;
            }
        } else {
            printf("result: %lf\n", result);
        }




    }

    while (1);
}
