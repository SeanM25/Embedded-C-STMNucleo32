#include "stack.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void StackInit(struct Stack *stack){

stack->currentItemIndex = -1;

stack->initialized = TRUE;

}


int StackIsFull(const struct Stack *stack){

if(stack->initialized == FALSE){

    return FALSE;

}else if(stack->currentItemIndex != STACK_SIZE - 1){

    return FALSE;
}

return stack->currentItemIndex == STACK_SIZE - 1;

}


int StackPush(struct Stack *stack, double value)
{
    if(stack->currentItemIndex == STACK_SIZE - 1){

        return STANDARD_ERROR;
    }

    else if(stack->initialized == FALSE){

     return STANDARD_ERROR;

    }

stack->stackItems[++stack->currentItemIndex] = value;

return SUCCESS;

}

int StackIsEmpty(const struct Stack *stack){

if(stack->initialized == FALSE){

    return FALSE;
    
} else if(stack->currentItemIndex != -1){

return FALSE;

}

return TRUE;

}

int StackGetSize(const struct Stack *stack){

if(stack->initialized == FALSE){

    return SIZE_ERROR;

}

return stack->currentItemIndex + 1;

}

int StackPop(struct Stack *stack, double *value){

if(stack->initialized == FALSE){

    return STANDARD_ERROR;

} else if (stack->currentItemIndex == -1){

return STANDARD_ERROR;

}

*value = (stack->stackItems[stack->currentItemIndex--]);

return SUCCESS;

    
}

