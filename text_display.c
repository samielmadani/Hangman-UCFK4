/** @file    text_display.c
    @author  M. Croucher (mcr93) and S. Elmadani (sae53)
    @date    5 Oct 2021

    @defgroup Text Display module for the Hangman game
*/

#include <stdint.h>
#include "text_display.h"
#include "tinygl.h"
#include "display.h"
#include "pacer.h"

//external variables required for the functions in this module
extern int8_t lives;
extern char alphabet[];
extern int8_t guessed_chars[];
extern int8_t hidden_word[];
extern char current_word[];
extern int8_t target_char;
extern int8_t current_word_length;

static uint16_t pacer_frequency;

/* store pacer frequency as a static */
void get_pacer_frequency(uint16_t freq)
{
	pacer_frequency = freq;
}

/* render a char on the dot matrix */
void mat_display_character(char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text(buffer);
}

/* display current alphabet character */
void render_alphabet(void)
{
	if (guessed_chars[target_char] == 0) {
		mat_display_character(alphabet[target_char]);
	} else {
		mat_display_character('_');
	}
}

/* display guessing screen */
void render_hidden_word(void)
{
	if (hidden_word[target_char] == 0) {
		mat_display_character('_'); //unknown char
	} else if (hidden_word[target_char] == 1) {
		mat_display_character(current_word[target_char]); //correctly guessed char
	} else {
		mat_display_character(current_word_length + '0'); //display length of word
	}
}

/* animate through a string at a given frequency */
void animate_frames(char* string, uint8_t size, uint8_t num_repeats, uint16_t animation_frequency)
{
	for (int8_t i = 0; i < num_repeats; i++) {
		for (int8_t i = 0; i < size; i++)
		{
			mat_display_character(*(string + i));
			for (uint8_t j = 0; j < (pacer_frequency / animation_frequency); j++) {
				pacer_wait();
				tinygl_update();
			}
		}
	}
}