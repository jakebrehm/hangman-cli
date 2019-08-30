#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char play_again();

int main() {

    // Generate a seed for the random number generator
    srand(time(NULL));

    // Define a list of words
    char words[][16] = {
        "red",
        "green",
        "blue",
        "orange",
        "purple"
    };
    // Determine the number of possible words
    int numberOfWords = sizeof(words) / sizeof(words[0]);

    // Initialize the terminate variable
    int terminate = 0;

    // Define list containing all valid guesses (the alphabet)
    char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
                         'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                         'w', 'x', 'y', 'z'};


    while ( 1 ) {

        // Initialize the player's current guess
        char guess;

        // Information about the current game
        int limbs = 5;              // The amount of limbs (lives) remaining
        int score = 0;              // The player's current score
        int before = 0;             // What the score was before the current guess

        // Generate a random index used to select a word
        int r = rand() % numberOfWords;
        // Store the randomly selected word in its own variable
        char word[16];
        strcpy(word, words[r]);
        // Get the length of the word
        int total = strlen(word);

        printf("The random number is: %d\n", r);
        printf("The word is: %s\n", word);
        printf("Its length is: %d\n", total);

        // Make an array of zeros of the same length as the word
        int body[total];
        memset(body, 0, sizeof(body));

        // Copy the alphabet list for use in the current game
        char available[26];
        strcpy(available, alphabet);

        // Let the player know the game has begun
        printf("\n~~~~~HANGMAN~~~~~\n");
        printf("The word has %d letters: ", total);
        for ( int i = 0 ; i < total ; i++ ) {
            printf("-");
        }
        printf(".\n");

        // Main game loop
        while ( score < total ) {

            printf("\n");

            // Have the player guess a letter
            printf("Guess a letter: ");
            scanf("%c", &guess);
            // Only take the first letter as a guess
            while ( getchar() != '\n' ) { ; }

            // If the player pressed the <enter> key twice, quit the game
            if ( guess == '\n' || guess == '0' ) {
                terminate = 1;
                break;
            }

            /************************************************************
             * Determine if the letter has been guessed before; if the
             * letter has not been guessed before but is in the target
             * word, increment the player's score accordingly.
             ************************************************************/
            // New guess: 0 -> already guessed, 1 -> new guess
            int new_guess = 0;
            // Incorrect guess: 0 -> already guessed, 1 -> correct, 2 -> incorrect
            int incorrect_guess = 0;
            for ( int i = 0 ; i < 26 ; i++ ) {
                if ( guess == available[i] && available[i] != 0 ) {
                    available[i] = 0;
                    new_guess = 1;
                    incorrect_guess = 2;
                    for ( int j = 0 ; j < total ; j++ ) {
                        if ( guess == word[j] ) {
                            body[j] = 1;
                            incorrect_guess = 1;
                            score++;
                        }
                    }
                }
            }
            // Do nothing if the player reguesses a letter
            if ( new_guess == 0 ) {
                printf("Try again - <%c> has been guessed already.\n", guess);
                continue;
            }
            // Tell the player if they were correct, and how many limbs they have left
            if ( incorrect_guess == 1 ) {
                printf("Correct - <%c> was a great guess!\n", guess);
            } else if ( incorrect_guess == 2 ) {
                printf("Sorry, your guess of <%c> was incorrect.\n", guess);
                limbs--;
                printf("You have %d limbs remaining.\n", limbs);
                // Break from the while loop if the player has no more limbs
                if ( limbs < 1 ) {
                    terminate = 2;
                    break;
                }
            }

            // Print the player's current score
            printf("Your score is currently: %d\n", score);
            // Print the status of the game (which letters have been guessed)
            printf("Word status: ");
            for ( int i = 0; i < total; i++ ) {
                if ( body[i] == 0 ) {
                    printf("-");
                } else {
                    printf("%c", word[i]);
                }
            }
            printf("\n");

        }

        // Write a message to the player depending on the termination value
        printf("\n");
        if ( terminate == 0 ) {
            printf("Congratulations, you win!\n");
        } else if ( terminate == 1 ) {
            // printf("The player has exited the program.\n");
            break;
        } else if ( terminate == 2 ) {
            printf("Sorry, you have run out of limbs.\n");
            printf("The word was <%s>.\n", word);
        }

        // Ask the user if they would like to play again
        char choice = play_again();
        while ( choice != 'y' && choice != 'n' ) {
            choice = play_again();
        }
        // // Either restart or exit the game
        if ( choice == 'y' ) {
            continue;
        } else if ( choice == 'n' ) {
            break;
        }

    }

    printf("\n");
    printf("The player has exited the program.\n");

}

char play_again() {
    char choice;
    printf("\n");
    printf("Would you like to play again? (y/n): ");
    scanf("%c", &choice);
    while ( getchar() != '\n' ) { ; }
    return choice;
}