#ifndef WORDS_H
#define WORDS_H

#define NUM_WORDS 32
#define MAX_WORD_LEN 9
#define ALPHABET_LENGTH 26

char alphabet[ALPHABET_LENGTH];

char word_list[NUM_WORDS][MAX_WORD_LEN];

/* Select a random word from the predetermined list */
void generate_word(int8_t random_number);

/* return current state of characters as a string */
void stringify(char* current_word, uint8_t* guessed_chars, uint8_t length);

#endif
