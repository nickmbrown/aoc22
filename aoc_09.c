#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROPE_LENGTH 1

struct vec2 {
    int x, y;
};

struct vec2 dimensions, startingpoint, headpos, tailpos;
struct vec2 rope[ROPE_LENGTH];

void setdimensions(FILE*);
void printgrid(char[dimensions.x][dimensions.y]);
int getnumtailvisits(char[dimensions.x][dimensions.y]);

float distancebetweenpoints(struct vec2 pointA, struct vec2 pointB) {
    return sqrt(((pointB.x - pointA.x) * (pointB.x - pointA.x)) + ((pointB.y - pointA.y) * (pointB.y - pointA.y)));
}

int main(void) {
    FILE* input = fopen("aoc_09_input.txt", "r");

    int horizontal, vertical, value;
    char line[5];
    char dir;
    int index = 0;


    if (input == NULL) {
        printf("Can't open file");
        return -1;
    }

    // setdimensions(input);

    dimensions.x = 6;
    dimensions.y = 5;
    startingpoint.x = 0;
    startingpoint.y = dimensions.y -1;

    for(int i = 0; i < ROPE_LENGTH; i++) {
        rope[ROPE_LENGTH] = startingpoint;
    }


    // dimensions.x = 400;
    // dimensions.y = 1000;
    // startingpoint.x = dimensions.x/2;
    // startingpoint.y = dimensions.y/2;

    headpos = startingpoint;
    tailpos = startingpoint;

    char grid[dimensions.x][dimensions.y];
    char path[dimensions.x][dimensions.y];
    path[tailpos.x][tailpos.y] = '#';

    // printf("Starting Grid:\n");
    // printgrid(grid);

    fseek(input, 0, SEEK_SET);
    while (fgets(line, sizeof(line), input) != NULL) {
        sscanf(line, "%c %d", &dir, &value);

        horizontal = 0;
        vertical = 0;
        
        if (dir == 'R') {
            horizontal = 1;
        } else if (dir == 'L') {
            horizontal = -1;
        } else if (dir == 'U') {
            vertical = -1;
        } else if (dir == 'D') {
            vertical = 1;
        } else {
            continue;
        }
        printf("== %c %i == Index: %i\n", dir, value, index);

        for (int i = 0; i < value; i++) {
            headpos.x += horizontal;
            headpos.y += vertical;

            if (distancebetweenpoints(headpos, rope[0]) > 1.5) {
                for (int j = ROPE_LENGTH; j > 0; j--) {
                    rope[j] = rope[j-1];
                }

                if (horizontal != 0) {
                    rope[0].x += horizontal;
                    rope[0].y = headpos.y;
                        
                } else if (vertical != 0) {
                    rope[0].y += vertical;
                    rope[0].x = headpos.x;
                }
                tailpos = rope[ROPE_LENGTH - 1];
                path[tailpos.x][tailpos.y] = '#';
            }         

            printgrid(grid);
        }

        index++;
    } 

    printgrid(grid);

    printf("\n");
    int numtailvisits = getnumtailvisits(path);
    printf("numtailvisits: %i\n", numtailvisits); // Part 1: 5874

    fclose(input);
    return 0;
}

void setdimensions(FILE* input) {
    int horizontal, vertical, value;
    char line[5];
    char dir;

    horizontal = 0;
    vertical = 0;

    fseek(input, 0, SEEK_SET);
    while (fgets(line, sizeof(line), input) != NULL) {
        sscanf(line, "%c %i", &dir, &value);
        printf("Dir: %c Value:%i\n", dir, value);

        if (dir == 'R') {
            horizontal += value;
        } else if (dir == 'L') {
            horizontal -= value;
        } else if (dir == 'U') {
            vertical -= value;
        } else if (dir == 'D') {
            vertical += value;
        }
    } 

    dimensions.x = abs(horizontal) + 3;
    dimensions.y = abs(vertical) + 3;
}

void printgrid(char grid[dimensions.x][dimensions.y]) {
    for (int y = 0; y < dimensions.y; y++)
    {
        for (int x = 0; x < dimensions.x; x++)
        {

            if (x == headpos.x && y == headpos.y) {
                grid[x][y] = 'H';
            } else if (x == tailpos.x && y == tailpos.y) {
                grid[x][y] = 'T';
            } else if (x == startingpoint.x && y == startingpoint.y) {
                grid[x][y] = 's';
            } else {
                grid[x][y] = '.';
            }

            for (int r = ROPE_LENGTH-1; r >= 0; r-- ) {
                grid[rope[r].x][rope[r].y] = (r+1) + '0';
            }

            printf("%c", grid[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}

int getnumtailvisits(char grid[dimensions.x][dimensions.y]) {

    int numtailvisits = 0;
    for (int y = 0; y < dimensions.y; y++)
    {
        for (int x = 0; x < dimensions.x; x++)
        {
            if (grid[x][y] != '#') {
                grid[x][y] = '.';
            } else {
                numtailvisits++;
            }
            printf("%c", grid[x][y]);
        }
        printf("\n");
    }

    return numtailvisits;
}