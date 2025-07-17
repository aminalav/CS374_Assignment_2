#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    }

    fclose(file);
    return 0;
}