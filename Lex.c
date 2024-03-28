#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMERIC 72000
#define MAX_IDENTIFIER 12
#define INPUT "input2.txt"
#define INPUT_MOD "input3.txt"
#define OUTPUT_TOKENS "input4.txt"
#define OUTPUT_TOKENS_COMPLETE "input5.txt"

//void functions
void clearNoCommentFile();
void displayContents(const char* fileName);
void delFileAnnotations(char* inputFileName);
void decipherlex();
void TokenCatalog();
void FileDetails(char* header, char* fileName);

//File related functions
FILE* openFile(char* fileName, char* mode);

// int & char functions
int verifyNum(char c);
int verifyLet(char c);
int certifyIdent(char* ID);
int certifyNum(char* NUM);
int toInt(char* NUM);
char* scanUntilSymbolic(FILE* file);
char* attachChar(char* ch, char c);


//global variables for main function
int printSourceCode = 0;
int printSourceNoComments = 0;

//main function
int main(int argc, char** argv) {
    char fileNameBuffer[100];
    // Determine the file name; default used if no arguments provided
    if (argc == 1) {
        strcpy(fileNameBuffer, INPUT);
    } 
    
    // Custom file handling with potential flags for printing source code or removing comments
    else {
        strcpy(fileNameBuffer, argv[1]);
        int i;
        for (i = 2; i < argc; i++) {
            if (strcmp(argv[i], "--show-original") == 0) {
                printSourceCode = 1;
            } else if (strcmp(argv[i], "--show-clean") == 0) {
                printSourceNoComments = 1;
            }
        }
    }
    
    // Prepare the file without comments
    clearNoCommentFile();
    // Strip comments from the provided input file
    delFileAnnotations(fileNameBuffer);
    // Perform the lexical analysis process
    decipherlex();
    // Conditionally display the original and/or modified source based on user flags
    if (printSourceCode) {
        FileDetails("Original Source Code:", fileNameBuffer);
        printf("\n");
    }
    if (printSourceNoComments) {
        FileDetails("Modified Source Code:", INPUT_MOD);
        printf("\n");
    }
    // Display the list of tokens generated from the lexical analysis
    TokenCatalog();
}

// Function to clear the contents of a file except comments
void clearNoCommentFile() {
    FILE* a1 = openFile(INPUT_MOD, "w"); // Open the file for writing (truncate mode)
    fclose(a1);
}



// Function to display the contents of a file
void displayContents(const char* fileName) {
    FILE* a2 = fopen(fileName, "r"); 
    if (a2 == NULL) {
        fprintf(stderr, "Error: impossible to open file %s.\n", fileName); // Print error message if file opening fails
        return;
    }

    printf("\n\nSource Program: \n\n");

    char ch; 
    while ((ch = fgetc(a2)) != EOF) { // Read characters from the file until end of file is reached
        putchar(ch); 
    }

    fclose(a2); 
    printf("\n\n///////////\n\n"); 
}




void delFileAnnotations(char* inputFileName) {
    FILE* sourceFile = openFile(inputFileName, "r");
    FILE* cleanedFile = openFile(INPUT_MOD, "w");

    if (sourceFile == NULL || cleanedFile == NULL) {
        fprintf(stderr, "Error: Impossible to reach files.\n");
        exit(1);
    }

    char previousChar = '\0', currentChar;
    // Indicator for comment presence.
    int commentMode = 0;
    
    while (fscanf(sourceFile, "%c", &currentChar) != EOF) {
        if (!commentMode && previousChar == '/' && currentChar == '*') {
            // Initiate comment block
            commentMode = 1;
            // Omit '/' from being written to output.
            previousChar = '\0';
            continue;
        } else if (commentMode && previousChar == '*' && currentChar == '/') {
            // Terminate comment block
            commentMode = 0;
            // Prevent the subsequent '/' from being written.
            previousChar = '\0';
            continue;
        } else if (!commentMode && previousChar != '\0') {
            // Write characters outside comments
            if (fputc(previousChar, cleanedFile) == EOF) {
                fprintf(stderr, "Error writing to cleaned file.\n");
                exit(1);
            }
        }
        
        previousChar = currentChar;
    }

    // Ensure the final character is written if not within a comment
    if (!commentMode && previousChar != '\0' && previousChar != '/') {
        if (fputc(previousChar, cleanedFile) == EOF) {
            fprintf(stderr, "Error finalizing the cleaned file.\n");
            exit(1);
        }
    }

    // Conclude file operations
    fclose(sourceFile);
    fclose(cleanedFile);
    // Print the cleaned file content to the terminal
    displayContents(INPUT_MOD);
}

