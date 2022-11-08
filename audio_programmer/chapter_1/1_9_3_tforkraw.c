/* Listing 1.9.5. P.170.
 *
 * Generate raw sound file with native endianness 
 * based on tfork.c
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#ifndef M_PI
#define M_PI (3.14152654)
#endif

enum {
    ARG_NAME, ARG_OUTFILE, ARG_DUR, ARG_HZ, 
    ARG_SR, ARG_AMP, ARG_TYPE, ARG_NARGS
};

enum samp_type {RAWSAMP_SHORT, RAWSAMP_FLOAT};

/* thanks to the SNDAN programmers for this */
/* return 0 for big-endian machine, 1 for little-endian machine */
/* so we can tell user what order the data is */
int byte_order() {
    int one = 1;
    char *p_end = (char *) &one;
 
    return (*p_end);
}

const char *endianness[2] = {"big_endian", "little_endian"};

int main(int argc, char **argv) {
    unsigned int n_samps, samp_type, endian, bit_reverse;
    unsigned int max_frame = 0;

    double samp, dur, freq, s_rate, amp, step;
    double start, end, fac, max_samp;
    double two_pi = 2.0 * M_PI;
    double angle_incr;

    FILE *fp = NULL;

    float f_samp;
    short s_samp;

    if (argc != ARG_NARGS) {
        printf("Usage: %s outsfile.raw dur"
                "freq s_rate amp is_float\n",
                argv[ARG_NAME]);
        return 1;
    }

    dur = atof(argv[ARG_DUR]);
    freq = atof(argv[ARG_HZ]);
    s_rate = atof(argv[ARG_SR]);
    amp = atof(argv[ARG_AMP]);

    samp_type = (unsigned int) atoi(argv[ARG_TYPE]);
    if (samp_type > 1) {
        printf("Error: sample_type can be only 0 or 1\n");
        return 1;
    }

    /* create binary file: not all systems require the 'b' */
    fp = fopen(argv[ARG_OUTFILE], "wb");
    if (fp == NULL) {
        fprintf(stderr, "Error creating output file %s\n",
                argv[ARG_OUTFILE]);
        return 1;
    }

    n_samps = (int) (dur * s_rate);
    angle_incr = two_pi * freq / n_samps;
    step = dur / n_samps;

    /* normailized range always - just scale by amp */
    start = 1.0;
    end = 1.0e-4;
    max_samp = 0.0;
    fac = pow(end/start, 1.0/n_samps);

    endian = byte_order();
    printf("Writing %d %s samples\n", n_samps, endianness[endian]);

    /* run the loop for this samp_type */
    if (samp_type == RAWSAMP_SHORT) {
        for (int i = 0; i < n_samps; i++) {
            samp = amp * sin(angle_incr * i);
            samp *= start;
            start *= fac;

            /* use 32767 to avoid overflow problem */
            s_samp = (short) (samp * 32767.0);

            if (fwrite(&s_samp, sizeof(short), 1, fp) != 1) {
                printf("Error writing data to file\n");
                return 1;
            }
    
            if (fabs(samp) > max_samp) {
                max_samp = fabs(samp);
                max_frame = i;
            }
        }
    } else {
        for (int i = 0; i < n_samps; i++) {
            samp = amp * sin(angle_incr * i);
            samp *= start;
            start *= fac;
            f_samp = (float) samp;

            if (fwrite(&f_samp, sizeof(float), 1, fp) != 1) {
                printf("Error writing data to file\n");
                return 1;
            }    
    
            if (fabs(samp) > max_samp) {
                max_samp = fabs(samp);
                max_frame = i;
            }
        }
    }

    fclose(fp);
    printf("Done. Maximum sample values = %.8lf at frame %d\n",
            max_samp, max_frame);

    return 0;
}

