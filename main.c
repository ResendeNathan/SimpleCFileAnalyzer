#include <stdio.h>  // For input/outp (printf, fopen, fgets, fclose)
#include <string.h> // For strings manipulation (strcmp, strstr)
#include <stdlib.h> // For exit()

// Function to show the correct usage of the application.
void print_usage(){
    printf("\nUsage: \n");
    printf("  ./cli_utility -c <file>           -- Counts the number of lines in the file.\n");
    printf("  ./cli_utility -s <file> <word>    -- Searches for and counts occurrences of 'word' in the file.\n");
}


int main(int argc, char *argv[]){
    // Validates if there are enough arguments
    if (argc < 2){
        print_usage();
        return 1; // Returns 1 to indicate error
    }

    // Check the first argument (option)
    if (strcmp(argv[1], "-c") == 0){
        // Option to count the lines
        if (argc != 3){
            printf("Error: Option '-C' requires a file.\n");
            print_usage();
            return 1;
        }

        char *filename = argv[2];

        printf("Counting the lines in the file '%s'\n", filename);

        FILE *file = fopen(filename, "r"); // Open the file in read mode ("r")

        if (file == NULL){
            perror("\n\tError opening the file"); //perror prints an error message based on errno
            return 1;
        }

        int line_count = 0;
        char buffer[1024]; // Buffer to read each line.

        //Loop to read each line of the file
        while (fgets(buffer, sizeof(buffer), file) != NULL){
            line_count++;
        }

        fclose(file); //Closes the file

        printf("\n\tTotal of lines: %d\n", line_count);

    } else if (strcmp(argv[1], "-s") == 0){
        // Option to search the word
        if (argc != 4){
            printf("Error: Option '-s' requires a file and a word.\n ");
            print_usage();
            return 1;
        }

        char *filename = argv[2];
        char *search_word = argv[3];

        printf("Searching the word '%s' in the file '%s'\n", search_word, filename);
        
        FILE *file = fopen(filename, "r");

        if (file == NULL){
            perror("\n\tError opening the file");
            return 1;
        }

        int word_count = 0;
        char buffer[1024]; //Buffer to read each line

        while(fgets(buffer, sizeof(buffer), file) != NULL){
            // strstr returns a pointer to the first occurrence of the substring, or NULL if not found
            char *ptr = buffer;

            while ((ptr = strstr(ptr, search_word)) != NULL){
                word_count++;
                ptr += strlen(search_word); // Move the pointer after the word found to avoid repeated counts on the same occurrence
            }
        }

        fclose(file);

        printf("\n\tThe word '%s' was found %d times.\n", search_word, word_count);
        
    } else {
        printf("Invalid Option: '%s'\n", argv[1]);
        print_usage;
        return 1;
    }

    return 0; // Retruns 0 to indicate success
}