// Function to decipher and tokenize input characters
void decipherlex() {
    FILE* input = openFile(INPUT_MOD, "r"); // Open the input file for reading
    FILE* output = openFile(OUTPUT_TOKENS, "w"); // Open the output file for writing
    FILE* output2 = openFile(OUTPUT_TOKENS_COMPLETE, "w");

    printf("\nToken List:  \n");
    char curr; // Variable to store the current character being processed

    // Process characters from the input file until end of file is reached
    while(fscanf(input, "%c", &curr) != EOF) {
        // Skip whitespace characters and newline characters
        if (curr == ' ' || curr == '\n') continue;

        // Tokenize arithmetic operators
        else if (curr == '+') {
            fprintf(output, "%s %d ", "+", 4);
            printf("%d ", 4);
            fprintf(output2, "%d ", 4);
        }
        else if (curr == '-') {
            fprintf(output, "%s %d ", "-", 5);
            printf("%d ", 5);
            fprintf(output2, "%d ", 5);
        }
        else if (curr == '*') {
            fprintf(output, "%s %d ", "*", 6);
            printf("%d ", 6);
            fprintf(output2, "%d ", 6);
        }
        else if (curr == '/') {
            fprintf(output, "%s %d ", "/", 7);
            printf("%d ", 7);
            fprintf(output2, "%d ", 7);
        }

        // Tokenize assignment operator
        else if (curr == '=') {
            fprintf(output, "%s %d ", "=", 9);
            printf("%d ", 9);
            fprintf(output2, "%d ", 9);
        }

        // Tokenize parentheses, comma, semicolon, and period
        else if (curr == '(') {
            fprintf(output, "%s %d ", "(", 15);
            printf("%d ", 15);
            fprintf(output2, "%d ", 15);
        }
        else if (curr == ')') {
            fprintf(output, "%s %d ", ")", 16);
            printf("%d ", 16);
            fprintf(output2, "%d ", 16);
        }
        else if (curr == ',') {
            fprintf(output, "%s %d ", ",", 17);
            printf("%d ", 17);
            fprintf(output2, "%d ", 17);
        }
        else if (curr == ';') {
            fprintf(output, "%s %d ", ";", 18);
            printf("%d ", 18);
            fprintf(output2, "%d ", 18);
        }
        else if (curr == '.') {
            fprintf(output, "%s %d ", ".", 19);
            printf("%d ", 19);
            fprintf(output2, "%d ", 19);
        }

        // Tokenize assignment operator ":="
        else if (curr == ':') {
            char next;
            fscanf(input, "%c", &next);
            
            if (next == '=') {
                fprintf(output, "%s %d ", ":=", 20);
                printf("%d ", 20);
                fprintf(output2, "%d ", 20);
            } else {
                printf("Error: Invalid token (:%c) detected.\nProgram Terminated\n", next);
                exit(1);
            }
        }

        // Tokenize relational operators and not equal operator
        else if (curr == '<' || curr == '>') {
            char next;
            fscanf(input, "%c", &next);
            
            if (curr == '<' && next == '>') {
                fprintf(output, "%s %d ", "<>", 10);
                printf("%d ", 10);
                fprintf(output2, "%d ", 10);
            }
            else if (curr == '<' && next == '=') {
                fprintf(output, "%s %d ", "<=", 12);
                printf("%d ", 12);
                fprintf(output2, "%d ", 12);
            }
            else if (curr == '>' && next == '=') {
                fprintf(output, "%s %d ", ">=", 14);
                printf("%d ", 14);
                fprintf(output2, "%d ", 14);
            }

            else {
                fprintf(output, "%c %d ", curr, curr == '<' ? 11 : 13);
                printf("%d ", curr == '<' ? 11 : 13);
                fprintf(output2, "%d ", curr == '<' ? 11 : 13);
                fseek(input, -1, SEEK_CUR);
            }
        }

        // Tokenize numbers
        else if (verifyNum(curr)) {
            fseek(input, -1, SEEK_CUR);
            
            char* number = scanUntilSymbolic(input);
            if (!certifyNum(number)) {
                printf("Error: Invalid number (%s) detected.\nProgram terminated\n", number);
                exit(1);
            }
            
            printf("%d %s ", 3, number);
            fprintf(output, "%s %d", number, 3);
            fprintf(output2, "%d %s ", 3, number);
        }

        // Tokenize keywords and identifiers
        else if (verifyLet(curr)) {
            fseek(input, -1, SEEK_CUR);
            
            char* token = scanUntilSymbolic(input);
            
            // Tokenize keywords
            if (strcmp(token, "odd") == 0) {
                fprintf(output, "%s %d ", token, 8);
                printf("%d ",  8);
                fprintf(output2, "%d ", 8);
            }
            else if (strcmp(token, "begin") == 0) {
                fprintf(output, "%s %d ", token, 21);
                printf("%d ",  21);
                fprintf(output2, "%d ", 21);
            }
            else if (strcmp(token, "end") == 0) {
                fprintf(output, "%s %d ", token, 22);
                printf("%d ",  22);
                fprintf(output2, "%d ", 22);
            }
            else if (strcmp(token, "if") == 0) {
                fprintf(output, "%s %d ", token, 23);
                printf("%d ",  23);
                fprintf(output2, "%d ", 23);
            }
            else if (strcmp(token, "then") == 0) {
                fprintf(output, "%s %d ", token, 24);
                printf("%d ",  24);
                fprintf(output2, "%d ", 24);
            }
            else if (strcmp(token, "while") == 0) {
                fprintf(output, "%s %d ", token, 25);
                printf("%d ",  25);
                fprintf(output2, "%d ", 25);
            }
            else if (strcmp(token, "do") == 0) {
                fprintf(output, "%s %d ", token, 26);
                printf("%d ",  26);
                fprintf(output2, "%d ", 26);
            }
            else if (strcmp(token, "call") == 0) {
                fprintf(output, "%s %d ", token, 27);
                printf("%d ",  27);
                fprintf(output2, "%d ", 27);
            }
            else if (strcmp(token, "const") == 0) {
                fprintf(output, "%s %d ", token, 28);
                printf("%d ", 28);
                fprintf(output2, "%d ", 28);
            }
            else if (strcmp(token, "var") == 0) {
                fprintf(output, "%s %d ", token, 29);
                printf("%d ",  29);
                fprintf(output2, "%d ", 29);
            }
            else if (strcmp(token, "procedure") == 0) {
                fprintf(output, "%s %d ", token, 30);
                printf("%d ", 30);
                fprintf(output2, "%d ", 30);
            }
            else if (strcmp(token, "write") == 0) {
                fprintf(output, "%s %d ", token, 31);
                printf("%d ",  31);
                fprintf(output2, "%d ", 31);
            }
            else if (strcmp(token, "read") == 0) {
                fprintf(output, "%s %d ", token, 32);
                printf("%d ",  32);
                fprintf(output2, "%d ", 32);
            }
            else if (strcmp(token, "else") == 0) {
                fprintf(output, "%s %d ", token, 33);
                printf("%d ",  33);
                fprintf(output2, "%d ", 33);
            } 

            // Tokenize identifiers
            else {
                if (!certifyIdent(token)) {
                    printf("Error: Invalid ident (%s) detected.\nProgram terminated\n", token);
                    exit(1);
                }
                fprintf(output, "%s %d ", token, 2);
                printf("%d %s ", 2, token);
                fprintf(output2, "%d %s ", 2, token);
            }
        }
        else {
            printf("Error: Invalid token (%c) detected.\nProgram Terminated\n", curr);
            exit(1);
        }
    }

    printf("\n\n///////////\n");
    
    fclose(input); // Close the input file
    fclose(output); // Close the output file
    fclose(output2); //Close the second output file
}


