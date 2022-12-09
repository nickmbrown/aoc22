#include <stdio.h>
#include <stdlib.h>

int xsize, ysize;
int updist, downdist, leftdist, rightdist;

void setdimensions(FILE*);
void printgrid(int[xsize][ysize]);
int getnumvisible(char[xsize][ysize]);
int greaterthanright(int[xsize][ysize], int, int, int);
int greaterthanleft(int[xsize][ysize], int, int, int);
int greaterthantop(int[xsize][ysize], int, int, int);
int greaterthanbottom(int[xsize][ysize], int, int, int);
int calculatescenicscore(int[xsize][ysize], int, int, int);

int main(void) {
    FILE* input = fopen("aoc_08_input.txt", "r");
    char line[200];
    int rowIndex = 0, colIndex = 0;
    int numvisible = 0;
    int greatestscenicscore = 0;

    if (input == NULL) {
        printf("Can't open file");
        return -1;
    }

    setdimensions(input);
    int grid[xsize][ysize];
    char visible[xsize][ysize];

    // Load array
    fseek(input, 0, SEEK_SET);
    while (fgets(line, sizeof(line), input) != NULL) {
        rowIndex = 0;

        for (int i = 0; i < sizeof(line); i++)
        {
            if(line[i] == '\n' || line[i] == EOF) {
                break;
            }

            int value = line[i] - '0';
            grid[rowIndex][colIndex] = value;

            if (rowIndex >= xsize) {
                break;
            }

            rowIndex++;
        }

        if (colIndex >= ysize) {
            break;
        }

        colIndex++;
    } 

    // printgrid(grid);

    for (int y = 0; y < ysize; y++)
    {
        for (int x = 0; x < xsize; x++)
        {
            if(x == 0 || x == xsize-1 || y == 0 || y == ysize-1) {
                visible[x][y] = 'v';
                continue;
            } else if (greaterthanleft(grid, x, y, xsize) == 0 ||
                greaterthanright(grid, x, y, xsize) == 0 ||
                greaterthantop(grid, x, y, xsize) == 0 ||
                greaterthanbottom(grid, x, y, xsize) == 0) {
                
                int scenicscore = calculatescenicscore(grid, x, y, xsize);
                if(scenicscore > greatestscenicscore) {
                    greatestscenicscore = scenicscore;
                }

                visible[x][y] = 'v';
            } else {
                visible[x][y] = 'h';
            }
            // printf("\n");
        }
    }

    numvisible = getnumvisible(visible);
    printf("numvisible: %i\n", numvisible);

    printf("Scenic score: %i\n", greatestscenicscore);

    fclose(input);
    return 0;
}

void setdimensions(FILE* input) {
    int c, rowcount, colcount;
    rowcount = 0;
    colcount = 0;

    for (c = fgetc(input); c != EOF; c = fgetc(input)) {
        if (c == '\n' || c == EOF) {
            ++rowcount;
            colcount = 0;
        }
        ++colcount;
    }

    xsize = colcount-1;
    ysize = rowcount+1;
}

int getnumvisible(char grid[xsize][ysize]) {
    int visible = 0;
    printf("Printing...\n");
    for (int y = 0; y < ysize; y++)
    {
        for (int x = 0; x < xsize; x++)
        {
            // printf("%c", grid[x][y]);
            if(grid[x][y] == 'v') {
                visible++;
            }
        }

        // printf("\n");
    }
    return visible;
}

void printgrid(int grid[xsize][ysize]) {
    printf("\nPrinting...\n");
    for (int y = 0; y < ysize; y++)
    {
        for (int x = 0; x < xsize; x++)
        {
            printf("%i", grid[x][y]);
        }

        printf("\n");
    }
}

int greaterthanright(int grid[xsize][ysize], int x, int y, int size) {

    int value = grid[x][y];

    for (int i = size-1; i >= 0; i--)
    {
        if (i == x) {
            return 0;
        } else if (value <= grid[i][y]) {
            return 1; // false
        } 
    }
    
    return 0;
}

int greaterthanleft(int grid[xsize][ysize], int x, int y, int size) {

    int value = grid[x][y];

    for (int i = 0; i < size; i++)
    {
        if (i == x)  {
            return 0;
        } else if (value <= grid[i][y]) {
            return 1; // false
        } 
    }
    
    return 0;
}

int greaterthantop(int grid[xsize][ysize], int x, int y, int size) {

    int value = grid[x][y];

    for (int i = 0; i < size; i++)
    {
        if (i == y)  {
            return 0;
        } else if (value <= grid[x][i]) {
            return 1; // false
        } 
    }

    return 0;
}

int greaterthanbottom(int grid[xsize][ysize], int x, int y, int size) {
    
    int value = grid[x][y];

    for (int i = size-1; i >= 0; i--)
    {
        if (i == y)  {
            return 0;
        } else if (value <= grid[x][i]) {
            return 1; // false
        }
    }

    return 0;
}

int calculatescenicscore(int grid[xsize][ysize], int x, int y, int size) {
    
    int value = grid[x][y];
    leftdist = 0;
    rightdist = 0;
    updist = 0;
    downdist = 0;

    // left
    for (int l = x-1; l >= 0; l--) {
        leftdist++;
        if (value <= grid[l][y]) {
            break;
        }
    }

    //right
    for (int r = x+1; r < size; r++) {
        rightdist++;
        if (value <= grid[r][y]) {
            break;
        }
    }

    //up
    for (int u = y-1; u >= 0; u--) {
        updist++;
        if (value <= grid[x][u]) {
            break;
        }
    }

    //down
    for (int d = y+1; d < size; d++) {

        downdist++;
        if (value <= grid[x][d]) {
            break;
        }
    }

    return leftdist * rightdist * updist * downdist;
}