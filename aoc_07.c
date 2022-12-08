#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100000
#define RECURSION_DEPTH 10
#define TOTAL_SPACE 70000000
#define MIN_SPACE 30000000

fpos_t prevDirPos[RECURSION_DEPTH];
char line[50];
int depth = 0, totalsize = 0, allfiles = 0, folderindex = 0;
int smallestfolder = TOTAL_SPACE;
int folders[100];

int startswith(const char *, const char *);
int parsefolder(FILE *);

int main(void) {
    FILE* input = fopen("aoc_07_input.txt", "r");
    int filteredfiles, unusedspace;

    if(input == NULL) {
        printf("Couldn't read file");
        return -1;
    }

    filteredfiles = parsefolder(input); // PART 1 : 1723892
    printf("Part 1: %i\n", filteredfiles);

    unusedspace = TOTAL_SPACE - allfiles; 

    for (int i = 0; i < sizeof(folders); i++)
    {
        if (folders[i] == 0) {
            continue;
        }
        else if(folders[i] + unusedspace >= MIN_SPACE && folders[i] < smallestfolder) {
            smallestfolder = folders[i];
        }
    }
    
    printf("Part 2: %i\n", smallestfolder);
    // printf("All files: %i\n", allfiles);

    fclose(input);
    return 0;
}

int startswith(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre));
}

int parsefolder(FILE* input) {
    int filesize = 0, foldersize = 0;

    fsetpos(input, &prevDirPos[depth]);
    
    while (fgets(line, sizeof(line), input) != NULL) {
        // printf("Depth: %i - %s", depth, line);

        if(startswith("$ cd ..", line) == 0) {
            depth--;
            totalsize += (foldersize <= MAX_SIZE) ? foldersize : 0;
            // totalsize += foldersize;

            folders[folderindex] = foldersize;
            folderindex++;

            return foldersize;
        }

        else if (startswith("$ cd", line) == 0) {
            // printf("%s", line);
            depth++;
            fgetpos(input, &prevDirPos[depth]);
            
            foldersize += parsefolder(input);

        } else if(sscanf(line, "%i", &filesize)) {
            // printf("File size: %i\n", filesize);
            foldersize += filesize;
            allfiles += filesize;
        } 
    }

    folders[folderindex] = foldersize;
    folderindex++;

    totalsize += (foldersize <= MAX_SIZE) ? foldersize : 0;
    return totalsize;
}