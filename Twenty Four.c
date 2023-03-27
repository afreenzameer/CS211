#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

/*-------------------------------------------
Program 1: Game 24, lets user play the game 24 by 3 different operators, either +,-,* or /. Can be played in easy mode using 10 different combinations of numbers or hard mode using 3188 different combinations of numbers. 
Course: CS 211, Spring 2023, UIC
System: Replit
Author: Afreen Zameer
------------------------------------------- */

//does the math for the allSolutions function in doubles. Takes in the first number, the operator, and the second number. Returns solution of the 3 parameters. 
double op(double x, char operator, double y)
{
    double solution;

    if (operator== '+')
    {

        solution = x + y;
    }
    else if (operator== '-')
    {

        solution = x - y;
    }
    else if (operator== '*')
    {

        solution = x * y;
    }
    else if (operator== '/')
    {

        solution = x / y;
    }

    return solution;
}

//4 nested for loops which iterate through numbers 1-9 and 3 nested for loops which iterate through operators +,-,*, and /. Takes in whether debug mode is on or not and the array of all 3188 combinations. Prints solutions if debug mode is true and if solutions are equal to 24. 
void allSolutions(int array2[3188][4], int debugMode)
{

    int counter = 1;
    char operators[4] = {'+', '-', '*', '/'};
    for (double a = 1; a < 10; a++)
    {
        for (double b = 1; b < 10; b++)
        {
            for (double c = 1; c < 10; c++)
            {
                for (double d = 1; d < 10; d++)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        double ab = op(a, operators[i], b);
                        for (int j = 0; j < 4; j++)
                        {
                            double abc = op(ab, operators[j], c);
                            for (int k = 0; k < 4; k++)
                            {
                                double abcd = op(abc, operators[k], d);
                                if (fabs(abcd - 24.0) < 0.00000001)
                                {
                                    if (debugMode == 1)
                                    {
                                        printf("%d. %d%c%d%c%d%c%d\n", counter,
                                               (int)a, operators[i], (int)b, operators[j], (int)c, operators[k], (int)d);
                                    }
                                    array2[counter - 1][0] = a;
                                    array2[counter - 1][1] = b;
                                    array2[counter - 1][2] = c;
                                    array2[counter - 1][3] = d;
                                    counter++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//checks if easy mode is set to true or false, if set to true it takes a random array from the 10 arrays given. If set to false it takes a random array from one of the 3188 possible solutions to the game 24. Takes in whether it is set to easy mode or hard mode, both arrays of the different possible solutions, and ints a, b, c, and d which are used to perform math in main.  
void easyModeCheck(int easyMode, int array1[10][4], int array2[][4], int *a, int *b, int *c, int *d)
{

    if (easyMode == 1)
    {
        int num = rand() % 10;
        *a = array1[num][0];
        *b = array1[num][1];
        *c = array1[num][2];
        *d = array1[num][3];
    }
    else
    {
        int num = rand() % 3188;
        *a = array2[num][0];
        *b = array2[num][1];
        *c = array2[num][2];
        *d = array2[num][3];
    }
}

int main(int argc, char *argv[])
{
    //2D array of the 10 possible sets of 4 numbers included in easy mode
    int array1[10][4] = {{3, 9, 4, 1}, {8, 5, 8, 1}, {6, 1, 5, 1}, {2, 8, 7, 8}, {5, 2, 9, 2}, {2, 6, 8, 4}, {5, 5, 4, 3}, {6, 6, 2, 6}, {8, 4, 2, 6}, {6, 2, 8, 1}};

    //uses srand once to give consistent random numbers, sets debug to false and easymode to true. 
    srand(1);
    int debugMode = 0;
    int easyMode = 1;
    int a, b, c, d;
    int sol, sol1, sol2, sol3;

  //welcome statement
    printf("Welcome to the game of TwentyFour.\n");
    printf("Use each of the four numbers shown below exactly once,\ncombining them somehow with the basic mathematical operators (+,-,*,/)\nto yield the value twenty-four.\n \n");

  //takes in command line arguements for easymode and debugmode
    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-' && argv[i][1] == 'e')
        {
            easyMode = atoi(argv[i + 1]);
        }
        if (argv[i][0] == '-' && argv[i][1] == 'd')
        {
            debugMode = atoi(argv[i + 1]);
        }
    }
        
  int array2[3188][4];
        
  allSolutions(array2, debugMode);
  
  char command[2];
  char operators[100];
  
    while (1)
    {
        easyModeCheck(easyMode, array1, array2, &a, &b, &c, &d);
        printf("The numbers to use are: %d, %d, %d, %d.\n", a, b, c, d);
        printf("Enter the three operators to be used, in order (+,-,*, or /): ");
        scanf("%s", operators);

        //checks if the number of operators is correct
        if (strlen(operators) != 3)
        {
            printf("Error! The number of operators is incorrect. Please try again.\n\n");
            continue;
        }
      
        //checks if the type of operators is correct
        int w = 0;

        for (int i = 0; i < strlen(operators); i++)
        {
            if (operators[i] != '+' && operators[i] != '-' && operators[i] != '*' && operators[i] != '/')
            {
                w = 1;
            }
        }

        if (w == 1)
        {
            printf("Error! Invalid operator entered. Please try again.\n");
            continue;
        }

        //math in ints for each of the equations and a statement printing each one out 
        int sol = 0;

        if (operators[0] == '+')
        {

            sol = a + b;
        }
        else if (operators[0] == '-')
        {

            sol = a - b;
        }
        else if (operators[0] == '*')
        {

            sol = a * b;
        }
        else if (operators[0] == '/')
        {

            sol = a / b;
        }

        printf("%d %c %d = %d.\n", a, operators[0], b, sol);
        int sol2 = sol;

        if (operators[1] == '+')
        {

            sol2 = sol + c;
        }
        else if (operators[1] == '-')
        {

            sol2 = sol - c;
        }
        else if (operators[1] == '*')
        {

            sol2 = sol * c;
        }
        else if (operators[1] == '/')
        {

            sol2 = sol / c;
        }

        printf("%d %c %d = %d.\n", sol, operators[1], c, sol2);

        int sol3 = sol2;

        if (operators[2] == '+')
        {

            sol3 = sol2 + d;
        }
        else if (operators[2] == '-')
        {

            sol3 = sol2 - d;
        }
        else if (operators[2] == '*')
        {

            sol3 = sol2 * d;
        }
        else if (operators[2] == '/')
        {

            sol3 = sol2 / d;
        }

        //end statement telling user if they win or lose
        printf("%d %c %d = %d.\n", sol2, operators[2], d, sol3);

        if (sol3 == (double)24)
        {
            printf("Well done! You are a math genius. \n");
        }
        else
        {
            printf("Sorry. Your solution did not evaluate to 24. \n");
        }

        //exit statement
        printf("Would you like to play again? Enter N for no and any other character for yes.\n");
        scanf("%s", command);
        if (command[0] == 'N')
        {
            printf("Thanks for playing!");
            exit(0);
        }
    }

    return 0;
}
