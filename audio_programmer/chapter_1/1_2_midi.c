/* Calculate the frequency of a midi note from a user's input. P.69,76. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char* notes[] = {"C", "Db", "D", "Eb",
                 "E", "F", "Gb", "G",
                 "Ab", "A", "Bb", "B"};

int main(int argc, char* argv[]) {
    double semitone_ratio = pow(2, 1.0/12.0);
    double frequency, fracmidi;
    double c0; /* for frequency of MIDI note 0 */
    double c5; /* for frequency of middle C */
    int midi_note;

	if (argc != 3) {
		printf("usage: %s MIDINOTE FREQUENCY\n", argv[0]);
		printf("├─ MIDINOTE range: 0-127\n");
		printf("└─ FREQUENCY range: 20-20000\n");
		return 1;
	}

    c5 = 220.0 * pow(semitone_ratio, 3.0); /* Frequency of middle C, three semitone above low A = 220hz */
    c0 = c5 * pow(0.5, 5.0); /* Calculate frequency of c0, 5 octives below middle C */
	
	midi_note = atoi(argv[1]);
    frequency = c0 * pow(semitone_ratio, (double) midi_note);
    printf("MIDI note %d is %s, the frequency is %f.\n", midi_note, notes[midi_note%12], frequency);

    /* REVERSE UNO CARD */
    /* find nearset MIDI note to a given frequency in Hz */
    frequency = atoi(argv[2]);
    fracmidi = log(frequency / c0) / log(semitone_ratio); /* use the log rule */
    midi_note = (int) (fracmidi + 0.5);
    printf("The nearest MIDI note to the frequency %d is %d, which is %s.\n",
           (int) frequency, midi_note, notes[midi_note%12]); 

    return 0;
}
