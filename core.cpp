#include "core.h"

// TODO: add more global variables to complete tasks
bool __coreInitialized = false;  /// an example of global variable
// int  __userChoice = 0;        /// a global variable to store user choice
bool __isExiting = false ;       /// this variable should be turn on when the program exits
char __fileContent[1500];
char __menu[200];
int __exitOpt;

/**
 * Function: Initialization
 * Purpose:  Initialize anything necessary in your program before starting
 * Input:    None
 * Output:   None
 */
void Initialization() {
    // TODO: write the code to initialize the program
    // Open file and save data in string
    const char* filePath = "./conf.json";
    FILE* file;
    file = fopen(filePath, "r");
    int index = 0;

    while ((__fileContent[index] = fgetc(file)) != EOF) {
        index++;
    }
    __fileContent[index - 1] = '\0';

    fclose(file);

    LoadConfiguration();
    LoadMenu();
    __coreInitialized = true;
}

/**
 * Function: Finalization
 * Purpose:  Clean up everything before the program exits
 * Input:    None
 * Output:   None
 */
void Finalization() {
    // TODO: write the code to clean up when the program exits
}

void LoadConfiguration() {
    // TODO: write code to load data from the configuration file
    char welcome[1000];
    int index = 0;
    // Cut string in WelcomeText
    for (int i = 0; __fileContent[i] != '\0'; i++) {
        if ((__fileContent[i] == 'W') && (__fileContent[i + 1] == 'e') && (__fileContent[i + 7] == 'T') && (__fileContent[i + 10] == 't')) {
            for (int j = i + 16; __fileContent[j] != '}'; j++) {
                welcome[index] = __fileContent[j];
                index++;
            }
        }
    }

    // Cut string in ""
    for (index = 0; welcome[index] != '\0'; index++) {
        if ((welcome[index] == '"') && (welcome[index + 1] == ':') && (welcome[index + 2] == ' ')) {
            for (int i = index + 4; welcome[i] != '"'; i++) {
                printf("%c", welcome[i]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

void LoadMenu() {
    // TODO: write code to load menu from the configuration file
    // Cut menu
    int index = 0;
    for (int i = 0; __fileContent[i] != '\0'; i++) {
        if ((__fileContent[i] == 'M') && (__fileContent[i + 1] == 'e') && (__fileContent[i + 2] == 'n') && (__fileContent[i + 7] == '{')) {
            for (int j = i + 9; __fileContent[j] != '}'; j++) {
                __menu[index] = __fileContent[j];
                index++;
            }
        }
    }
    
    // Cut option and save
    char opt[10];
    int indexOpt = 0;
    for (int i = 0; __menu[i] != '\0'; i++) {
        if ((__menu[i] == 'o') && (__menu[i + 1] == 'p') && (__menu[i + 2] == 't') && (__menu[i + 8] != 'E') && (__menu[i + 9] != 'x') && (__menu[i + 10] != 'i') && (__menu[i + 11] != 't')) {
            opt[indexOpt] = __menu[i + 3];
            indexOpt++;
        }
        else if ((__menu[i] == 'o') && (__menu[i + 1] == 'p') && (__menu[i + 2] == 't') && (__menu[i + 8] == 'E') && (__menu[i + 9] == 'x') && (__menu[i + 10] == 'i') && (__menu[i + 11] == 't')) {
            __exitOpt = __menu[i + 3] - 48;
        }
    }
    opt[indexOpt] = '\0';
}

void DisplayMenu() {
    // TODO: Display the menu loaded from configuration file
    int stt = 1;
    int i = 0;
    int j;
    for (i = 0; __menu[i] != '\0'; i++) {
        if ((__menu[i] == 'o') && (__menu[i + 1] == 'p') && (__menu[i + 2] == 't')) {
            printf("%d. ", stt);
            stt++;
            for (j = i + 8; __menu[j] != '"'; j++) {
                printf("%c", __menu[j]);
            }
            printf("\n");
        }
    }
    printf("Please select: ");
}

int power(int base, int power) {
    if (power == 0) {
        return 1;
    }

    int result = base;

    for (int i = 0; i < power - 1; i++) {
        result *= base;
    }

    return result;
}

void ProcessUserChoice() {
    // TODO: Read user input and process
    // Input data
    char user[20];
    int i = 0;
    do {
        scanf("%c", &user[i]);
        i++;
    } while(user[i - 1] != '\n' && i < 20);
    user[i - 1] = '\0';
    
    // Check data
    bool isInvalid = false;
    for (int i = 0; user[i] != '\0'; i++) {
        if ((user[i] != '0') && (user[i] != '1') && (user[i] != '2') && (user[i] != '3') && (user[i] != '4') && (user[i] != '5') && (user[i] != '6') && (user[i] != '7') && (user[i] != '8') && (user[i] != '9')) {
            printf("Invalid input, please input an integer number.\n");
            isInvalid = true;
        }
    }

    if (isInvalid == false) {
        // Cast to int
        int count = 0;
        for (int i = 0; user[i] != '\0'; i++) {
            count++;
        }
        int userChoice = 0;
        for (int i = 0; i < count; i++) {
            int k = user[i] - 48;
            userChoice += k * power(10, count - i - 1);
        }

        // Check range
        if ((userChoice > __exitOpt) && (userChoice < 0)) {
            printf("Please select from 1 to %d.", __exitOpt);
            printf("\n");
        }

        // Process data
        if (userChoice == __exitOpt) {
            printf("Exiting...");
            __isExiting = true;
        }
        else if ((userChoice >= 1) && (userChoice < __exitOpt)) {
            printf("You select menu item %d. Processing... Done!\n", userChoice);
        }
        else {
            printf("Please select from 1 to %d", __exitOpt);
            printf("\n");
        }
        }
}