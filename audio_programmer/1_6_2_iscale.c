/* Listing 1.6.10. P.126. */
/* generate E.T. tables for N-note to octave ( N <= 24) */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* usage iscale [-m] [-i] N start_val [outfile.txt]
	-m : sets format of start_val as MIDI note
	-i : prints the calculated interval as well as the abs freq
	outfile : optional text filename for output data
*/

int main(int argc, char* argv[]) {
	int notes;
	int is_midi = 0;
	int write_interval = 0;
	int append_to_file = 0;
	int err = 0;
	double start_val, base_freq, ratio;
	FILE* fp;
	double intervals[25];
	int flags = 0;
	int argc_copy = argc;

	/* check first arg for flag option: argc at least 2 */
	while (argc > 1) {
		if (argv[1][0] == '-') {
			if (argv[1][1] == 'm') {
				is_midi = 1;
			} else if (argv[1][1] == 'i') {
				write_interval = 1;
			} else if (argv[1][1] == 'a') {
				append_to_file = 1;
			} else {
				printf("error: unrecognized option %s\n", argv[1]);
				return 1;
			}
			/* step up to next arg */
			argc--;
			argv++;
			flags++;
		} else {
			break;
		}
	}

	if (argc < 3) {
		printf("insufficient arguments\n");
		printf("usage: iscale [-m] [-i] [-a] N start_val [outfile.txt]\n");
		printf(" -m : set format of start_val as MIDI note\n");
		printf(" -i : prints the calculated interval "
			   "as well as the absolute frequency.\n");
		printf(" -a : append data to output text file with the same name.\n");
		printf(" N : number of notes to calculate in one octave. "
		       "0 <= N <= 24\n");
		printf(" start_val : the raw hertz value of the starting note. "
			   "start_val > 0.0\n");
		return 1;
	}
/* now read and check all arguments */
/* we now expect argv[1] to hold N and argv[2] start_val */
	notes = atoi(argv[1]);
	if (notes < 1 || notes > 24) {
		printf("error: N out of range (1-24).\n");
		return 1;
	}

	start_val = atof(argv[2]);
	if (is_midi) {
		if (start_val > 127.0) {
			printf("error: MIDI start_val must be <= 127.\n");
			return 1;
		}
		if (start_val < 0.0) {
			printf("error: MIDI start_val must be >= 0.0\n");
			return 1;
		}
	} else { /* it's freq: must be positive number */
		if (start_val <= 0.0) { /* check low limit */
			printf("error: frequency start_val must be positive.\n");
			return 1;
		}
	}

	/* check for optional filename */
	fp = NULL;
	if (argc == 4) {
		if (append_to_file) {
			fp = fopen(argv[3], "a");
		} else {
			fp = fopen(argv[3], "w");
		}

		if (fp == NULL) {
			printf("WARNING: unable to create file %s\n", argv[3]);
			perror("");
		}
	}

/* all params ready - fill array and write to file if created */
	/* find base freq, if val is MIDI */
	if (is_midi) {
		double c0, c5;
		/* find base MIDI note */
		ratio = pow(2.0, 1.0/12.0);
		c5 = 220.0 * pow(ratio, 3);
		c0 = c5 * pow(0.5, 5);
		base_freq = c0 * pow(ratio, start_val);
	} else {
		base_freq = start_val;
	}

	/* calc ratio from notes, and fill the array */
	ratio = pow(2.0, 1.0/notes);
	for (int i = 0; i <= notes; i++) {
		intervals[i] = base_freq;
		base_freq *= ratio;
	}

/* create new empty line if in append_to_file mode*/
	if (append_to_file) {
		fprintf(fp, "\n");
	};

/* print to file the full command line */
	if (fp) {
		argv -= flags;

		for (int i = 0; i < argc_copy; i++) {
			err = fprintf(fp, "%s ", argv[i]);
		}
		fprintf(fp, "\n");
	}

/* read array, write to screen, and optionally to file */
	for (int i = 0; i <= notes; i++) {
		double curr_interval = pow(ratio, i);
		double curr_freq = intervals[i];

		if (write_interval) {
			printf("%d:\t%f\t%f\n", i, curr_interval, curr_freq);
		} else {
			printf("%d:\t%f\n", i, curr_freq);
		}
		
		if (fp) {
			if (write_interval) {
				err = fprintf(fp, "%d:\t%f\t%f\n",
							  i, curr_interval, curr_freq);
			} else {
				err = fprintf(fp, "%d:\t%f\n", i, curr_freq);
			}
			
			if (err < 0) {
				break;
			}
		}
	}

	if (err < 0) {
		perror("There was an error writing to file.\n");
	}
	if (fp) {
		fclose(fp);
	}

	return 0;
}

