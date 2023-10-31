/** @file    game.c
    @author  M. Croucher (mcr93) and S. Elmadani (sae53)
    @date    5 Oct 2021

    @defgroup Main game code for Group_234's ENCE260 project, Hangman
*/

#include <stdint.h>

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "led.h"
#include "button.h"

#include "font5x7_1.h"
#include "text_display.h"
#include "words.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10

int8_t target_char;
int8_t target_word;
int8_t current_word_length;
int8_t lives;
int8_t current_screen;
int8_t display_word_len;

int8_t guessed_chars[ALPHABET_LENGTH];
int8_t hidden_word[MAX_WORD_LEN];
char current_word[MAX_WORD_LEN];

/* initialise some variables and choose the word before game starts */
void hangman_init(void)
{
	lives = 6;
	current_screen = 0;
	display_word_len = 0;
	
	/* wait for button press to start game - randomise start word from clock */
	mat_display_character('&');
	int8_t wait_for_start = 0;
	int8_t random_number = 0;
	while (wait_for_start == 0) {
		tinygl_update();
		pacer_wait();
		navswitch_update();
		
		random_number++;
		if (random_number >= NUM_WORDS) {
			random_number = 0;
		}
		
		if (navswitch_push_event_p(4)) {
			wait_for_start = 1;
		}
	}
	
	/* initialise guessed char array to all '0's */
	for (int8_t i = 0; i < ALPHABET_LENGTH; i++) {
		guessed_chars[i] = 0;
	}
	
	generate_word(random_number);
	animate_frames("&%$#\"!", 6, 1, 5);
	
	/* show the length of the word */
	char life_count[2] = {current_word_length + '0', ' '};
	animate_frames(life_count, 2, 3, 5);
}

/* process a player's guess */
void guess_char(void)
{
	int8_t valid_guess = 0;
	for (int8_t i = 0; i < current_word_length; i++) { //check if guess is a valid word
		if (alphabet[target_char] == current_word[i]) {
			valid_guess = 1;
		}
	}
	if (valid_guess == 0) { //invalid guess
		if (lives == 0) { //out of lives. game lost
			animate_frames("( ", 2, 4, 5);
			animate_frames(current_word, current_word_length, 1, 2);
			hangman_init();
		} else {
			lives--;
			char animation_string[2] = {('&'-lives), ('&'-lives-1)};
			animate_frames(animation_string, 2, 2, 5); //animate a life being deducted
			guessed_chars[target_char] = 1;
		}
	} else { //valid guess
		int8_t word_complete = 1;
		for (int8_t i = 0; i < current_word_length; i++) {
			if (alphabet[target_char] == current_word[i]) {
				hidden_word[i] = 1;
			} else if (hidden_word[i] == 0) {
				word_complete = 0;
			}
		}
		if (word_complete == 1) { //all chars are guessed correctly, win game
			animate_frames(") ", 2, 4, 5);
			animate_frames(current_word, current_word_length, 1, 3);
			hangman_init();
		} else {
			char animation_string[2] = {alphabet[target_char], '_'};
			animate_frames(animation_string, 2, 4, 5); //animate a char being guessed
			guessed_chars[target_char] = 1;
		}
	}
}

/* process a player's navswitch input */
void process_button_input(void)
{
	if (current_screen == 0) {
		display_word_len = ALPHABET_LENGTH;
	} else {
		display_word_len = current_word_length + 1;
	}
	
	
    if (navswitch_push_event_p(1)) { //right on navswitch
		target_char++;
		if (target_char == display_word_len) {
			target_char = 0;
		}
	}
    if (navswitch_push_event_p(3) ) { //left on navswitch
		target_char--;
		if (target_char < 0) {
			target_char = display_word_len - 1;
		}
	}
	
    if (navswitch_push_event_p(0)) { //up on navswitch
		target_char = 0;
		current_screen ^= 1;
	}
	
	if (navswitch_push_event_p(2)) { //down on navswitch
		target_char = 0;
		current_screen ^= 1;
	}
	
	if (navswitch_push_event_p(4) && current_screen == 0) { //guess a character if player is on alphabet screen
		if (guessed_chars[target_char] == 0) {
			guess_char();
		}
	}
}

/* main game block */
int main (void)
{
	/* initialise ucfk4 */
    system_init();
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
	navswitch_init();
    pacer_init(PACER_RATE);
	get_pacer_frequency(PACER_RATE);
	
	led_init();
	button_init();
	hangman_init();
	
	/* main loop */
	while(1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();
		button_update();
		
		process_button_input();
		
		if (button_down_p(0)) { //render correct screen
			mat_display_character('&' - lives);
		} else if (current_screen == 0){
			render_alphabet();
			led_set(LED1, 0);
		} else {
			render_hidden_word();
			led_set(LED1, 1);
		}
    }
    return 0;
}
