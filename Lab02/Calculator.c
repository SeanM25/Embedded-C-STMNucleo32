/**Lab - 2 ECE 13 Simple Calculator
 *
 * The program implemented here is a Simple Calculator that performs standard arithmetic operations plus Rounding, Finding the Tangent, Average, Absolute Value,
 * and Temperature conversions from Farenheit To Celcius & Celcius to Farenheit. The user selects a desired operation and then enters their desired operand(s)
 * to perform the operation with. This Calculator performs error checking for invalid operational and numeric input and prompts the user to try again.
 * Operators Are Either Binary or Unary depending on the desired operation.
 *
 *
 * @file Calculator.c
 * @author Sean M. Manger (smanger@ucsc.edu)
 *
 * @date 10/11/2024
 *
 *  Note: All code written is my own orignal work.
 */
// Standard libraries.
#include <stdio.h>
#include <math.h>

// User libraries.
#include "BOARD.h"

// **** Function Prototypes for the Simple Calculator. ****
double Add(double operand1, double operand2);      // Adds Two Numbers
double Subtract(double operand1, double operand2); // Subtracts Two Numbers
double Multiply(double operand1, double operand2); // Multiplies Two Numbers
double Divide(double operand1, double operand2);   // Divides Two Numbers & Returns an error if there is division by Zero.
double Average(double operand1, double operand2);  // Finds the Average of Two Numbers
double AbsoluteValue(double operand);              // Finds Aboslute Value of a Number
double FahrenheitToCelsius(double operand);        // Treats input as degrees in F and converts to C
double CelsiusToFarenheit(double operand);         // Treats input as degrees in C and converts to F
double Tangent(double operand);                    // Treats input as angle in degrees and finds the tangent
double Round(double operand);                      // Rounds number to the nearest whole number based on fractional part

void CalculatorRun(void) // Gets User Input Repeatedly & Performs Calculator Logic / Operations
{

    char user_OP; // Gets desired operation from user via STDIN

    double oper_1; // Stores First Operand

    double oper_2; // Stores Second Operand if desired

    double result; // Outputs Result from Function Calls

    printf(
        "\n\nWelcome to Sean's calculator program! Compiled at %s %s\n", // Standard Greeting Prints Once To Avoid User Irritation
        __DATE__,
        __TIME__);

    while (1)
    { // Main Loop which continuously prompts user for input & performs desired calculations

        printf("\nUser, Please Enter a Mathematical Operation you Desire to Perform (*, /, +, -, m, a, c, f, t, q, r): "); // User prompted for desired operation

        scanf(" %c", &user_OP); // Reads user input

        if (user_OP == 'q')
        { // If the user wants to Quit?

            printf("\n"); // Prints \n for better termination visibility

            break; // Exit Program
        }
        else if (user_OP == '*' || user_OP == '/' || user_OP == '+' || user_OP == '-' || user_OP == 'm')
        { // Binary Operations: Add, Sub, Mul, Div, Avg

            printf("\nEnter Your 1st Operand: "); // Prompts User for 1st Operand

            while (scanf("%lf", &oper_1) != 1)
            { // Checks to see if user has entered valid numerical input

                printf("\nNaN Try Again: "); // otherwise prompts them to try again

                while (getchar() != '\n')
                    ; // Clear buffer
            }

            printf("\nEnter Your 2nd Operand: "); // Prompts user for 2nd Operand

            while (scanf("%lf", &oper_2) != 1)
            { // Checks again for valid input

                printf("\nNaN Try Again: "); // Try Again?

                while (getchar() != '\n')
                    ; // Clear Buffer
            }

            if (user_OP == '*')
            { // If operation is multiplication call Multiply()

                result = Multiply(oper_1, oper_2); // Result from * function call

                printf("\nResult of Multiply (%lf * %lf) = %lf\n", oper_1, oper_2, result); // prints result
            }
            else if (user_OP == '/')
            { // If operation is division call Divide()

                result = Divide(oper_1, oper_2); // result from / funtion call

                if (result == HUGE_VAL)
                { // If div by 0 print error

                    printf("\nError: You Cannot Divide By Zero!\n"); // div by 0 Error message
                }
                else
                {

                    printf("\nResult of Divide (%lf / %lf) = %lf\n", oper_1, oper_2, result); // Otherwise print result
                }
            }
            else if (user_OP == '+')
            { // If user desires adition call Add()

                result = Add(oper_1, oper_2); // Result of Add()

                printf("\nResult of Add (%lf + %lf) = %lf\n", oper_1, oper_2, result); // Print Result of Add()
            }
            else if (user_OP == '-')
            { // If user desires subtraction call Subtract()

                result = Subtract(oper_1, oper_2); // Result of Subtract()

                printf("\nResult of Subtract (%lf - %lf) = %lf\n", oper_1, oper_2, result); // Print Result of Subtract()
            }
            else if (user_OP == 'm')
            { // If user desires average call Average()

                result = Average(oper_1, oper_2); // Result of Average()

                printf("\nAverage of (%lf & %lf) = %lf\n", oper_1, oper_2, result); // Print Result of Average()
            }
        }
        else if (user_OP == 'a' || user_OP == 'c' || user_OP == 'f' || user_OP == 't' || user_OP == 'r')
        { // Unary Functions: Abs, Cel, Far, Tan, Round

            printf("\nEnter Your Operand: "); // Promps user for only a single operand since unary

            while (scanf("%lf", &oper_1) != 1)
            { // Checks again for valid numerical input

                printf("\nNaN Try Again: "); // otherwise print error

                while (getchar() != '\n')
                    ; // Clear buffer
            }

            if (user_OP == 'a')
            { // If user desires absolute value call AbsoluteValue()

                result = AbsoluteValue(oper_1); // result of AbsoluteValue()

                printf("\n|%lf| is = %lf \n", oper_1, result); // print result of AbsoluteValue()
            }
            else if (user_OP == 'c')
            { // If user desires Celcius call FarenheitToCelcius()

                result = FahrenheitToCelsius(oper_1); // result of FarenheitToCelcius()

                printf("\n(%lf deg F --> C): %lf\n", oper_1, result); // Print result of FarenheitToCelcius()
            }
            else if (user_OP == 'f')
            { // If user desires Farenheit call CelciusToFarenheit()

                result = CelsiusToFarenheit(oper_1); // result of CelciusToFarenheit()

                printf("\n(%lf deg C --> F): %lf\n", oper_1, result); // print result of CelciusToFarenheit
            }
            else if (user_OP == 't')
            { // If user desires tan call Tangent()

                result = Tangent(oper_1); // result of Tangent()

                printf("\ntan (%lf) = %lf\n", oper_1, result); // Print result of Tangent()
            }
            else if (user_OP == 'r')
            { // If user desires rounding call Round()

                result = Round(oper_1); // Result of Round()

                printf("\nRound (%lf) = %lf\n", oper_1, result); // Print result of Round()
            }
        }
        else
        {

            printf("Invalid Input Please Try Again"); // If desired user operation is neither a unary, binary, or quit, the input is invalid print error message & try again
        }
    }
}

