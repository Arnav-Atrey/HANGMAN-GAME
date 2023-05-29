#include <stdio.h>
//#include <conio.h> // helps in accessing user defined func like getch
//#include <curses.h> // conio.h is Windows only, curses.h is for MacOS - OSX
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// helper macros
#define ARRAY_SIZE(x) ( sizeof(x) / sizeof((x)[0]) )
#define FALSE 0
#define TRUE 1
#define DEBUG FALSE

// program specific macros
#define MAX_ATTEMPTS 6
#define UNDERSCORE '_'


// function to print the hangman progress based on attempt number
void print_hangman(int attempt) {
    switch (attempt) {
        case 6 :
            printf("\n");
            printf("  _______\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("__|_________\n\n");
            break;

        case 5 :
            printf("\n");
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("__|_________\n\n");
            break;

        case 4 :
            printf("\n");
            printf("  _______\n");
            printf("  |/   | \n");
            printf("  |    O \n");
            printf("  |    |\n");
            printf("  |    |\n");
            printf("  |\n");
            printf("__|_________\n\n");
            break;

        case 3 :
            printf("\n");
            printf("  _______\n");
            printf("  |/   | \n");
            printf("  |    O \n");
            printf("  |   /|\n");
            printf("  |    |\n");
            printf("  |\n");
            printf("__|_________\n\n");
            break;

        case 2 :
            printf("\n");
            printf("  _______\n");
            printf("  |/   | \n");
            printf("  |    O \n");
            printf("  |   /|\\\n");
            printf("  |    | \n");
            printf("  |     \n");
            printf("__|_________\n\n");
            break;

        case 1 :
            printf("\n");
            printf("  _______\n");
            printf("  |/   | \n");
            printf("  |    O \n");
            printf("  |   /|\\\n");
            printf("  |    | \n");
            printf("  |   /\n");
            printf("__|_________\n\n");
            break;
        case 0 :
            //exit
            printf("\n");
            printf("  _______\n");
            printf("  |/   | \n");
            printf("  |    X \n");
            printf("  |   /|\\\n");
            printf("  |    | \n");
            printf("  |   / \\\n");
            printf("__|_________\n\n");
            break;
    }
}

// function to print instructions to the game
void print_instructions() {

    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t___________________________________________________\n");
    printf("\t\t| #   #    #    #   #   ####  #   #    #    #   # |\n");
    printf("\t\t| #   #   # #   ##  #  #      ## ##   # #   ##  # |\n");
    printf("\t\t| #####  #####  # # #  #  ##  # # #  #####  # # # |\n");
    printf("\t\t| #   #  #   #  #  ##  #   #  #   #  #   #  #  ## |\n");
    printf("\t\t| #   #  #   #  #   #   ###   #   #  #   #  #   # |\n");
    printf("\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\n");

    printf("\n\n\n\t\t =================INSTRUCTIONS=============");
    printf("\n   1: HANGMAN IS THE GAME WHERE YOU HAVE TO GUESS A WORD.");
    printf("\n   2: YOU WILL HAVE TO GUESS THE WORD BY GUESSING THE LETTERS OF THE WORD.");
    printf("\n   3: AN INCORRECT GUESS REDUCES NUMBER OF CHANCES BY 1 .");
    printf("\n   4: A CORRECT GUESS FILLS THE RESPECTIVE BLANKS AND NO OF CHANCES REMAINS SAME");
    printf("\n   5: GUESS THE WORD AND SAVE THE MAN OR HE WILL BE HANGED!!!!!!\n\n");
}


int main(int argc, char** argv) {
    // reference words for the hangman game
	char reference_words[][100] = {"integration","engineer","computer","examination","motivation"};
    int num_of_words = ARRAY_SIZE(reference_words); // number of words to choose from to initialize the game

	int i; // used for array traversal
	int remaining_attempts = MAX_ATTEMPTS; // variable to track the number of attempts remaining
	int correctly_guessed_chars = 0; // to track number of correctly guessed characters

	int is_correct_guess = FALSE; // flag to track if the user attempt was a correct guess
    int is_repeated = FALSE; // flag to check if the user re-entered a character that was already tried

    char wrong[26] = ""; // char array to keep track of wrong characters (max size is 26 since there are only 26 alphabets user can enter)
	char user_input; // variable to read user input when they play the game

    // print instructions to the game
	print_instructions();

    // Initialize the game with a start word
    // User can start the game by entering a random positive integer on command line to choose the word
    // If user does not enter the number we choose a random word from reference_words
    int num;
    // User entered a random number on command line
    if (argc > 1) { // argv is an array of strings argc is no of inputs
        //argv[0] is the program name
        //atoi = ascii to int
        num = atoi(argv[1]);
        if (num < 0) {
            num = num * -1;
        }
    }
    // user has not entered a number, choose a random number
    else {
        num = rand();
    }

    int word_index = num % num_of_words; // to make sure word_index never exceeds num_of_words we do a modulo
    char* word = reference_words[word_index];
    int word_len = strlen(word);

    // print variables when DEBUG is set
    /*if (DEBUG) {
        printf("\n\nChosen word::: %s ::: at index %d ::: ", word, word_index);
        printf("\nword_len %d\n", word_len);
    }*/

	char intermediate_output[word_len]; // array to hold the intermediate words as the user plays the game
    int len=0;//to count the number of letters in  the guess word
    // to print the initial blanks
	for(i = 0; i < word_len; ++i) {
	    printf("%c ", UNDERSCORE);
	    intermediate_output[i] = UNDERSCORE; // initialize intermediate_output with UNDERSCORES
        len++;
    }
    printf("The length of the word is: %d",len);//tells user no of letters in the array

	// Play the game until the user exhausts all attempts
	while (remaining_attempts > 0) {
		/*if (DEBUG) {
		    // print all variables on every iteration if DEBUG is set
		    printf("\n\nwrong array ::: %s", wrong);
		    printf("\nintermeditate_output ::: %s", intermediate_output);
		    printf("\nis_correct_guess flag ::: %d", is_correct_guess);
		    printf("\nis_repeated flag ::: %d", is_correct_guess);
		    printf("\nRemaining attempts ::: %d", remaining_attempts);
        }*/

		printf("\n\n\n\t Enter a char:    ");

		do {
		    scanf("%c", &user_input);
		} while ( getchar() != '\n'); // enter should not be taken as a character

		// Only alphabets are allowed in hangman game
		if(isalpha(user_input) == FALSE) {
		    printf("Please enter an alphabet (numbers and special characters not accepted)");
		}
        else {
            printf("\t\t\t\t");
            // convert the input to lower case
            char input_in_lower = tolower(user_input);

            // first check if this letter is already encountered
            // repeated letters can be of two types
            // 1. Repeated letters that are correct
            // 2. Repeated letters that are wrong

            // Handle repeated letter, but it is correct
            int seen_correct_len = strlen(intermediate_output);
            for (i = 0; i < seen_correct_len ; ++i) {
                if (input_in_lower == intermediate_output[i]) {
                    printf("This letter already exists. Please type another letter.\n\n");
                    is_repeated = TRUE;
                    break;
                }
            }

            // Handle repeated letter, but it is wrong
            int seen_wrong_len = strlen(wrong);
            for (i = 0; i < seen_wrong_len ; ++i) {
                if (input_in_lower == wrong[i]) {
                    printf("Letter %c is incorrect and was previously guessed. Please try a different letter\n\n", user_input);
                    is_repeated = TRUE;
                    break;
                }
            }

            if (is_repeated) {
                is_repeated = FALSE; // reset the is_repeated flag
                // do not penalize the user for this guess (hence not incrementing count)
                continue; // continue taking the input for different try
            }

            // If we are here, we are seeing a character for the very first time
            for(i = 0; i < word_len; ++i) {
                // user entered a correct letter (we found a match)
                if (input_in_lower == word[i]) {
                    intermediate_output[i] = input_in_lower;  // update the intermediate_output with the correctly guessed char
                    printf("%c\t ", toupper(intermediate_output[i])); // print uppercase when printing to user
                    is_correct_guess = TRUE; // set the is_correctly_guessed_chars flag
                    correctly_guessed_chars++; // increment the number of correctly guessed characters
                }
                else {
                    printf("%c\t ", toupper(intermediate_output[i])); // print a blank for user to know it needs to be guessed
                }
            }

            printf("\n\n\t****************************************************************************************\t\t\t\n");

            if(is_correct_guess == TRUE) {
                printf("\n\t\t CORRECT LETTER!!");
                // if num of correctly guessed chars is equal to the length of the word, it means user got the word and WON the game
                if(correctly_guessed_chars == word_len) {
                    break;
                }
                // user still has other characters to guess, game needs to continue
                else {
                    printf("\n\n\t\t (CHANCES LEFT: %d)", remaining_attempts);
                    print_hangman(remaining_attempts);
                    is_correct_guess = FALSE; // reset to check if letter is right or wrong in the next iteration of the loop
                }
            }
            else {
                // We did not find a match - record the input as wrong character guessed
                strncat(wrong, &input_in_lower, 1);
                printf("\n\n\t\t%c IS A WRONG GUESS", user_input);
                //if (DEBUG) {
                    printf("\n\n\t\tThe wrong guesses are: %s", wrong);
                //}
                remaining_attempts = remaining_attempts - 1; // chances getting reduced
                print_hangman(remaining_attempts);
                printf("\n\n\t\t (YOU HAVE %d GUESSES REMAINING)", remaining_attempts);
            }
		}
	}

	if(correctly_guessed_chars == word_len) {
	    printf("\n\n\n\t YOU WIN :)!!   (PRESS ANY KEY TO CONTINUE)");
	}
	else {
	    printf("\n\n\t\t  YOU LOSE. :( \n\n");
		printf("\n\n\t\t  The correct word is: %s\n\n", word);
		printf("\n\n\t\t SORRY  U R HANGED :(    (PRESS ANY KEY TO CONTINUE)");
	}
	getchar();

	return 0; // Program ran successfully
}