#include<stdio.h>
#include<stdlib.h>

void ReplaceLowestValueInArrayInArray(int array[], int arraySize, int newValue)
{
    int lowestIndex = 0;
    for (int i = 0; i < arraySize; i++)
    {
        // printf("Value at index %i: %i\n", i, array[i]);
        // printf("Lowest Value: %i\n", array[lowestIndex]);

        if(array[i] < array[lowestIndex])
        {
            lowestIndex = i;
        }
    }

    // printf("Replacing [%i] with [%i]\n\n", array[lowestIndex], newValue);
    array[lowestIndex] = newValue;
    
}

void PrintHighestCalorieCount(FILE *input)
{
    int highestCal = 0, total = 0, lowest = 0;
    int highestCals[3] = {0, 0, 0};
    char line[1000];


    int counter = 0;
    while (fgets(line, sizeof(line), input) != NULL)
    {
        if(line[0] != '\n')
        {
            total += atoi(line);
        }
        else
        {
            if(total > highestCal)
            {
                highestCal = total;
            }

            for(int i = 0; i < 3; i++)
            {
                if(total > highestCals[i])
                {
                    // printf("Total: %i\n" , total);
                    ReplaceLowestValueInArray(highestCals, 3, total);
                    break;
                }
            }

            total = 0;
        }

        counter++;
    }
    
    // This is the total calorie count for the elf carrying the most calories
    printf("Highest 1: %i\n", highestCal); //69281

    for (int i = 1; i < 3; i++)
    {
        highestCal += highestCals[i];
        printf("Highest %i: %i\n", i+1, highestCals[i]);
    }
    
    // This is the total calorie count for the top 3 elves
    printf("Sum of 3 Highest: %i\n", highestCal); // 201524 = 69281 + 67653 + 64590
}

int main(void)
{
    FILE *input = fopen("aoc_01_input.txt", "r");
    if(input == NULL) 
    {
        printf("Error. File could not be opened\n");
        exit(-1);
    }

    PrintHighestCalorieCount(input);

    fclose(input);
    exit(0);
}