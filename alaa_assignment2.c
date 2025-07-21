#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// struct for movie
struct movie {
    char name[50];
    int year;
    char languages[5][20];
    float rating;
};

// struct for movie node, necessary for linked list
struct movieNode {
    struct movie data;
    struct movieNode *next;
};

// Parse a language string
void parseLanguages(char *languageStr, char languages[5][20]) {

    char *token = strtok(languageStr + 1, ";]");
    int i = 0;
    // Loop set to go through each element 
    while(token != NULL && i < 5) {
        strncpy(languages[i], token, 19);
        languages[i][19] = '\0';  // null-termination
        i++;
        token = strtok(NULL, ";]");
    }

}

void showMoviesByYear(struct movieNode *head, int year) {
    // Movies found initializa 
    int found = 0;

    // Setting while loop
    while (head != NULL) {
        // Points to year of head node for movie desired
        if (head->data.year == year) {
            printf("%s\n", head->data.name);
            found = 1;
        }
        // Update head to be the next node
        head = head->next;
    }
    // Message output if desired year has no movies
    if (!found) {
        printf("No data about movies released in the year %d\n", year);
    }
}



int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    FILE *file = fopen(argv[1], "r");
    if (!file) return 1;

    char line[1024];
    int movieCount = 0;

    // Setting up head and tail for linked list
    struct movieNode *head = NULL;
    struct movieNode *tail = NULL;

    // Skipping header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        struct movie mov;
        char *token = strtok(line, ",");

        // Title of the movie
        strncpy(mov.name, token, 49);
        mov.name[49] = '\0';
        token = strtok(NULL, ",");

        // Year of release for the movie
        mov.year = atoi(token);
        token = strtok(NULL, ",");

        // Languages movie was released in
        parseLanguages(token, mov.languages);
        token = strtok(NULL, ",");

        // Rating of the movie
        mov.rating = atof(token);

        // Creating nodes for movie/linked
        struct movieNode *newNode = malloc(sizeof(struct movieNode));
        newNode->data = mov;
        newNode->next = NULL;

        // Adding to the linked list
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        // Next element
        movieCount++;
    }

    fclose(file);

    // Output message
    printf("Processed file %s and parsed data for %d movies\n", argv[1], movieCount);

    // Menu input for options
    int inputNum;

    do {
        printf("\n1. Show movies released in the specified year\n");
        printf("2. Show highest rated movie for each year\n");
        printf("3. Show movies and their year of release for a specific language\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &inputNum);

        if (inputNum == 1) {
            int year;
            printf("Enter the year: ");
            scanf("%d", &year);
            // TODO: Implement function to show movies by year

        } else if (inputNum == 2) {
            // TODO: Implement function to show highest rated movie by year

        } else if (inputNum == 3) {
            char language[20];
            printf("Enter the language: ");
            scanf("%s", language);
            // TODO: Implement function to show movies by language

        } else if (inputNum == 4) {
            break;
        } else {
            printf("You entered an incorrect choice. Try again.\n");
        }

    } while (inputNum != 4);

    // Free linked list memory
    struct movieNode *curr = head;
    while (curr != NULL) {
        struct movieNode *temp = curr;
        curr = curr->next;
        free(temp);
    }

    return 0;
}