/*******************************************************************************
 * Defined the Add function here.
 ******************************************************************************/
double Add(double operand1, double operand2) // Note: See Prototypes for Further Definition
{

    double add_RES = operand1 + operand2; // Performs Addition

    return add_RES; // returns result of addition
}

/*******************************************************************************
 * Defined the Subtract function here.
 ******************************************************************************/
double Subtract(double operand1, double operand2)
{
    double sub_RES = operand1 - operand2; // Performs Subtraction

    return sub_RES; // returns result of subtraction
}

/*******************************************************************************
 * Defined the Multiply function here.
 ******************************************************************************/
double Multiply(double operand1, double operand2)
{
    double mulRES = operand1 * operand2; // performs multiplication

    return mulRES; // returns result of multiplication
}

/*******************************************************************************
 * Defined the Divide function here.
 ******************************************************************************/
double Divide(double operand1, double operand2)
{

    double div_RES = (operand1 / operand2); // performs division

    return div_RES; // returns result of division
}

/*******************************************************************************
 * Defined the Absolute Value function here.
 ******************************************************************************/
double AbsoluteValue(double operand)
{

    if (operand < 0)
    { // If operand is negative swap sign

        return operand * -1; // returns result of addition
    }

    return operand; // otherwise just return the operand if it is positive
}

/*******************************************************************************
 * Defined the Fahrenheit to Celsius function here.
 ******************************************************************************/
double FahrenheitToCelsius(double operand)
{

    double res_F2C = (5.0 / 9.0) * (operand - 32); // Performs conversion of Farenheit to Celcius

    return res_F2C; // returns conversion of Farenheit to Celcius
}

/*******************************************************************************
 * Defined the Celsius to Fahrenheit function here.
 ******************************************************************************/
double CelsiusToFarenheit(double operand)
{

    double res_C2F = (operand * (9.0 / 5.0)) + 32.0; // Performs conversion of Celsius to Farenheit

    return res_C2F; // returns conversion of Celsius to Farenheit
}

/*******************************************************************************
 * Defined the Average function here.
 ******************************************************************************/
double Average(double operand1, double operand2)
{

    double avg_RES = Add(operand1, operand2) / 2.0; // Computes average of two numbers

    return avg_RES; // returns result
}

/*******************************************************************************
 * Defined the Tangent function that takes input in degrees.
 ******************************************************************************/
double Tangent(double operand)
{

    double deg2rad = Multiply((M_PI / 180.0), operand); // converts degrees to radians

    double res_TAN = tan(deg2rad); // computes tan of degrees converted into radians

    return res_TAN; // returns result
}

/*******************************************************************************
 * Defined the Round function here.
 ******************************************************************************/
double Round(double operand)
{

    double frac_part = AbsoluteValue(operand - (int)operand); // Gets fractional part of operand EX: 5.5 --> 0.5

    double amount_added = 1 - frac_part; // Gets Amount needed for rounding EX: 5.5 ---> 0.5 ---> 1 - 0.5 = 0.5 ---> 5.5 + 0.5 =6

    double round_RES; // Stores final rounded result

    if (frac_part >= 0.5 && operand <= 0)
    { // If fractional part is greater than or equal to 0.5 round up. In this case operand is negative so we subtract to round

        round_RES = operand - amount_added; // Do rounding

        return round_RES; // return rounded result
    }
    else if (frac_part >= 0.5 && operand >= 0)
    { // In this case operand is positive so we add to round

        round_RES = operand + amount_added; // Do rounding

        return round_RES; // return rounded result
    }
    else
    {

        return (int)operand; // otherwise round down EX: 5.2 ---> 5.0
    }
}
