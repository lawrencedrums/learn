/* Interactive version of 1_2_midi.c. Listing 1.3. P.87. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
	double c0, c5, semitone_ratio, freq;
	int midinote;

	semitone_ratio = pow(2.0, 1.0/12.0);
	c5 = 220.0 * pow(semitone_ratio, 3);
	c0 = c5 * pow(0.5, 5);

	if (argc != 2) {
		printf("usage: %s MIDINOTE\n", argv[0]);
		printf("└─ MIDINOTE range: 0-127\n");
		return 1;
	}

	midinote = atoi(argv[1]);
	if (midinote < 0 || midinote > 127) {
		printf("The input MIDI note %d is out of range (0-127).\n", midinote);
		return 1;
	}

	freq = c0 * pow(semitone_ratio, midinote);
	printf("MIDI note %d has the frequency %f.\n", midinote, freq);

	return 0;
}
