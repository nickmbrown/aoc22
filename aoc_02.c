#include<stdio.h>
#include<stdlib.h>
#include<math.h>

char GetWinner(char*, char*);
int GetScore(char*, char*);
char DeterminePlay(char*, char*);
void PrintScore(FILE*);
int GetMoveValue(char*);


struct move
{
    const char letter;
    const int value;
} 

movemapping[] = {
    { 'A', 0 },
    { 'B', 1 },
    { 'C', 2 },
    { 'X', 0 },
    { 'Y', 1 },
    { 'Z', 2 },
};

int main(void) {
    FILE* input = fopen("aoc_02_input.txt", "r");
    if (input == NULL) 
    {
        printf("Error. File could not be opened\n");
        return -1;
    }

    PrintScore(input);

    fclose(input);
    return 0;
}

void PrintScore(FILE* input) {
    int roundscore, totalscore = 0;
    char line[5];

    while (fgets(line, sizeof(line), input) != NULL) {

        char* p1 = &line[0];
        char* p2 = &line[2];
    
        char newPlay = DeterminePlay(p1, p2);
        // roundscore = GetScore(p1, p2);
        roundscore = GetScore(p1, &newPlay);
        totalscore += roundscore;
    }

    // Part 1 = 14827
    // Part 2 = 13889    

    printf("Total Score: %i\n", totalscore); 
}

char GetWinner(char* p1, char* p2) {
    int p1val = GetMoveValue(p1);
    int p2val = GetMoveValue(p2);

    int winnerNumber = abs(p2val - p1val);
    if (winnerNumber == 0) { 
        return '\0'; // both numbers are the same so it's a tie
    } else if (winnerNumber == 1) { // the numbers are consecutive so the larger one wins
        return p1val < p2val ? *p2 : *p1; 
    } else { // the numbers are not consecutive so the smaller one wins
        return p1val < p2val ? *p1 : *p2; 
    }
}

int GetScore(char* p1, char* p2) {
    int value = 0;

    value += GetMoveValue(p2) + 1;

    char winner = GetWinner(p1, p2);
    if (winner == *p1) {
        value += 0;
    } else if (winner == *p2) {
        value += 6;
    } else if (winner == '\0') {
        value += 3;
    }

    return value;
}

char DeterminePlay(char* p1, char* p2) {
    if (*p1 == 'A') { // opponent uses Rock
        if (*p2 == 'X') { // we should lose
            return 'Z';
        } else if (*p2 == 'Y') { // we should tie
            return 'X';
        } else if (*p2 == 'Z') { // we should win
            return 'Y';
        }
    } else if (*p1 == 'B') { // opponent uses Paper
        if (*p2 == 'X') { // we should lose
            return 'X';
        } else if (*p2 == 'Y') { // we should tie
            return 'Y';
        } else if (*p2 == 'Z') { // we should win
            return 'Z';
        }    
    } else if (*p1 == 'C') { // opponent uses Scissors
        if (*p2 == 'X') { // we should lose
            return 'Y';
        } else if (*p2 == 'Y') { // we should tie
            return 'Z';
        } else if (*p2 == 'Z') { // we should win
            return 'X';
        }    
    }
}

int GetMoveValue(char* move) {
    int movevalue;
    for (size_t i = 0; i < 6; i++)
    {
        if(*move == movemapping[i].letter)
        {
            return movemapping[i].value;
        }
    }

    return -1;
}