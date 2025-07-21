#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct movie {
    char name[50];
    int year;
    char languages[5][20];
    float rating;
    struct movie *next;  //This points to the next movie, setting up linked list
};

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

