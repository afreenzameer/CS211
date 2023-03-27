#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*-------------------------------------------
Program 2: Game Weaver, lets the user play the game Weaver by picking their own two words or substituting either (or both) word with "r" to pick a random word from the dictionary. The user is only allowed to play using words of a specified length, chosen by the user. There are several checks put in place to ensure the  length of the word is correct, the word exists in the dictionary, and that the word is at most one character different from the previous word. If the user successfully reaches the goal word, a message is printed congratulating them on their success along with the number of tries it took to reach the goal word. The user is then asked if they would like to exit the game, play again with the same number of letters, or play again with a different number of letters. The game continues until the user exits, upon which an exit message is printed and the program ends.
Course: CS 211, Spring 2023, UIC
System: Replit
Author: Afreen Zameer
------------------------------------------- */
int main(void)
{

    char word1[81];
    char initialWord[81];
    char goal[81];
    char word2[81];
    srand(1);
    // welcome statement explaining the rules of the game
    printf("Weaver is a game where you try to find a way to get from the "
           "starting word to the ending word.\n");
    printf("You can change only one letter at a time, and each word along the "
           "way must be a valid word.\n");
    printf("Enjoy!\n\n");
    while (1)
    {
        int num;

        printf("How many letters do you want to have in the words? ");
        scanf("%d", &num);
        // opens and reads in file
        char filename[] = "words.txt";
        FILE *filePtr =
            fopen(filename, "r");
        if (filePtr == NULL)
        {
            printf("Error: could not open %s for reading\n", filename);
            exit(-1);
        }
        // increments counter for the number of words which are the same character length as the userinput number
        int value = 10;
        char inputString[81];
        int totalWords = 0;
        while (fscanf(filePtr, "%s", inputString) != EOF)
        {
            if (strlen(inputString) == num)
            {
                totalWords++;
                continue;
            }
        }
        // dynamically allocates space in an array named wordArray
        char **wordArray;
        char **newArray;
        wordArray = malloc(sizeof(char *) * value);
        for (int i = 0; i < value; i++)
        {
            wordArray[i] = (char *)malloc(sizeof(char) * (num + 1));
        }
        filePtr = fopen(filename, "r"); // "r" means we open the file for reading
        // edge case for if the file does not open
        if (filePtr == NULL)
        {
            printf("Error: could not open %s for reading\n", filename);
            exit(-1);
        }
        char inputString1[81];
        int totalWords1 = 0;
        int count = 0;
        while (fscanf(filePtr, "%s", inputString1) != EOF)
        {
            if (strlen(inputString1) == num)
            {
                totalWords1++;
                // grows the array by 100 each time the count is equal or greater to value, so each time when reading the file the number of words exceeds the size of the array.
                if (count >= value)
                {

                    newArray = malloc(sizeof(char *) * (value + 100));
                    for (int i = 0; i < value + 100; i++)
                    {
                        newArray[i] = (char *)malloc(sizeof(char) * (num + 1));
                    }
                    for (int k = 0; k < value; k++)
                    {
                        strcpy(newArray[k], wordArray[k]);
                    }
                    for (int z = 0; z < value; z++)
                    {
                        free(wordArray[z]);
                    }
                    free(wordArray);
                    wordArray = newArray;
                    value = value + 100;
                }
                strcpy(wordArray[count], inputString1);
                count++;
            }
        }
        fclose(filePtr); // closes file once done with reading

        printf("Number of %d-letter words found: %d.\n", num, totalWords1);

        while (1)
        {
            int p = 0;
            int v = 0;
            int z = 0;
            int result = 1;
            printf("Enter starting and ending words, or 'r' for either for a random word: ");
            scanf("%s %s", initialWord, goal);
            // stores the users first word to initial for later print statement
            strcpy(word1, initialWord);
            // if the user types in r, pick a random number from the number of the length of the array. Then using that number it will pick an index from the array, effectively picking a word at random from the array.
            if (strcmp(word1, "r") == 0)
            {
                int num = rand() % totalWords1;
                strcpy(word1, wordArray[num]);
                strcpy(initialWord, wordArray[num]);
            }
            if (strcmp(goal, "r") == 0)
            {
                int num = rand() % totalWords1;
                strcpy(goal, wordArray[num]);
            }
            // checks if the length of the words the user input were equal to the specificed number. If it does not, the loop begins again
            if (strlen(word1) != num)
            {
                printf("Your word, '%s', is not a %d-letter word. Try again.\n", word1,
                       num);
                continue;
            }
            if (strlen(goal) != num)
            {
                printf("Your word, '%s', is not a %d-letter word. Try again.\n", goal,
                       num);
                continue;
            }
            // checks if the word the user input exists in the array or not, if it does not it prints that it is not a valid dictionary word.
            for (int g = 0; g < totalWords1; g++)
            {
                if (strcmp(word1, wordArray[g]) == 0)
                {
                    p = 0;
                    break;
                }
                else
                {
                    p = 1;
                }
            }
            for (int n = 0; n < totalWords1; n++)
            {
                if (strcmp(goal, wordArray[n]) == 0)
                {
                    v = 0;
                    break;
                }
                else
                {
                    v = 1;
                }
            }
            // if statement created so the message prints only once, rather than multiple times in the for loop
            if (p == 1)
            {
                printf("Your word, '%s', is not a valid dictionary word. Try again.\n",
                       word1);
                continue;
            }
            if (v == 1)
            {
                printf("Your word, '%s', is not a valid dictionary word. Try again.\n",
                       goal);
                continue;
            }
            // if all the neccesary conditions are met, the game will start through exiting the while loop
            if (strlen(word1) == num && strlen(goal) == num && p == 0 && v == 0)
            {
                break;
            }
        }
        printf("Your starting word is: %s.\n", word1);
        printf("Your ending word is: %s.\n", goal);
        printf("On each move enter a word of the same length that is at most 1 "
               "character different and is also in the dictionary.\n");
        printf("You may also type in 'q' to quit guessing.\n");
        int counter = 1;
        // while loop continues until user input word is equal to the goal word. Inside this while loop it also checks for the same conditions as in the previous loop, for correct length of word, the validity of the word, as well as  being one character different.
        while (strcmp(word1, goal) != 0)
        {
            int p1 = 0;
            int v1 = 0;
            int z = 0;
            int result = 1;

            printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ",
                   counter, word1, goal);
            scanf("%s", word2);
            if (strcmp(word2, "q") == 0)
            {
                break;
            }
            if (strlen(word2) != num)
            {
                printf("Your word, '%s', is not a %d-letter word. Try again.\n", word2,
                       num);
                continue;
            }

            for (int g = 0; g < totalWords1; g++)
            {
                if (strcmp(word2, wordArray[g]) == 0)
                {
                    p1 = 0;
                    break;
                }
                else
                {
                    p1 = 1;
                }
            }
            if (p1 == 1)
            {
                printf("Your word, '%s', is not a valid dictionary word. Try again.\n",
                       word2);

                continue;
            }
            // loops through each character of word1 and word2 and increments each time a character is different. If the diff is  anything other  than 1, the error message appears.
            int diff = 0;
            for (int i = 0; i < num; i++)
            {
                if (word1[i] != word2[i])
                {
                    diff++;
                }
            }
            if (diff != 1)
            {
                printf("Your word, '%s', is not exactly 1 character different. Try "
                       "again.\n",
                       word2);
                continue;
            }

            strcpy(word1, word2);
            counter++;
        }
        // the while loops ends and if word1 is equal to the goal word the congratulations statement prints.
        if (strcmp(word1, goal) == 0)
        {
            printf("Congratulations! You changed '%s' into '%s' in %d moves.",
                   initialWord, goal, counter - 1);
        }

        // switch menu is printed, with three different options. 3 exits the  program and  clears the memory of wordArray. 2 allows the user to play the game using the same while loop from the begining of the program, when the user inputs a number for the letters they want to play with. option 1 allows the user to play with the same number of letters.
        int number = 0;
        char menuOption = ' ';
        while (menuOption != '3')
        {
            printf("\nEnter: \t1 to play again,\n");
            printf("\t2 to change the number of letters in the words and then play "
                   "again, or\n");
            printf("\t3 to exit the program.\n");
            printf("Your choice --> ");

            scanf(" %c", &menuOption);

            switch (menuOption)
            {
            case '3':
            {
                // frees the memory allocated for wordArray
                printf("\nThanks for playing!\nExiting...");
                if (wordArray != NULL)
                {
                    for (int z = 0; z < value; z++)
                    {
                        free(wordArray[z]);
                    }
                }
                free(wordArray);
                return 0;
                break;
            }
            case '1':
            {
                // case one, takes care of when the user wants to play again with the same number of letters in their words
                while (1)
                {
                    int p = 0;
                    int v = 0;
                    int z = 0;
                    int result = 1;
                    printf("Enter starting and ending words, or 'r' for either for a "
                           "random word: ");
                    scanf("%s %s", initialWord, goal);
                    strcpy(word1, initialWord);
                    // selects a word at random from the array of words
                    if (strcmp(word1, "r") == 0)
                    {
                        int num = rand() % totalWords1;
                        strcpy(word1, wordArray[num]);
                        strcpy(initialWord, wordArray[num]);
                    }
                    if (strcmp(goal, "r") == 0)
                    {
                        int num = rand() % totalWords1;
                        strcpy(goal, wordArray[num]);
                    }
                    // checks to see if the length of the word is correct. If it is not, it prints an error message and starts the loop again.
                    if (strlen(word1) != num)
                    {
                        printf("Your word, '%s', is not a %d-letter word. Try again.\n",
                               word1, num);
                        continue;
                    }
                    if (strlen(goal) != num)
                    {
                        printf("Your word, '%s', is not a %d-letter word. Try again.\n",
                               goal, num);
                        continue;
                    }
                    // check to make sure the word is in the dictionary
                    for (int g = 0; g < totalWords1; g++)
                    {
                        if (strcmp(word1, wordArray[g]) == 0)
                        {
                            p = 0;
                            break;
                        }
                        else
                        {
                            p = 1;
                        }
                    }
                    for (int n = 0; n < totalWords1; n++)
                    {
                        if (strcmp(goal, wordArray[n]) == 0)
                        {
                            v = 0;
                            break;
                        }
                        else
                        {
                            v = 1;
                        }
                    }
                    if (p == 1)
                    {
                        printf(
                            "Your word, '%s', is not a valid dictionary word. Try again.\n",
                            word1);
                        printf("%s\n", wordArray[6920]);
                        continue;
                    }
                    if (v == 1)
                    {
                        printf(
                            "Your word, '%s', is not a valid dictionary word. Try again.\n",
                            goal);
                        continue;
                    }
                    // if all conditions pass, the user can play the game
                    if (strlen(word1) == num && strlen(goal) == num && p == 0 && v == 0)
                    {
                        break;
                    }
                }
                printf("Your starting word is: %s.\n", word1);
                printf("Your ending word is: %s.\n", goal);
                printf("On each move enter a word of the same length that is at most 1 "
                       "character different and is also in the dictionary.\n");
                printf("You may also type in 'q' to quit guessing.\n");
                int counter = 1;
                while (strcmp(word1, goal) != 0)
                {
                    int p1 = 0;
                    int v1 = 0;
                    int z = 0;
                    int result = 1;

                    printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ",
                           counter, word1, goal);
                    scanf("%s", word2);
                    // if the user types q the switch menu appears again
                    if (strcmp(word2, "q") == 0)
                    {
                        break;
                    }
                    if (strlen(word2) != num)
                    {
                        printf("Your word, '%s', is not a %d-letter word. Try again.\n",
                               word2, num);
                        continue;
                    }
                    // checks to make sure the word the user in using during the game is in the dictionary
                    for (int g = 0; g < totalWords1; g++)
                    {
                        if (strcmp(word2, wordArray[g]) == 0)
                        {
                            p1 = 0;
                            break;
                        }
                        else
                        {
                            p1 = 1;
                        }
                    }
                    if (p1 == 1)
                    {
                        printf(
                            "Your word, '%s', is not a valid dictionary word. Try again.\n",
                            word2);
                        continue;
                    }
                    // checks to make sure the word the user inputs is exactly one character different using a counter which increments when a character is different from the previous word
                    int diff = 0;
                    for (int i = 0; i < num; i++)
                    {
                        if (word1[i] != word2[i])
                        {
                            diff++;
                        }
                    }
                    if (diff != 1)
                    {
                        printf("Your word, '%s', is not exactly 1 character different. Try "
                               "again.\n",
                               word2);
                        continue;
                    }

                    strcpy(word1, word2);
                    counter++;
                }
                // if the word matches the goal word, the loop breaks and a congrats statement is printed
                if (strcmp(word1, goal) == 0)
                {
                    printf("Congratulations! You changed '%s' into '%s' in %d moves.",
                           initialWord, goal, counter - 1);
                }

                break;
            }
            case '2':
                // case two handles when the user wants to change the number of letters they want to play with.
                // frees the memory  allocated for wordArray so that the array can allocate memory for the new number of letters array.
                if (wordArray != NULL)
                {

                    for (int z = 0; z < value; z++)
                    {
                        free(wordArray[z]);
                    }
                }
                free(wordArray);

                printf("How many letters do you want to have in the words? ");
                scanf("%d", &num);

                char filename[] = "words.txt";
                FILE *filePtr = fopen(filename, "r"); // "r" means we open the file for reading

                if (filePtr == NULL)
                {
                    printf("Error: could not open %s for reading\n", filename);
                    exit(-1);
                }

                char inputString[81];
                totalWords = 0;
                while (fscanf(filePtr, "%s", inputString) != EOF)
                {
                    if (strlen(inputString) == num)
                    {
                        totalWords++;
                        continue;
                    }
                }
                value = 10;
                wordArray = malloc(sizeof(char *) * value);
                for (int i = 0; i < value; i++)
                {
                    wordArray[i] = (char *)malloc(sizeof(char) * (num + 1));
                }
                filePtr = fopen(filename, "r"); // "r" means we open the file for reading

                if (filePtr == NULL)
                {
                    printf("Error: could not open %s for reading\n", filename);
                    exit(-1);
                }
                totalWords1 = 0;
                count = 0;
                while (fscanf(filePtr, "%s", inputString1) != EOF)
                {
                    if (strlen(inputString1) == num)
                    {
                        totalWords1++; // increments counter for the number of words which are the same character length as the userinput number

                        if (count >= value)
                        {

                            newArray = malloc(sizeof(char *) * (value + 100));
                            for (int i = 0; i < value + 100; i++)
                            {
                                newArray[i] = (char *)malloc(sizeof(char) * (num + 1));
                            }
                            for (int k = 0; k < value; k++)
                            {
                                strcpy(newArray[k], wordArray[k]);
                            }
                            for (int z = 0; z < value; z++)
                            {
                                free(wordArray[z]);
                            }
                            free(wordArray);
                            wordArray = newArray;
                            newArray = NULL;
                            value = value + 100;
                        }
                        strcpy(wordArray[count], inputString1);
                        count++;
                    }
                }
                // close the file once we are done reading from it
                fclose(filePtr);
                printf("Number of %d-letter words found: %d.\n", num, totalWords1);

                while (1)
                {
                    int p = 0;
                    int v = 0;
                    int z = 0;
                    int result = 1;
                    printf("Enter starting and ending words, or 'r' for either for a "
                           "random word: ");
                    scanf("%s %s", initialWord, goal);
                    strcpy(word1, initialWord);
                    if (strcmp(word1, "r") == 0)
                    {
                        int num = rand() % totalWords1;
                        strcpy(word1, wordArray[num]);
                        strcpy(initialWord, wordArray[num]);
                    }
                    if (strcmp(goal, "r") == 0)
                    {
                        int num = rand() % totalWords1;
                        strcpy(goal, wordArray[num]);
                    }

                    if (strlen(word1) != num)
                    {
                        printf("Your word, '%s', is not a %d-letter word. Try again.\n",
                               word1, num);
                        continue;
                    }
                    if (strlen(goal) != num)
                    {
                        printf("Your word, '%s', is not a %d-letter word. Try again.\n",
                               goal, num);
                        continue;
                    }
                    for (int g = 0; g < totalWords1; g++)
                    {
                        if (strcmp(word1, wordArray[g]) == 0)
                        {
                            p = 0;
                            break;
                        }
                        else
                        {
                            p = 1;
                        }
                    }
                    for (int n = 0; n < totalWords1; n++)
                    {
                        if (strcmp(goal, wordArray[n]) == 0)
                        {
                            v = 0;
                            break;
                        }
                        else
                        {
                            v = 1;
                        }
                    }
                    if (p == 1)
                    {
                        printf(
                            "Your word, '%s', is not a valid dictionary word. Try again.\n",
                            word1);
                        continue;
                    }
                    if (v == 1)
                    {
                        printf(
                            "Your word, '%s', is not a valid dictionary word. Try again.\n",
                            goal);
                        continue;
                    }
                    if (strlen(word1) == num && strlen(goal) == num && p == 0 && v == 0)
                    {
                        break;
                    }
                }
                printf("Your starting word is: %s.\n", word1);
                printf("Your ending word is: %s.\n", goal);
                printf("On each move enter a word of the same length that is at most 1 "
                       "character different and is also in the dictionary.\n");
                printf("You may also type in 'q' to quit guessing.\n");
                int counter1 = 1;
                while (strcmp(word1, goal) != 0)
                {
                    int p1 = 0;
                    int v1 = 0;
                    int z = 0;
                    int result = 1;

                    printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ",
                           counter1, word1, goal);
                    scanf("%s", word2);
                    if (strcmp(word2, "q") == 0)
                    {
                        break;
                    }
                    if (strlen(word2) != num)
                    {
                        printf("Your word, '%s', is not a %d-letter word. Try again.\n",
                               word2, num);
                        continue;
                    }

                    for (int g = 0; g < totalWords1; g++)
                    {

                        if (strcmp(word2, wordArray[g]) == 0)
                        {
                            p1 = 0;
                            break;
                        }
                        else
                        {
                            p1 = 1;
                        }
                    }
                    if (p1 == 1)
                    {
                        printf(
                            "Your word, '%s', is not a valid dictionary word. Try again.\n",
                            word2);
                        continue;
                    }

                    int diff = 0;
                    for (int i = 0; i < num; i++)
                    {
                        if (word1[i] != word2[i])
                        {
                            diff++;
                        }
                    }
                    if (diff != 1)
                    {
                        printf("Your word, '%s', is not exactly 1 character different. Try "
                               "again.\n",
                               word2);
                        continue;
                    }

                    strcpy(word1, word2);
                    counter1++;
                }
                if (strcmp(word1, goal) == 0)
                {
                    printf("Congratulations! You changed '%s' into '%s' in %d moves.", initialWord, goal, counter1 - 1);
                }
                break;
                // end of case 1
            default:
                printf("Invalid menu option.  Retry. \n"); // sanity check, should never reach this option
                continue;
            }
        }
    }

    return 0;
}
