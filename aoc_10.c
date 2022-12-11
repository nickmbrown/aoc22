#include <stdio.h>
#include <string.h>

int cycle = 1, xreg = 1;
int signalstrength = 0;
int count = 0;

int spritepos[3];

int startswith(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre));
}

void incrementcycle(int cycles) {
    for(int i=0; i<cycles; i++) {
        if (/*cycle == 20 || */count == 40) {
            signalstrength += cycle * xreg;
            // printf("Cycle: %i xreg: %i Strength: %i\n", cycle, xreg, cycle*xreg);
            count = 0;
            printf("\n");
        }

        if (count == spritepos[0] ||
            count == spritepos[1] ||
            count == spritepos[2] ) {
            printf("#");
        } else {
            printf(".");
        }

        cycle++;
        count++;
    }
}



int main(void) {
    FILE* input = fopen("aoc_10_input.txt", "r");
    char line[20];
    int instruction;

    spritepos[0] = xreg-1;
    spritepos[1] = xreg;
    spritepos[2] = xreg+1;

    if (input == NULL) {
        printf("Can't open file");
        return -1;
    }

    while (fgets(line, sizeof(line), input) != NULL) {



        if (startswith("noop", line) == 0) {
            incrementcycle(1);
            
        } else {
            sscanf(line, "addx %d", &instruction);
            incrementcycle(2);

            xreg += instruction;
            
            spritepos[0] = xreg-1;
            spritepos[1] = xreg;
            spritepos[2] = xreg+1;
        }        
    }

    printf("\n");
    // printf("Signal Strength: %i\n", signalstrength);

    fclose(input);
    return 0;
}