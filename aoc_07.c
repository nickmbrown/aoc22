#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 100000
#define RECURSION_DEPTH 50
#define TOTAL_SPACE 70000000
#define MIN_SPACE 30000000

fpos_t prevDirPos[RECURSION_DEPTH];
char line[50];
int depth = 0, totalsize = 0, allfiles = 0, folderindex = 0;
int smallestfolder = TOTAL_SPACE;
int folders[100];

bool startswith(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}

int parsefolder(FILE* input) {
    int filesize = 0, foldersize = 0;

    fsetpos(input, &prevDirPos[depth]);
    
    while (fgets(line, sizeof(line), input) != NULL) {
        // printf("Depth: %i - %s", depth, line);

        if(startswith("$ cd ..", line)) {
            depth--;
            totalsize += (foldersize <= MAX_SIZE) ? foldersize : 0;
            // totalsize += foldersize;

            folders[folderindex] = foldersize;
            folderindex++;

            return foldersize;
        }

        else if (startswith("$ cd", line)) {
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


int main(void) {
    FILE* input = fopen("aoc_07_input.txt", "r");

    if(input == NULL) {
        printf("Couldn't read file");
        return -1;
    }

    int part = parsefolder(input); // PART 1 : 1723892
    printf("Part 1: %i\n", part);


    int unusedspace = TOTAL_SPACE - allfiles; 

    for (int i = 0; i < sizeof(folders); i++)
    {
        if (folders[i] == 0) {
            continue;
        }
        printf("Folder: %i\n", folders[i]);
        if(folders[i] + unusedspace >= MIN_SPACE && folders[i] < smallestfolder) {
            smallestfolder = folders[i];
            printf("Setting smallestfolder: %i\n", smallestfolder);
        }
    }
    


    printf("Part 2: %i\n", smallestfolder);
    printf("All files: %i\n", allfiles);

    // WRONG ANSWERS:
    // 2133411 - too high
    // 17654 - too low
    // 2151065 
    // 1361483
    // 388462
    // omg i want to cry

    // WRONG ANSWERS DEUX:
    // 29001698 - too high

    fclose(input);
    return 0;
}