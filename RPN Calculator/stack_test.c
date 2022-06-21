// **** Include libraries here ****

// User libraries
#include "stack.h"
//#include "DEF.h"
int main() {
    printf("\n###### Beginning trkmille's stack test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
    //test StackInit:

    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    struct Stack stack = {};
    StackInit(&stack);
    if (stack.currentItemIndex == -1) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    //test StackPush:
    int PushTest = 0; //Number of tests that passed
    int PushTestsTot = 0; //Total number of tests run
    StackPush(&stack, 8);
    if (stack.currentItemIndex == 0 && stack.stackItems[stack.currentItemIndex] == 8) {
        PushTest++; //1st time stack is changed; make sure it's working right
    }
    PushTestsTot++;
    StackPush(&stack, 10);
    StackPush(&stack, 20.1);
    if (stack.currentItemIndex == 2 && stack.stackItems[stack.currentItemIndex] == 20.1) {
        PushTest++; //Push a few times and make sure it's still working
    }
    PushTestsTot++;
    //test StackPop:
    double test;
    int PopTest = 0; //Number of tests passed
    int PopTestsTot = 0; //Total number of tests run
    StackPop(&stack, &test);
    if (test == 20.1 && stack.currentItemIndex == 1 && stack.stackItems[stack.currentItemIndex] == 10) {
        PopTest++;
    }
	PopTestsTot++;
	int FullTest = 0; //number of tests passed
    int FullTestsTot = 0; //Total number of tests run
	if (!StackIsFull(&stack)){
		FullTest++; //make sure it returns FALSE when not full
	}
	FullTestsTot++;
    
    StackPop(&stack, &test);
    StackPop(&stack, &test);
    int error = StackPop(&stack, &test); //test StackPop on an empty stack
    if (error == STANDARD_ERROR) {
        PopTest++;
    }
    PopTestsTot++;
    //test StackIsEmpty:
    int EmptyTest = 0; //Tests passed
    int EmptyTestsTot = 0; //Total Tests run
    if (StackIsEmpty(&stack)) {
        EmptyTest++;
    }
    EmptyTestsTot++;
    //test StackIsFull:
    for (int i = 0; i < STACK_SIZE; i++) {
        StackPush(&stack, i); //Just fill up the stack with 1-19
    }
    if (StackIsEmpty(&stack) != 1) {
        EmptyTest++; //Does it work right for non-empty stacks?
    }
    EmptyTestsTot++;


    int error2 = StackPush(&stack, 20);
    if (error2 == STANDARD_ERROR) {
        PushTest++; //Might as well test that this works, since this is where I have a full stack
    }
    PushTestsTot++;
    if (StackIsFull(&stack)) {
        FullTest++;
    }
    FullTestsTot++;

    //test StackGetSize:
    int SizeTest = 0; // number of tests passed
    int SizeTestsTot = 0; //Total number of tests run
    if (StackGetSize(&stack) == 20) {
        SizeTest++;
    }
    SizeTestsTot++;


    printf("(%d/%d) PASSED StackPush()\n", PushTest, PushTestsTot);
    printf("(%d/%d) PASSED StackPop()\n", PopTest, PopTestsTot);
    printf("(%d/%d) PASSED StackIsEmpty()\n", EmptyTest, EmptyTestsTot);
    printf("(%d/%d) PASSED StackIsFull()\n", FullTest, FullTestsTot);
    printf("(%d/%d) PASSED StackGetSize()\n", SizeTest, SizeTestsTot);

    return 0;
}