///////////////////////////////////////////
///////////////////////////////////////////

void FileDetails(char* header, char* fileName) {
    // Initialize file access. Terminate the program if the file is unavailable.
    FILE* a3 = openFile(fileName, "r");
    // Display the header
    printf("%s\n", header);
    int i;
    for (i = 0; i < strlen(header); i++) {
        printf("-");
    }
    printf("\n");
    char* first;
    while (fgets(first, 256, a3)) {
        printf("%s", first);
    }
    fclose(a3);
}

// Function to display token catalog
void TokenCatalog() {
    
    FILE* tList = openFile(OUTPUT_TOKENS, "r"); // Open the token list file for reading
    
    char symbol[100];
    int data; 
    printf("\n\nLex Table:\n\n");
    printf("Lexeme       Token Type\n");
    
    // Read tokens and their corresponding values from the file until end of file is reached
    while (fscanf(tList, "%s %d ", symbol, &data) != EOF) {
        printf("%-13s%d\n", symbol, data); // Display token and its value
    }
    
    fclose(tList);
}

// Function to open a file with the specified mode
FILE* openFile(char* fileName, char* mode) {
    FILE* file;
    
    // Attempt to open the file with the specified mode
    file = fopen(fileName, mode);
    
    // Check if the file opening was successful
    if (file == NULL) {
        printf("[ERR] Failed to open file %s\n", fileName);
        exit(1);
    }
    
    return file;
}


