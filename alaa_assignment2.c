// Author: Amin Alavi
// Date: July 20th, 2025
// Sources Used: Exploration: Arrays & Structures -> Code for structs, arrays, 
// Sources continued: Exploration: Pointers -> referenced to properly use pointers in code
// Sources continued: Exploration: Memory Allocation -> For dynamic memory allocation (malloc())
// Sources continued: Exploration: Strings, Exploration: Parsing Strings

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

void displayMoviesYear(struct movieNode *head, int year) {
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

void displayRatingYear(struct movieNode *head) {
    // Array for best movie node by particular year (year range set)
    struct movieNode *bestByYear[2022 - 1900] = {NULL};

    while (head != NULL) {
        int index = head->data.year - 1900;
        // Setting comparison to update head node. If null or rating > current date, update
        if (bestByYear[index] == NULL || head->data.rating > bestByYear[index]->data.rating) {
            bestByYear[index] = head;
        }
        // Updating head node (linked list)
        head = head->next;
    }

    // Print results
    for (int i = 0; i < 2022 - 1900; i++) {
        if (bestByYear[i] != NULL) {
            printf("%d %.1f %s\n", bestByYear[i]->data.year, bestByYear[i]->data.rating, bestByYear[i]->data.name);
        }
    }
}

// Definition to set up showing movies by language option
void displayByLanguage(struct movieNode *head, const char *language) {
    int found = 0;
    // Setting up while loop
    while (head != NULL) {
        // Language max is 5, increment/move to next language
        for (int i = 0; i < 5; i++) {
            // Setting parameters to compare and show languages for movie in particular year
            if (strcmp(head->data.languages[i], language) == 0) {
                printf("%d %s\n", head->data.year, head->data.name);
                found = 1;
                break; 
            }
        }
        // Update head to be next node (linked list)
        head = head->next;
    }
    // Message printed if no movies found for input
    if (!found) {
        printf("No data about movies released in %s\n", language);
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
        // Print messages displaying options to user
        printf("\n1. Show movies released in the specified year\n");
        printf("2. Show highest rated movie for each year\n");
        printf("3. Show movies and their year of release for a specific language\n");
        printf("4. Exit\n");

        // Entering input to select desired choice
        printf("Enter your choice: ");
        scanf("%d", &inputNum);

        // Selecting option 1, setting up to call defintion
        if (inputNum == 1) {
            int year;
            printf("Enter the year: ");
            scanf("%d", &year);
            displayMoviesYear(head, year);

        // Selecting option 2, setting up to call defintion
        } else if (inputNum == 2) {
            displayRatingYear(head);

        // Selecting option 3, setting up to call defintion
        } else if (inputNum == 3) {
            char language[20];
            printf("Enter the language: ");
            scanf("%s", language);
            displayByLanguage(head, language);
        
        // Option 4, to exit
        } else if (inputNum == 4) {
            break;
        // Incorrect choice handling
        } else {
            printf("You entered an incorrect choice. Try again.\n");
        }

    } while (inputNum != 4);

    // Freeing up linked list memory
    struct movieNode *curr = head;
    while (curr != NULL) {
        struct movieNode *temp = curr;
        curr = curr->next;
        free(temp);
    }

    return 0;
}

