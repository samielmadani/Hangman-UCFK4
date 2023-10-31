#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

/* store pacer frequency as a static */
void get_pacer_frequency(uint16_t freq);

/* render a char on the dot matrix */
void mat_display_character(char character);

/* display current alphabet character */
void render_alphabet(void);

/* display guessing screen */
void render_hidden_word(void);

/* animate through a string at 5Hz per char */
void animate_frames(char* string, uint8_t size, uint8_t num_repeats, uint16_t animation_frequency);

#endif
