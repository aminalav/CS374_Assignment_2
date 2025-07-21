#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct movie {
    char name[50];
    int year;
    char languages[5][20];
    float rating;
};

struct movieNode {
    struct movie data;
    struct movieNode *next;
};

// Parse a language string

void parseLanguages(char *languageStr, char languages[5][20]) {

    char *token = strtok(languageStr + 1, ";]");
    int i = 0;

    while(token != NULL && i < 5) {
        strncpy(languages[i], token, 19);
        languages[i][19] = '\0';  // null-termination
        i++;
        token = strtok(NULL, ";]");
    }

}



int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    FILE *file = fopen(argv[1], "r");
    if (!file) return 1;

    char line[1024];

    // Optional: skip header line
    fgets(line, sizeof(line), file); 

    while (fgets(line, sizeof(line), file)) {
        // Remove newline at end if it exists
        line[strcspn(line, "\n")] = 0;

        // Tokenizing and printing each field
        char *token = strtok(line, ",");
        int column = 1;

        while (token != NULL) {
            printf("Field %d: %s\n", column, token);
            token = strtok(NULL, ",");
            column++;
        }

        printf("-----\n"); // separator between rows
        //stdout("Professed file XYZ and parsed data for M movies")

    }
    
    int inputNum;

    printf("Type a number: \n");

    scanf("%d", &inputNum);

    printf("Your number is: %d", inputNum);

    fclose(file);

    return 0;
}

