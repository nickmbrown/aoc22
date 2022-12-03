#include <stdio.h>
#include <string.h>

char GetCommonItem(char[], int);
char GetCommonItem3(char[], char[], char[], int);
int GetStringLength(char[], int);
int GetItemPriority(char);

int main(void) {
    FILE* input = fopen("aoc_03_input.txt", "r");
    char line[1000], line1[1000], line2[1000], line3[1000];
    int prioritySum = 0, prioritySum3 = 0, index = 0;

    if (input == NULL) 
    {
        printf("Error. File could not be opened\n");
        return -1;
    }

    while (fgets(line, sizeof(line), input) != NULL) {
        index++;
        if(index == 1) {
            strcpy(line1, line);
        } else if (index == 2) {
            strcpy(line2, line);
        } else {
            strcpy(line3, line);
            char commonItem3 = GetCommonItem3(line1, line2, line3, sizeof(line));
            int itemPriority3 = GetItemPriority(commonItem3);
            prioritySum3 += itemPriority3;
            printf("ItemPriority3: %i PrioritySum3: %i\n", itemPriority3, prioritySum3);
            index = 0;
        }


        char commonItem = GetCommonItem(line, sizeof(line));
        int itemPriority = GetItemPriority(commonItem);
        prioritySum += itemPriority;
        
    }

    printf("Priority Sum: %i\n", prioritySum);
    printf("Priority Sum 3: %i\n", prioritySum3);

    fclose(input);
    return 0;
}

char GetCommonItem(char line[], int size) {
    int length = GetStringLength(line, size);

    if (length != -1) {
        int half = length/2;

        for (size_t i = 0; i < half; i++)
        {
            for (size_t j = 0; j < half; j++)
            {
                if (line[i] == line[j+half]) {
                    return line[i];
                }
            }
            
        }
    } else {
        printf("Couldn't read string length");
    }
    
    return '\0';
}

char GetCommonItem3(char line1[], char line2[], char line3[], int size) {
    for (size_t i = 0; i < size; i++)
    {
        if(line1[i] == '\n' || line1[i] == '\0') {
            break;
        }
        for (size_t j = 0; j < size; j++)
        {
            if (line2[j] == '\n' || line2[j] == '\0') {
                break;
            }
            for (size_t k = 0; k < size; k++)
            {
                if (line3[k] == '\n' || line3[k] == '\0') {
                    break;
                }
                if (line1[i] == line2[j] && line2[j] == line3[k]) {
                    return line1[i];
                }
            }
            
        }
    }

    printf("\n");
    return '\0';
}

int GetItemPriority(char item) {
    char prioritymap[52] = {'a','b','c','d','e','f','g','h','i','j','k','l',
    'm','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E',
    'F','G','H','I','J','K','L','M','N','O','P','Q','R', 'S','T','U','V','W','X','Y','Z' };

    for (size_t i = 0; i < sizeof(prioritymap); i++)
    {
        if (item == prioritymap[i]) {
            return i+1;
        }
    }

    return -1;
    
}

int GetStringLength(char string[], int size) {
    int length = 0;
    for(int i = 0; i < size; i++) {
        if (string[i] == '\n' || string[i] == '\0') {
            return length;
        }
        else {
            length++;
        }
    }

    return -1;
}