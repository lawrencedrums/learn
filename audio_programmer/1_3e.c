/* Exercises from chapter 1.3. P88. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

/* Exercise 1.3.1. Adding comments to 1_3_midi.c. */

/* Exercise 1.3.2. Interactive version of freq2mini. */

/* Excerise 1.3.3. Add more defensive programming features to 1.3.2. */

int freq2mini() {
	int freq_input, closest_upper, closest_lower, closest_note, std_dev;
	char message[256];
	double c0, c5, semitone_ratio, fracmidi, upper_freq, lower_freq;
	char* notes[] = {"C", "Db", "D", "Eb",
					 "E", "F", "Gb", "G",
					 "Ab", "A", "Bb", "B"};
	
	printf("Enter frequency (20-20000): \n");
	if (gets(message) == NULL) {
		printf("Error reading the input.\n");
		return 1;
	}
	if (message[0] == '\0') {
		printf("Empty input. Exiting program.\n");
		return 1;
	}

	freq_input = atoi(message);
	if (freq_input == 0) {
		printf("DO NOT enter chars you mf.\n");
		return 1;
	}

	/* very naive way to defend against floating point number */
	for (int i = 0; i < sizeof(message); i++) {
		if (message[i] == '.') {
			printf("Please only enter decimal number 20-20000.\n");
			return 1;
		}
	}
	if (freq_input < 20 || freq_input > 20000) {
		printf("Frequency out of range! (20-20000).\n");
		return 1;
	}

	semitone_ratio = pow(2, 1.0/12.0);
	c5 = 220.0 * pow(semitone_ratio, 3);
	c0 = c5 * pow(0.5, 5);

	fracmidi = log(freq_input / c0) / log(semitone_ratio); // approx. of MIDI note
	closest_upper = (int) (fracmidi + 0.5);
	closest_lower = (int) (fracmidi - 0.5);
	upper_freq = c0 * pow(semitone_ratio, closest_upper);
	lower_freq = c0 * pow(semitone_ratio, closest_lower);

	/* Determine the closer note */
	closest_note = (upper_freq - freq_input) < (freq_input - lower_freq) ? closest_upper : closest_lower;
	
	/* Calculate standard deviation */
	if (closest_note == closest_upper) {
		std_dev = - (int) ((upper_freq - freq_input) / (upper_freq - lower_freq) * 100 + 1);
	} else {
		std_dev = (int) ((freq_input - lower_freq) / (upper_freq - lower_freq) * 100);
	}

	printf("Closest MIDI note to frequency %dHz is %s.\n",
		   freq_input, notes[closest_note % 12]);
	printf("With standard deviation %d%%.\n", std_dev);

	return 0;
}

int main() {
	freq2mini();

	return 0;
}

