#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    FILE* input = fopen("aoc_04_input.txt", "r");
    char line[1000];
    int numfullycontained = 0, numOverlapping = 0;

    if (input == NULL) {
        printf("Error. File could not be opened\n");
        return -1;
    }

    while (fgets(line, sizeof(line), input) != NULL) {
        long s1, e1, s2, e2;
        char *remaining;
        remaining = line;

        // strtol wasn't playing well with the comma and I didn't want to troubleshoot it
        // easiest solution was replacing the comma with a space lol
        for (size_t i = 0; line[i] != 0; i++)
        {
            if (line[i] == ',') {
                line[i] = ' ';
                break;
            }
        }
        
        s1 = abs(strtol(remaining, &remaining, 10));
        e1 = abs(strtol(remaining, &remaining, 10));
        s2 = abs(strtol(remaining, &remaining, 10));
        e2 = abs(strtol(remaining, &remaining, 10));

        printf("S1: %-4ld E1: %-4ld      S2: %4ld E2: %4ld", s1, e1, s2, e2);
        if ((s1 <= s2 && e1 >= e2) || (s1 >= s2 && e1 <= e2)) {
            numfullycontained++;
            printf(" Fully contained");
        }

        if ((s1 >= s2 && s1 <= e2) || (s2 >= s1 && s2 <= e1)) {
            numOverlapping++;
            printf(" overlapping");
        }

        printf("\n");
    }

    printf("Num Fully Contained: %i\n", numfullycontained);
    printf("Num overlapping: %i\n", numOverlapping );

    return 0;
}