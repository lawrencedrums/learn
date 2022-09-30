/* Listing 1.5.3. P.107. */
/* Display E.T frequencies for an N-note octave, from a given MIDI note. */

/**
 * A octave jump corresponds to a frequency change by a factor of 2. 
 * Double for octave rise, half for octave fall. E.G. A4 = 440Hz, A3 = 220Hz, A5 = 880Hz.
 * Therefore in 12 tone E.T, 1 semitone rise corresponds to a frequency rise of 2^(1/12)
 * which is approx. 1.0594631. As such, in a scale with E.G. 18 notes the semitone ratio
 * can be calculated as 2^(1/18). This program uses this formula to print out a given
 * number of frequencies between a given MIDI note and the octave above.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("usage: %s notes midinote\n", argv[0]);
		printf("ranges ┬─ 0 <= notes <= 24\n");
		printf("       └─ 0 <= midinote <= 127\n");
		return 1;
	}
	
	int notes, midinote;
	double frequency, ratio, c0, c5;
	double intervals[25];

	notes = atoi(argv[1]);
	if (notes < 0 || notes > 24) {
		printf("Notes input out of range (0-24)\n");
		return 1;
	}

	midinote = atoi(argv[2]);
	if (midinote < 0 || midinote > 127) {
		printf("MIDI note out of range (0-127)\n");
		return 1;
	}

	/* calc 12 tone E.T semitone ratio */
	ratio = pow(2.0, 1.0/12.0);
	/* find middle C, which is 3 semitones above low A = 220 */
	c5 = 220.0 * pow(ratio, 3);
	/* find MIDI note 0, 5 octaves below middle C */ 
	c0 = c5 * pow(0.5, 5.0);
	frequency = c0 * pow(ratio, midinote);

	/* calc new ratio from notes and fill the frequency array */
	ratio = pow(2.0, 1.0/notes);
	for (int i = 0; i < notes+1; i++) {
		intervals[i] = frequency;
		frequency *= ratio;
	}

	for (int i = 0; i < notes+1; i++) {
		printf("%d: %.2f\n", i, intervals[i]);
	}
	
	return 0;
}
