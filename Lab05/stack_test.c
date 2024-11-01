// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>

// Course library.
#include "BOARD.h"

// User libraries.
#include "stack.h"


int main()
{
    BOARD_Init();

    printf("\n###### Beginning CRUZID's stack test harness: ####\n\n");

    //printf("Does StackInit() set the currentItemIndex appropriately?\n");

    struct Stack stack = {};

    struct Stack stack_2 = {};

    struct Stack full_stack = {};

    struct Stack uninit_stack = {};

    struct Stack not_empty = {};

    double value;

    StackInit(&stack);

    StackInit(&stack_2);


    if (stack.currentItemIndex == -1) {

        printf("\nStackInit() Passed!\n");

    } else {

        printf("failed");
    }

  StackInit(&full_stack);

  for(int i = 0; i < STACK_SIZE; i++){

StackPush(&full_stack,i);

  }

  if(StackPush(&full_stack,4) == -1){


 printf("\nStackPush() w/ Full Stack Passed!\n");

  }

if(StackPush(&uninit_stack,4) == -1){


 printf("\nStackPush() w/ Unitialized Stack Passed!\n");

}

if(StackPush(&stack,4) == TRUE){


 printf("\nStackPush() Passed!\n");

}

if(StackIsFull(&full_stack)){

printf("\nStackIsFull() Passed!\n");

}

if(StackIsFull(&uninit_stack) == FALSE){

  printf("\nStackIsFull() w/ Uninitialized Stack Passed!\n");
}

StackInit(&not_empty);

StackPush(&not_empty,5);

if(StackIsFull(&not_empty) == FALSE){

  printf("\nStackIsFull() w/ Non-Empty Stack Passed!\n");
}

if(StackIsEmpty(&stack_2)){

  printf("\nStackIsEmpty() Passed!\n");
}

if(StackIsEmpty(&not_empty) == FALSE){

  printf("\nStackIsEmpty() w/ Non-Empty Stack Passed!\n");
}

if(StackIsEmpty(&uninit_stack) == FALSE){

  printf("\nStackIsEmpty() w/ Uninitialized Stack Passed!\n");
}

if(StackGetSize(&full_stack) == 20){

 printf("\nStackGetSize() Passed!\n");

}

if(StackGetSize(&uninit_stack) == SIZE_ERROR){

 printf("\nStackGetSize() w/ Uninitialized Stack Passed!\n");

}

StackPop(&full_stack, &value);


if(value == 19){

printf("\nStackPop() Passed!\n");

}

if(StackPop(&uninit_stack,&value) == STANDARD_ERROR){

printf("\nStackPop() w/ Empty Stack Passed!\n");

}

if(StackPop(&uninit_stack, &value) == STANDARD_ERROR){

printf("\nStackPop() w/ Uninitialized Stack Passed!\n");

}













    BOARD_End();
    while (1);
    return 0;
}


