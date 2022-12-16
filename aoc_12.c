#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INFINITY 9999
#define MAX 10
#define DEPTH 50


struct vec2 {
    int x, y;
};

struct vec2 dimensions = { 8, 5 };

int loadheightmap(char [dimensions.x][dimensions.y], struct vec2 *, struct vec2 *);
void printheightmap(char [dimensions.x][dimensions.y], struct vec2 *, struct vec2 *);

int vec2_equals(struct vec2 *a, struct vec2 *b) {
    if(a->x != b->x || a->y != b->y) 
        return 1;
    return 0;
}

void dijkstra(int graph[MAX][MAX], int n, int start);
int getshortestpath(char heightmap[dimensions.x][dimensions.y], struct vec2 *);

void vec2_set(struct vec2 *original, struct vec2 new) {
    original->x = new.x;
    original->y = new.y;
}

struct vec2 vec2_add(struct vec2 *a, struct vec2 *b) {
    struct vec2 sum;
    sum.x = a->x + b->x;
    sum.y = a->y + b->y;
    return sum;
}

int main(void) {
    char heightmap[dimensions.x][dimensions.y];
    char travelmap[dimensions.x][dimensions.y];
    struct vec2 currentpos, endpos;
    int steps = 0;
    if(loadheightmap(heightmap, &currentpos, &endpos) != 0) {
        printf("Couldn't load heightmap");
        return -1;
    }

    for (int y = 0; y < dimensions.y; y++)
    {
        for (int x = 0; x < dimensions.x; x++)
        {
            travelmap[x][y] = '.';
        }
        
    }
    

    printheightmap(heightmap, &currentpos, &endpos);

    steps = getshortestpath(heightmap, &endpos);

    // printf("CurrentPos: [%i,%i] EndPos: [%i,%i]\n\n", currentpos.x, currentpos.y, endpos.x, endpos.y);


    // dijkstra(heightmap, 4, 0);

    // printheightmap(heightmap, &currentpos, &endpos);
    // printf("Steps: %i\n", steps);

    printf("\n");

    return 0;
}

int loadheightmap(char heightmap[dimensions.x][dimensions.y], struct vec2 *currentpos, struct vec2 *endpos) {
    FILE* input = fopen("aoc_12_input.txt", "r");
    char line[20];
    int y = 0;
    
    if (input == NULL) {
        printf("Can't open file");
        return -1;
    }

    while (fgets(line, sizeof(line), input) != NULL) {
        for(int x = 0; x < dimensions.x; x++) {
            heightmap[x][y] = line[x];
            
            if(line[x] == 'S') {
                currentpos->x = x;
                currentpos->y = y;
                heightmap[x][y] = 'a';
            }
            if(line[x] == 'E') {
                endpos->x = x;
                endpos->y = y;
                heightmap[x][y] = 'z';
            }
        }
        y++;
    }

    return 0;
    fclose(input);
}

void printheightmap(char heightmap[dimensions.x][dimensions.y], struct vec2 *currentpos, struct vec2 *endpos) {
    for (int y = 0; y < dimensions.y; y++)
    {
        for (int x = 0; x < dimensions.x; x++)
        {
            if (x == currentpos->x && y == currentpos->y) {
                printf("%c", 'S');
            } else if (x == endpos->x && y == endpos->y) {
                printf("%c", 'E');
            } else {
                printf("%c", heightmap[x][y]);
            }
        }

        printf("\n");
    }
}

