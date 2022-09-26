/* Calculate the frequency of a midi note from a user's input. */

#include <stdio.h>
#include <math.h>

char* notes[] = {"C", "Db", "D", "Eb",
                 "E", "F", "Gb", "G",
                 "Ab", "A", "Bb", "B"};

int main() {
    double semitone_ratio = pow(2, 1/12.0);
    double frequency, fracmidi;
    double c0; /* for frequency of MIDI note 0 */
    double c5; /* for frequency of middle C */
    int midi_note;

    do {
	printf("MIDI note (0-127): ");
	scanf("%d", &midi_note);
    } while (midi_note > 127 || midi_note < 0);

    /* printf("MIDI note: ");
    * scanf("%d", &midi_note);
    *
    * Handle midi out of range
    * if (midi_note > 127 || midi_note < 0) {
    *     printf("MIDI note out of range (0-127).");
    *     return 1;
    * }
    */

    c5 = 220.0 * pow(semitone_ratio, 3); /* Frequency of middle C, three semitone above low A = 220hz */
    c0 = c5 * pow(0.5, 5); /* Calculate frequency of c0, 5 octives below middle C */

    frequency = c0 * pow(semitone_ratio, midi_note);
    printf("MIDI note %d is %s, the frequency is %f.\n", midi_note, notes[midi_note%12], frequency);

    /* REVERSE UNO CARD */
    /* find nearset MIDI note to a given frequency in Hz */
    frequency = 400;
    fracmidi = log(frequency / c0) / log(semitone_ratio); /* use the log rule */
    midi_note = (int) (fracmidi + 0.5);
    printf("The nearest MIDI note to the frequency %f is %d, which is %s.\n", frequency, midi_note, notes[midi_note%12]); 

    return 0;
}
