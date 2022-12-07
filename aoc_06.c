#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define MARKER_LENGTH 14

bool IsValid(char*, int);

int main(void) {
    FILE* input = fopen("aoc_06_input.txt", "r");
    char data[4096];

    int index = 0;

    if (input == NULL) {
        printf("File can't be opened");
        return -1;
    }

    while (fgets(data, sizeof(data), input) != NULL) {
        for (int i = 3; i < sizeof(data); i++)
        {
            if (isalpha(data[i]) == 0)
            {
                break;
            }

            if (IsValid(data, i)) {
                index = i +1;
                printf("Index: %i\n", index);

                fclose(input);
                return 0;
            }
        }
        
    } 

    fclose(input);
    return 0;
}


bool IsValid(char *marker, int index) {
    char validMarker[MARKER_LENGTH];
    for (int i = 0; i < MARKER_LENGTH; i++) {
        for (int j = 0; j < MARKER_LENGTH; j++) {
            if (i == j) continue;

            if (marker[index-i] == marker[index-j])
            {
                return false;
            }
        }
    }

    return true;
}