// LMAO
int getshortestpath(char heightmap[dimensions.x][dimensions.y], struct vec2 *endpos) {
    int size = dimensions.x * dimensions.y;
    struct vec2 directions[] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

    struct node {
        struct vec2 pos;
        int dist;
        struct node *prevnode;
    };

    struct node visited[dimensions.x][dimensions.y];
    struct vec2 currentpos = {0,0};

    struct node *currentnode, *prevnode, *endnode;
    struct node start = { currentpos, 0, NULL };
    struct node end = { *endpos, INFINITY, NULL };
    currentnode = &start;

    visited[0][0] = start;
    visited[endpos->x][endpos->y] = end;

    for (int y = 0; y < dimensions.y; y++) {
        for (int x = 0; x < dimensions.x; x++) {
            if(vec2_equals(&visited[x][y].pos, &start.pos) == 0) continue;
            if(vec2_equals(&visited[x][y].pos, &end.pos) == 0) continue;
            visited[x][y].pos.x = x;
            visited[x][y].pos.y = y;
            visited[x][y].dist = INFINITY;
            visited[x][y].prevnode = NULL;
        }
    }

    for (int y = 0; y < dimensions.y; y++) {
        for (int x = 0; x < dimensions.x; x++) {
            for (int i = 0; i < 4; i++) {

                if(visited[x + directions[i].x][y + directions[i].y].dist < 100) {
                    // printf("Already been here. Skipping.\n");
                    break;
                }

                if (heightmap[x + directions[i].x][y + directions[i].y] - heightmap[x][y] <= 1  && 
                    heightmap[x + directions[i].x][y + directions[i].y] - heightmap[x][y] >= 0) {
                
                    // if out of bounds, skip
                    if (((x + directions[i].x) > dimensions.x || (x + directions[i].x < 0)) ||
                        ((y + directions[i].y) > dimensions.y || (y + directions[i].y < 0))) {
                        continue;
                    }

                    prevnode = &visited[x][y];
                    currentnode->prevnode = prevnode;

                    currentnode = &visited[x + directions[i].x][y + directions[i].y];
                    printf("currentnode [%i, %i] prevdist: %i\n", currentnode->pos.x, currentnode->pos.y, prevnode->dist);

                    currentnode->dist = prevnode->dist + 1;
                    // currentnode->dist = 1;
                }

                if(vec2_equals(&currentnode->pos, endpos) == 0) {
                    printf("EQUAL\n");
                }
            }
        }
    }

    struct node *head = &end;
    struct node *ptr = head;
    while(ptr != NULL) {
        printf("(%d)\n",ptr->dist);
        ptr = ptr->prevnode;
    }


    for (int y = 0; y < dimensions.y; y++) {
        for (int x = 0; x < dimensions.x; x++) {
            printf("Dist: %i\n", visited[x][y].dist);
        }
    }


    printf("\nVisited\n");
    for (int y = 0; y < dimensions.y; y++)
    {
        for (int x = 0; x < dimensions.x; x++)
        {
            if (visited[x][y].dist == INFINITY) {
                printf("8");
            } else {
                printf("1");
            }
        }

        printf("\n");
    }

    // while(vec2_equals(&currentpos, endpos) != 0) {
    //     // printf("CurrentPos: [%i,%i] EndPos: [%i,%i]\n\n", currentpos.x, currentpos.y, endpos.x, endpos.y);


    //     for (int i = 0; i < 4; i++) {
    //         // printf("Looking at direction [%i,%i]\n", directions[i].x, directions[i].y);

    //         for(int j = 0; j < size; j++) {
    //             if(currentpos.x + directions[i].x == visited[j].pos.x && currentpos.y + directions[i].y == visited[j].pos.y) {
    //                 // printf("Already been here. Skipping.\n");
    //                 continue;
    //             }
    //         }

    //         index = dimensions.x * currentpos.x + directions[i].x + currentpos.y + directions[i].y;

    //         if(heightmap[currentpos.x + directions[i].x][currentpos.y + directions[i].y] - heightmap[currentpos.x][currentpos.y] <= 1  && 
    //         heightmap[currentpos.x + directions[i].x][currentpos.y + directions[i].y] - heightmap[currentpos.x][currentpos.y] >= 0) {
                
    //             vec2_set(&visited[index].pos, vec2_add(&currentpos, &directions[i]));
                
    //             visited[index].prevnode = &visited[dimensions.x * currentpos.x + currentpos.y];
    //             visited[index].dist = visited[index].prevnode->dist + 1;
    //             printf("Direction: [%i, %i] Index: %i\n", directions[i].x, directions[i].y, index);
    //         }


    //     }



    //     // SORT
    //     int temp;
    //     for (int i = 0; i < size - 1; i++)
    //     {
    //         for(int j = 0; j < size - i - 1; j++) {
    //             if(visited[j].dist > visited[j + 1].dist) {
    //                 temp = visited[j].dist;
    //                 visited[j].dist = visited[j + 1].dist;
    //                 visited[j + 1].dist = temp;
    //             }
    //         }
    //     }

    //     for (int i = 0; i < size; i++)
    //     {
    //         if(visited[i].dist == INFINITY) continue;
    //         printf("Visited dist: %i\n", visited[i].dist);
    //     }

    //     // printf("Setting currentpos to [%i, %i]\n", visited[visitedindex].pos.x, visited[visitedindex].pos.y);
    //     currentpos.x = visited[visitedindex].pos.x;
    //     currentpos.y = visited[visitedindex].pos.y;
    //     vec2_set(&currentpos, visited[visitedindex].pos);
    //     visitedindex++;



        
    //     break;
    //     // currentpos.x = visitednodes[visitedindex].x;
    //     // currentpos.y = visitednodes[visitedindex].x;
    //     // visitedindex++;


    //     // printf("Current pos: [%i, %i]\n\n", currentpos.x, currentpos.y);

    //     if(vec2_equals(&currentpos, endpos) == 0) {
    //         printf("EQUAL\n");
    //         break;
    //     }       
    // }

    return 0;
}
