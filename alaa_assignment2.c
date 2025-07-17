#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1; // Expecting file name as argument
    FILE *file = fopen(argv[1], "r");
    if (!file) return 1;

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line); // process line here
    }

    fclose(file);
    return 0;
}