/**
 * Add your description here.
 *
 * @file
 * @author
 *
 * @date
 */
// Standard libraries.
#include <stdio.h>
#include <math.h>
#include <ctype.h>

// User libraries.
#include "BOARD.h"


// **** Declare function prototypes here. ****
double Add(double operand1, double operand2);
double Subtract(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double Divide(double operand1, double operand2);
double Average(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double CelsiusToFarenheit(double operand);
double Tangent(double operand);
double AbsoluteValue(double operand);
double Round(double operand);

void CalculatorRun(void)
{

    char user_OP;

    double oper_1;

    double oper_2;

    double result;

    
    printf(
        "\n\nWelcome to Sean's calculator program! Compiled at %s %s\n",
        __DATE__,
        __TIME__
    );

while(1){

   
   printf("\nUser, Please Enter a Mathematical Operation you Desire to Perform (*, /, +, -, m, a, c, f, t, q, r) : ");

   scanf("%c", &user_OP);

   while(getchar() != '\n');

   if (user_OP == 'q'){ 

    break;
   }else if (user_OP == '*' || user_OP == '/' || user_OP == '+' || user_OP == '-' || user_OP == 'm'){ // Binary Operations: Add, Sub, Mul, Div, Avg


printf("\nEnter Your 1st Operand: ");

while(scanf("%lf", &oper_1) != 1){

printf("\nNaN Try Again\n");

while(getchar() != '\n');

}

printf("\nEnter Your 2nd Operand: ");

while(scanf("%lf", &oper_2) != 1){

printf("\nNaN Try Again\n");

while(getchar() != '\n');

}

    if (user_OP == '*'){

        result = Multiply(oper_1, oper_2);

        printf("\nResult of Multiply (%lf * %lf) = %lf\n", oper_1, oper_2, result);
        
    } else if (user_OP == '/'){

        result = Divide(oper_1, oper_2);

        if(result == HUGE_VAL){

           printf("\nError: You Cannot Divide By Zero!\n");

        }else{

        printf("\nResult of Divide (%lf / %lf) = %lf\n", oper_1, oper_2, result);

    }

    } else if (user_OP == '+'){

        result = Add(oper_1, oper_2);

        printf("\nResult of Add (%lf + %lf) = %lf\n", oper_1, oper_2, result);

    } else if (user_OP == '-'){

        result = Subtract(oper_1, oper_2);

        printf("\nResult of Subtract (%lf - %lf) = %lf\n", oper_1, oper_2, result);

    } else if (user_OP == 'm'){

        result = Average(oper_1, oper_2);

        printf("\nAverage of (%lf & %lf) = %lf\n", oper_1, oper_2, result);
    }

} else if (user_OP == 'a' || user_OP == 'c' || user_OP == 'f' || user_OP == 't' || user_OP == 'r'){ // Unary Functions: Abs, Cel, Far, Tan, Round

printf("Enter Your Operand: ");

while(scanf("%lf", &oper_1) != 1){

printf("\nNaN Try Again: ");

while(getchar() != '\n');

}

if(user_OP == 'a'){

result = AbsoluteValue(oper_1);

printf("\n|%lf| is = %lf \n", oper_1, result);

}else if(user_OP == 'c'){

result = FahrenheitToCelsius(oper_1);

printf("(%lf deg F --> C): %lf", oper_1, result);

}else if(user_OP == 'f'){

result = CelsiusToFarenheit(oper_1);

printf("(%lf deg C --> F): %lf", oper_1, result);

}else if(user_OP == 't'){

result = Tangent(oper_1);

printf("tan (%lf) = %lf", oper_1, result);

}else if(user_OP == 'r'){

result = Round(oper_1);

printf("Round (%lf)",result);


}

}else{

printf("Invalid Input Please Try Again");

}
}
   
}

/*******************************************************************************
 * Define the Add function here.
 ******************************************************************************/
double Add (double operand1, double operand2)
{

    double add_RES = operand1 + operand2;

    return add_RES;
}

/*******************************************************************************
 * Define the Subtract function here.
 ******************************************************************************/
double Subtract (double operand1, double operand2)
{
   double sub_RES = operand1 - operand2;

    return sub_RES;
}

/*******************************************************************************
 * Define the Multiply function here.
 ******************************************************************************/
double Multiply (double operand1, double operand2)
{
    double mulRES = operand1 * operand2;

    return mulRES;
}

/*******************************************************************************
 * Define the Divide function here.
 ******************************************************************************/
double Divide(double operand1, double operand2)
{

    double div_RES = (operand1 / operand2);

    return div_RES;
	
}

/*******************************************************************************
 * Define the Absolute Value function here.
 ******************************************************************************/
double AbsoluteValue(double operand){

if (operand < 0){

return operand * -1;

}

return operand;

}

/*******************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ******************************************************************************/
double FahrenheitToCelsius(double operand){

double res_F2C = (5.0 / 9.0) * (operand - 32);

return res_F2C;

}

/*******************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ******************************************************************************/
double CelsiusToFarenheit(double operand){

double res_C2F = (operand * (9.0 / 5.0)) + 32.0;

return res_C2F;

}

/*******************************************************************************
 * Define the Average function here.
 ******************************************************************************/
double Average(double operand1, double operand2){

double avg_RES = Add(operand1, operand2) / 2.0;

return avg_RES;

}

/*******************************************************************************
 * Define the Tangent function that takes input in degrees.
 ******************************************************************************/
double Tangent(double operand)
{
   // double deg2rad = (M_PI / 180.0) * operand;

   double deg2rad = Multiply((M_PI / 180.0), operand);

    double res_TAN = tan(deg2rad);

    return res_TAN;

}

/*******************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST CORRECTLY utilize
 * this function.
 ******************************************************************************/
double Round(double operand)
{

    double frac_part = AbsoluteValue(operand - (int) operand);

    double amount_added = 1 - frac_part;

    double round_RES;

    if(frac_part >= 0.5 && operand <= 0){

       round_RES = operand - amount_added;

       return round_RES; 

    }else if(frac_part >= 0.5 && operand >= 0){

      round_RES = operand + amount_added;
      
      return round_RES;

    }else{
         
         return (int) operand;
    }

}

