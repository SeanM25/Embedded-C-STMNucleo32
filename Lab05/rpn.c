#include "rpn.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include <ctype.h>

int RPN_Evaluate(char *rpn_string, double *result)
{

    char *token = strtok(rpn_string, " ");

    double val;

    struct Stack rpn_stack;

    StackInit(&rpn_stack);

    for (; token != NULL; token = strtok(NULL, " "))
    {

        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {

            StackPush(&rpn_stack, atof(token));
        }
        else
        {

            double b = StackPop(&rpn_stack, &val);

            double a = StackPop(&rpn_stack, &val);

            switch (token[0])
            {
            case '+':
                StackPush(&rpn_stack, a + b);
                break;
            case '-':
                StackPush(&rpn_stack, a - b);
                break;
            case '*':
                StackPush(&rpn_stack, a * b);
                break;
            case '/':
                if (b != 0)
                {
                    StackPush(&rpn_stack, a / b);
                }

            default:
                printf("Error: Unknown operator '%s'\n", token);
            }
        }
    }
    *result = StackPop(&rpn_stack, &val);
    return 0;
}
/* Switch Statement Above Not Working Revisit This Approach?
int length = strlen(rpn_string);

for(int i = 0; i < length; i++){

if(isdigit(rpn_string[i])){

double num = rpn_string[i] - '0';

//printf("\n%f\n",x);

StackPush(&rpn_stack, num);

} else {


double b = StackPop(&rpn_stack);

double a = StackPop(&rpn_stack);
*/

int ProcessBackspaces(char *rpn_sentence)
{

    return 0;
}