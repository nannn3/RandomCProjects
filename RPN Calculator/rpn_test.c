// **** Include libraries here ****

// User libraries
#include "rpn.h"

int main() {
    int error;

    printf("\n###### Beginning trkmille's rpn test harness: ####\n\n");

    char test0[] = "1 1 +";
    double result0;
    double expected0 = 2;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test0);
    error = RPN_Evaluate(test0, &result0);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result0 != expected0) {
        printf("   Failed, expected = %f , result = %f\n", expected0, result0);
    } else {
        printf("   Success!\n");
    }

    char test1[] = "1 4 + 6 4 - * 8 /";
    double result1;
    double expected1 = 1.25;

    printf("Testing RPN_Evaluate with \"%s\"... \n ", test1); //Test from the lab manual, seemed like a pretty good basic one
    error = RPN_Evaluate(test1, &result1);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result1 != expected1) {
        printf("   Failed, expected = %f , result = %f\n", expected1, result1);
    } else {
        printf("   Success!\n");
    }

    char test2[] = "0 -1 + 6 4 - *";
    double result2;
    double expected2 = -2;

    printf("Testing RPN_Evaluate with \"%s\"... \n ", test2); //Testing 0 and negative numbers
    error = RPN_Evaluate(test2, &result2);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result2 != expected2) {
        printf("   Failed, expected = %f , result = %f\n", expected2, result2);
    } else {
        printf("   Success!\n");
    }

    char test3[] = "10 0 /";
    double result3;
    error = RPN_Evaluate(test3, &result3);
    if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
        printf("   Success, caught divide by zero\n"); //Testing to make sure it catches divide by zero errors
    } else {
        printf("Something failed");
    }

    printf("Testing ProcessBackspaces:\n");
    char test_pb1[] = "123\b34";
    ProcessBackspaces(test_pb1);
    printf("result    : %s\n", test_pb1);
    printf("should be : 1234\n");
    while (1);
}


