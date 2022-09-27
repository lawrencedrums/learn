/* Exercises from Chapter 1.2 of The Audio Programmer book. */
#include <stdio.h>
#include <math.h>

/* Exersice 1.2.1. P.76. */
int byte_reporter() {
	int int_obj;
	char char_obj;
	short short_obj;
	long long_obj;
	float float_obj;
	double double_obj;

	printf("The size in byte of each data types are: \n");
	printf("int:    %lu\n", sizeof(int_obj));
	printf("char:   %lu\n", sizeof(char_obj));
    printf("short:  %lu\n", sizeof(short_obj));
    printf("long:   %lu\n", sizeof(long_obj));
    printf("float:  %lu\n", sizeof(float_obj));
    printf("double: %lu\n", sizeof(double_obj));
	printf("\n");

	return 0;
}

/* Exercise 1.2.2. P.76.
 * This doesn't work because we are casting fracsamp to short first, which results in 0.
 * One way to solve this is: samp = (short) (fracsamp * 32767);
 */
int convert_fp_to_16int() {
	short samp;
	float fracsamp = 0.87;

	samp = (short) fracsamp * 32767;
	printf("%hd\n", samp);
	printf("\n");

	return 0;
}

/* Exercise 1.2.3. P.77. */
/* Subsituting with literal values loses lots of readability,
 * adding confusion as to how the values were calcuted,
 * and makes the statement harder to maintain and expand.
 */

/* Exercise 1.2.4. P.77. */
/* Modified listing 1.2. Avoid reliance on the compiler's automatic type promotion */

/* Exercise 1.2.5. P.77. */
int lengths_of_strings() {
	double string_ratio = pow(2.0, 1.0/12.0);
	double c4 = 660.0;
	
	printf("The lengths of string for each semitone between C4 and C5 are: \n");
	for (int i = 0; i < 13; i++) {
		printf("%.2f ", c4 / pow(string_ratio, i));
	}
	printf("\n\n");
	
	return 0; 	
}

/* Exercise 1.2.5-1.2.6. P.77. */
int freq2midi() {
	double semitone_ratio = pow(2.0, 1.0/12.0);
	double freq = 430;
	double c0 = 220.0 * pow(semitone_ratio, 3.0) * pow(0.5, 5.0);
	double fracmidi = log(freq / c0) / log(semitone_ratio);

	int midi_note_upper = (int) (fracmidi + 0.5);
	int midi_note_lower = (int) (fracmidi - 0.5);
	double upper_freq = c0 * pow(semitone_ratio, (double) midi_note_upper);
	double lower_freq = c0 * pow(semitone_ratio, (double) midi_note_lower);
	double upper_lower_diff = upper_freq - lower_freq;
	
	if ((upper_freq - freq) < (freq - lower_freq)) {
		printf("%f%%\n", -((upper_freq - freq) / upper_lower_diff) * 100);
	} else { /* if the estimate is closer to the lower guess */
		printf("%f%%\n", ((freq - lower_freq) / upper_lower_diff) * 100);
	}
	printf("\n");

	return 0;
}

int main() {
	byte_reporter();
	convert_fp_to_16int();
	lengths_of_strings();
	freq2midi();

	return 0;
}

