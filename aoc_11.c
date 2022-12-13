#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MONKIES 8
#define ROUNDS 20
#define ACTIVE_MONKIES 2
#define ITEMS 20

struct monkey {
    int index;
    ulong items[ITEMS];
    int inspecteditems;
    int test;

    char operation[30];
    char iftrue[30];
    char iffalse[30];
};

int startswith(const char *pre, const char *);
void printsinglemonkey(struct monkey, int);
void printmonkies(struct monkey[]);
ulong arrayisempty(ulong[], int);
void throwtomonkey(struct monkey[], int, ulong);
char* replaceword(const char*, const char*, const char*);
ulong eval(char *);
ulong operate(char[], ulong);
void loadmonkies(FILE *, struct monkey []);
void bubblesort(int[], int);
ulong calcmonkeybusiness(int[]);

int main(void) {
    FILE* input = fopen("aoc_11_input.txt", "r");
    if (input == NULL) {
        printf("Can't open file");
        return -1;
    }
    
    int monkeytothrow;
    ulong newworrylevel;
    int activeMonkies[NUM_MONKIES];
    int monkeybusiness = 1;
    struct monkey monkies[NUM_MONKIES];

    loadmonkies(input, monkies);
    printf("Starting Items\n");
    printmonkies(monkies);
    fclose(input);

    for(int r = 0; r < ROUNDS; r++ ) {
        for (int i = 0; i < NUM_MONKIES; i++) {

            // Monkey isn't holding any items
            if(arrayisempty(monkies[i].items, ITEMS) == 0) {
                continue;
            }
            
            for (int j = 0; j < ITEMS; j++)
            {
                if(monkies[i].items[j] == 0) break;

                // Calculate worry level
                newworrylevel = operate(monkies[i].operation, monkies[i].items[j]);
                newworrylevel = newworrylevel / 3;

                monkies[i].items[j] = newworrylevel;

                // Test item
                monkies[i].inspecteditems++;
                if(newworrylevel % monkies[i].test == 0) {
                    sscanf(monkies[i].iftrue, "throw to monkey %d", &monkeytothrow);
                } else {
                    sscanf(monkies[i].iffalse, "throw to monkey %d", &monkeytothrow);
                }

                // Throw item - get next open item slot from target monkey
                throwtomonkey(monkies, monkeytothrow, monkies[i].items[j]);
                monkies[i].items[j] = 0; 
            }
        }

        printf("\nRound %d\n", r+1);
        printmonkies(monkies);
    }

    // Generate array of inspected items
    for (int i = 0; i < NUM_MONKIES; i++)
    {
        activeMonkies[i] = monkies[i].inspecteditems;
    }

    printf("\n\nMonkies\n=============\n\n");
    printmonkies(monkies);

    bubblesort(activeMonkies, NUM_MONKIES);

    for (int i = 0; i < NUM_MONKIES; i++)
    {
        printf("%i ", activeMonkies[i]);
    }
    printf("\n");

    for (int i = 0; i < NUM_MONKIES; i++)
    {
        printf("Monkey %i inspected items %i times.\n", i, monkies[i].inspecteditems);
    }
    
    printf("Monkey Business: %ld\n", calcmonkeybusiness(activeMonkies));

    return 0;
}

void printsinglemonkey(struct monkey monkey, int i) {
    printf("Monkey %i:", i);
    for(int j = 0; j < ITEMS; j++) {
        if(monkey.items[j] == 0) break;
        printf(" %ld,", monkey.items[j]);
    }

    // printf("\nOperation: %s", monkey.operation);
    // printf("Test: %i\n", monkey.test);
    // printf("If True: %s", monkey.iftrue);
    // printf("If False: %s", monkey.iffalse);
    printf("\n");
}

void printmonkies(struct monkey monkies[]) {
    for(int i = 0; i < NUM_MONKIES; i++) {
        printsinglemonkey(monkies[i], i);
    }
    printf("\n");
}

ulong arrayisempty(ulong array[], int size) {
    for (int i = 0; i < size; i++) {
        if(i != 0) {
            return 1;
        }
    }
    return 0;
}

void throwtomonkey(struct monkey monkies[], int monkeytothrow, ulong item) {
    for (int k = 0; k < ITEMS; k++ ) {
        if (monkies[monkeytothrow].items[k] == 0) {
            monkies[monkeytothrow].items[k] = item;
            break;
        }
    }
}

