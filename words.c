/** @file    text_display.c
    @author  M. Croucher (mcr93) and S. Elmadani (sae53)
    @date    19 Oct 2021

    @defgroup Words module for the Hangman game
*/

#include <stdint.h>
#include <string.h>
#include "words.h"

extern char current_word[];
extern int8_t current_word_length;
extern int8_t hidden_word[];
extern int8_t target_char;


char alphabet[ALPHABET_LENGTH] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char word_list[NUM_WORDS][MAX_WORD_LEN] = {
	"TIME",
	"YEAR",
	"PEOPLE",
	"WAY",
	"DAY",
	"MAN",
	"THING",
	"WOMAN",
	"LIFE",
	"CHILD",
	"WORLD",
	"SCHOOL",
	"STATE",
	"FAMILY",
	"STUDENT",
	"GROUP",
	"COUNTRY",
	"PROBLEM",
	"HAND",
	"PART",
	"PLACE",
	"CASE",
	"WEEK",
	"COMPANY",
	"SYSTEM",
	"PROGRAM",
	"QUESTION",
	"WORK",
	"GOVERN",
	"NUMBER",
	"NIGHT",
	"POINT"
};

/* Select a random word from the predetermined list */
void generate_word(int8_t random_number)
{
	strcpy(current_word, word_list[random_number]);
	current_word_length = strlen(current_word);
	target_char = 0;
	
	//initialise the guessed word with an array of 0's, terminated with a -1
	for (int8_t i = 0; i < current_word_length; i++) {
		hidden_word[i] = 0;
	}
	hidden_word[current_word_length] = -1;
}