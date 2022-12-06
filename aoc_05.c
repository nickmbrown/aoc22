#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <regex.h>

#include "stack.c"

#define STACKS 9

void LoadStacks(FILE*);

struct stack *stack[STACKS];
regex_t regex;
int reti;

int main (void) {
    char line[1000];
    int rowIndex = 0, colIndex = 0;

    // initialize stacks
    for (size_t i = 0; i < STACKS; i++)
    {
        stack[i] = newStack(100);
    }


    FILE* input = fopen("aoc_05_input.txt", "r");
    if(input == NULL) {
        printf("Couldn't open file");
        return -1;
    }

    LoadStacks(input);

    while (fgets(line, sizeof(line), input) != NULL) {
        int numToMove, stack1, stack2;
        char *remaining = line;

        if (line[0] == 'm')
        {
            if (3 == sscanf(line, 
                            "%*[^0123456789]%d%*[^0123456789]%d%*[^0123456789]%d",
                            &numToMove,
                            &stack1,
                            &stack2))
            {
                // printf("NumToMove: %i Stack1: %i Stack2: %i\n", numToMove, stack1, stack2);
            
                // Move crates: Part 1
                // for (int i = 0; i < numToMove; i++)  {
                //     char crate = peek(stack[stack1-1]);
                //     pop(stack[stack1-1]);
                //     push(stack[stack2-1], crate);
                // }

                // Move crates: Part 2
                char crates[numToMove];
                for (int i = 0; i < numToMove; i++)  {
                    crates[i] = peek(stack[stack1-1]);
                    pop(stack[stack1-1]);
                }

                
                for (int i = numToMove-1; i >= 0; i--) {
                    push(stack[stack2-1], crates[i]);
                }
            }

        }

    }

    // Print top of each stack
    for (int i = 0; i < STACKS; i++)
    {
        // Part 1: QMBMJDFTD
        // Part 2: NBTVTJNFJ
        printf("%c", peek(stack[i]));
    }

    printf("\n");

    return 0;
}

void LoadStacks(FILE *input) {
    char line[1000];
    while (fgets(line, sizeof(line), input) != NULL) {

        int colIndex = 1, stackIndex = 0;

        while(colIndex < STACKS*5 && stackIndex < STACKS)
        {
            if (line[1] == '1') {
                return;
            }

            if (line[colIndex] != ' ') {
                insertToBottom(stack[stackIndex], line[colIndex]);

            }
            colIndex += 4;
            stackIndex++;
        }

        printf("\n");

    }

}