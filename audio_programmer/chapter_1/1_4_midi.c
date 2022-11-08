/* Listing 1.4. P.93. */
/* 1.3 but take argument from CLI. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("This program converts MIDI note to frequency.\n");
		printf("usage: %s MIDINOTE\n", argv[0]);
		printf("└─ range: 0 <= MIDINOTE <= 127\n");
		return 0;
	}

	double c0, c5, semitone_ratio, frequency;
	int midi_note;

	semitone_ratio = pow(2, 1.0/12.0);
	c5 = 220.0 * pow(semitone_ratio, 3);
	c0 = c5 * pow(0.5, 5);

	for (int i = 0; i < strlen(argv[1]); i++) {
		if (!isdigit(argv[1][i])) {
			printf("Please only input interger.\n");
			return 1;
		}
	}

	midi_note = atoi(argv[1]);
	if (midi_note < 0 || midi_note > 127) {
		printf("Input MIDI note %d out of range (0-127).\n", midi_note);
		return 1;
	}

	frequency = c0 * pow(semitone_ratio, midi_note);
	printf("The frequency of MIDI note %d is %f.\n", midi_note, frequency);

	return 0;
}
