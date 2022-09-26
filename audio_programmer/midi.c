/* Calculate the frequency of a midi note from a user's input. */

#include <stdio.h>
#include <math.h>

char* notes[] = {"C", "Db", "D", "Eb",
                 "E", "F", "Gb", "G",
                 "Ab", "A", "Bb", "B"};

int main() {
    double semitone_ratio = pow(2, 1/12.0);
    double frequency;
    double c0; /* for frequency of MIDI note 0 */
    double c5; /* for frequency of middle C */
    int midi_input;

    do {
	printf("MIDI note (0-127): ");
	scanf("%d", &midi_input);
    } while (midi_input > 127 || midi_input < 0);

    /* printf("MIDI note: ");
    * scanf("%d", &midi_input);
    *
    * Handle midi out of range
    * if (midi_input > 127 || midi_input < 0) {
    *     printf("MIDI note out of range (0-127).");
    *     return 1;
    * }
    */

    c5 = 220.0 * pow(semitone_ratio, 3); /* Frequency of middle C, three semitone above low A = 220hz */
    c0 = c5 * pow(0.5, 5); /* Calculate frequency of c0, 5 octives below middle C */

    frequency = c0 * pow(semitone_ratio, midi_input);
    printf("MIDI note %d is %s, the frequency is %f.\n", midi_input, notes[midi_input%12], frequency);

    return 0;
}