int startswith(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre));
}

// Function is from GeeksForGeeks.com
char* replaceword(const char* s, const char* oldW, const char* newW)
{
	char* result;
	int i, cnt = 0;
	int newWlen = strlen(newW);
	int oldWlen = strlen(oldW);

	// Counting the number of times old word
	// occur in the string
	for (i = 0; s[i] != '\0'; i++) {
		if (strstr(&s[i], oldW) == &s[i]) {
			cnt++;

			// Jumping to index after the old word.
			i += oldWlen - 1;
		}
	}

	// Making new string of enough length
	result = malloc(i + cnt * (newWlen - oldWlen) + 1);

	i = 0;
	while (*s) {
		// compare the substring with the result
		if (strstr(s, oldW) == s) {
			strcpy(&result[i], newW);
			i += newWlen;
			s += oldWlen;
		}
		else
			result[i++] = *s++;
	}

	result[i] = '\0';
	return result;
    free(result);
}

// Function provided by user Steve Summit on StackOverflow
// https://stackoverflow.com/questions/51476556/how-to-convert-a-string-with-mathematical-operators-to-number-integer-or-float
ulong eval(char *str) {
    char *p;
    ulong lhs, rhs;
    char op;
    ulong r = 0;
    lhs = strtol(str, &p, 10);
    while(*p == ' ') p++;
    op = *p++;
    rhs = strtol(p, &p, 10);
    switch(op) {
        case '+': r = lhs + rhs; break;
        case '*':
            r = lhs * rhs; 
            // printf("Multiplying %li * %li = %li\n", lhs, rhs, r); 
            break;
    }
    return r;
}

ulong operate(char operation[], ulong value) {
    char valstring[8];
    sprintf(valstring, "%ld", value);
    operation = replaceword(operation, "old", valstring);
    // printf("Operation: %s\n", operation);

    ulong result = eval(operation);
    return result;
}

void loadmonkies(FILE* input, struct monkey monkies[]) {
    char line[200];
    char *token;
    char delim[] = ", ";
    int monkeyindex = 0, itemindex;

    for(int i = 0; i < NUM_MONKIES; i++ ) {  
        monkies[i].inspecteditems = 0;     
        for (int j = 0; j < ITEMS; j++)
        {
            monkies[i].items[j] = 0;
        }
    }

    while (fgets(line, sizeof(line), input) != NULL) {

        if(sscanf(line, "Monkey %i", &monkeyindex) == 1) {
            // printf("Monkey %i\n", monkeyindex);
            monkies[monkeyindex].index = monkeyindex;
            monkies[monkeyindex].inspecteditems = 0;
        } else if (startswith("  Starting items:", line) == 0) {
            memmove(line, line+18, strlen(line));
            
            // int item[ITEMS] = {0};

            itemindex = 0;
            token = strtok(line, delim);

            while (token != NULL) {
                // item[itemindex] = atoi(token);
                monkies[monkeyindex].items[itemindex] = atoi(token);
                token = strtok(NULL, delim);
                itemindex++;
            }
            
        } else if (startswith("  Operation:", line) == 0) {
            memmove(line, line+18, strlen(line));
            strcpy(monkies[monkeyindex].operation, line);
        } else if (startswith("  Test:", line) == 0) {
            memmove(line, line+21, strlen(line));
            monkies[monkeyindex].test = atoi(line);
            // strcpy(monkies[monkeyindex].test, line);
        } else if (startswith("    If true:", line) == 0) {
            memmove(line, line+13, strlen(line));
            strcpy(monkies[monkeyindex].iftrue, line);
        } else if (startswith("    If false:", line) == 0) {
            memmove(line, line+14, strlen(line));
            strcpy(monkies[monkeyindex].iffalse, line);
        }
    }
}

void bubblesort(int array[], int size) {
    int temp;
    for (int i = 0; i < size - 1; i++)
    {
        for(int j = 0; j < size - i - 1; j++) {
            if(array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

ulong calcmonkeybusiness(int activeMonkies[]) {
    ulong monkeybusiness = 1;
    for (int i = NUM_MONKIES - ACTIVE_MONKIES; i < NUM_MONKIES; i++)
    {
        printf("Multiplying %ld * %i\n", monkeybusiness, activeMonkies[i]);
        monkeybusiness *= activeMonkies[i];
    }
    return monkeybusiness;
}