// Function to scan characters from a file until a symbolic character is encountered
char* scanUntilSymbolic(FILE* file) {
    char c; 
    char* ch = malloc(sizeof(char)); // Allocate memory for the resulting string
    
    // Loop through the file until encountering the end of file
    while (fscanf(file, "%c", &c) != EOF) {
        if (!(verifyNum(c) || verifyLet(c))) {
            fseek(file, -1, SEEK_CUR); // Move the file pointer back one position
            break;
        }
        ch = attachChar(ch, c); // Append the character to the resulting string
    }
    
    return ch;
}


// Function to append a character to a string
char* attachChar(char* ch, char c) {
    // Allocate memory for the resulting string, considering the original string and the appended character
    char* res = malloc(sizeof(char) * (strlen(ch) + 1));
    
    // Format the resulting string by appending the character to the original string
    sprintf(res, "%s%c", ch, c);
    
    return res;
}


int verifyNum(char c) {
    return '0' <= c && c <= '9';
}

int verifyLet(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

int certifyNum(char* NUM) {
    int i;
    int size = strlen(NUM);
    if (size == 0) {
        return 0;
    }
    for (i = 0; i < size; i++) {
        if (!verifyNum(NUM[i])) {
            return 0;
        }
    }
    return toInt(NUM) <= MAX_NUMERIC;
}

// Function to convert a string of digits to an integer
int toInt(char* NUM) {
    int a4 = 0; 
    int i; 
    
    // Loop through the characters in the string until reaching the end or the maximum allowed integer value
    for (i = 0; i < strlen(NUM) && a4 <= MAX_NUMERIC; i++) {
        a4 *= 10; // Multiply the current result by 10 to shift digits left
        a4 += NUM[i] - '0'; // Add the numerical value of the current character to the result
    }
    
    return a4; 
}


int certifyIdent(char* ID) {
    int i;
    int size = strlen(ID);
    // Verify initial character is alphabetic
    if (!verifyLet(ID[0])) {
        return 0;
    }
    // Verify size
    if (size > MAX_IDENTIFIER) {
        return 0;
    }
    // Ensure that all other components consist of digits or letters.
    for (i = 1; i < size; i++) {
        if (!(verifyNum(ID[i]) || verifyLet(ID[i]))) {
            return 0;
        }
    }
    return 1;
}
