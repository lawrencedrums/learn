/* Interactive version of 1_2_midi.c. Listing 1.3. P.87. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	double c0, c5, semitone_ratio, freq;
	int midinote;
	char message[256]; // holds the user's input

	semitone_ratio = pow(2.0, 1.0/12.0);
	c5 = 220.0 * pow(semitone_ratio, 3);
	c0 = c5 * pow(0.5, 5);

	printf("Enter MIDI note (0-127): ");
	if (gets(message) == NULL) { // handles input errors
		printf("Error reading the input.\n");
		return 1;
	}
	if (message[0] == '\0') { // handles empty input
		printf("Well alright then!\n");
		return 1;
	}

	midinote = atoi(message);
	if (midinote < 0 || midinote > 127) {
		printf("The input MIDI note %d is out of range (0-127).\n", midinote);
		return 1;
	}

	freq = c0 * pow(semitone_ratio, midinote);
	printf("MIDI note %d has the frequency %f.\n", midinote, freq);

	return 0;
}
