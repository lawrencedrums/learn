/* Exercises from chapter 1.4. P.94. */

/* Exercise 1.4.1. Convert prev programs to take input from CLI */

/* Exercise 1.4.2. Add a usage message to prev programs */

/* Exercise 1.4.3-1.4.4. Experimental exercises */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int is_digit_only(char* string, char* arg_name) {
	for (int i = 0; i < strlen(string); i++) {
		if (!isdigit(string[i])) {
			printf("%s only accepts integer value.\n", arg_name);
			return 0;
		}
	} 
	return 1; // return 1 for true if string contains only digit
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("usage: %s MIDINOTE ROOT_A TONES\n", argv[0]);
		printf("├─ MIDINOTE: 0-127\n");
		printf("├─ ROOT_A: 415, 435, 440\n");
		printf("└─ TONES: 12, 19, 24\n");
		return 1;
	}

	double semitone_ratio, c0, c5, frequency, tones;

	if (!is_digit_only(argv[1], "MIDI note")) {
		return 1;
	}
	if (!is_digit_only(argv[2], "Root A")) {
		return 1;
	}
	if (!is_digit_only(argv[3], "Tones")) {
		return 1;
	}

	int midi_note = atoi(argv[1]);
	if (midi_note < 0 || midi_note > 127) {
		printf("MIDI input out of range (0-127).\n");
		return 1;
	}

	int root_a = atoi(argv[2]);
	if (root_a == 415 || root_a == 435 || root_a == 440) {
		;
	} else {
		printf("Root A not recognised (415, 435, or 440).\n");
		return 1;
	}

	tones = atof(argv[3]);
	if (tones == 12 || tones == 19 || tones == 24) {
		;
	} else {
		printf("Tones not recognised (12, 19, or 24).\n");
		return 1;
	}

	semitone_ratio = pow(2, 1.0/tones);
	c5 = root_a * pow(semitone_ratio, 3);
	c0 = c5 * pow(0.5, 5);
	frequency = c0 * pow(semitone_ratio, midi_note);

	printf("With Root A of %d and %d tones equal temperament, "
           "MIDI note %d has frequency %f.\n",
		   root_a, (int) tones, midi_note, frequency);

	return 0;
}

