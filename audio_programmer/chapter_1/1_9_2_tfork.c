/* Listing 1.9.5. P.164.
 *
 * Virtual tuning fork combining sinetext.c and expdecay.c 
 * Simple version
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#ifndef M_PI
#define M_PI (3.141592654)
#endif

enum {ARG_NAME, ARG_OUTFILE, ARG_DUR, ARG_HZ,
        ARG_SR, ARG_AMP, ARG_NARGS};

int tfork_simple(char *file_path) {
    int sr, n_samps;
    double samp, dur, freq, s_rate, k, a, x, slope;
    double two_pi = 2.0 * M_PI;
    double angle_incr;
    double max_samp = 0.0;
    FILE *fp = NULL;

    if (ARG_NARGS != 7) {
        printf("usage: tfork outfile.txt dur freq s_rate slope\n");
        return 1;
    }

    fp = fopen(file_path, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error creating outup file %s\n",
                file_path);
        return 1;
    }

    // dur = atof(argv[ARG_DUR]);
    // freq = atof(argv[ARG_HZ]);
    // s_rate = atof(argv[ARG_SR]);
    slope = 0.5;
    n_samps = (int) (dur * s_rate);
    angle_incr = two_pi * freq / s_rate;
    k = dur / n_samps;
    a = exp(-k/slope);
    x = 1.0;

    for (int i = 0; i < n_samps; i++) {
        samp = sin(angle_incr * i);

        /* apply exp decay */
        x *= a;
        samp *= x;
        fprintf(fp, "%.8lf\n", samp);
    }

    fclose(fp);
    printf("done\n");

    return 0;
}


/* Listing 1.9.4. P.166.
 *
 * Tuning fork generator based on expbrk.c
 * - decay is always to ~silence regardless of duration
 */


int main(int argc, char **argv) {
    int sr, n_samps;
    double samp, dur, freq, s_rate, amp, max_samp;
    double start, end, fac, angle_incr;
    double two_pi = 2.0 * M_PI;
    FILE *fp = NULL;

    if (argc != ARG_NARGS) {
        printf("usage: %s outfile.txt dur freq s_rate amp\n",
                argv[ARG_NAME]);
        return 1;
    }

    fp = fopen(argv[ARG_OUTFILE], "W");
    if (fp == NULL) {
        printf("Error creating output file %s\n",
                argv[ARG_OUTFILE]);
        return 1;
    }

    dur = atof(argv[ARG_DUR]);
    freq = atof(argv[ARG_HZ]);
    s_rate = atof(argv[ARG_SR]);
    amp = atof(argv[ARG_AMP]);
    n_samps = (int) (dur * s_rate);
    angle_incr = two_pi * freq / n_samps;
    
    start = 1.0;
    end = 1.0e-4; /* = ~80dB */
    max_samp = 0.0;
    fac = pow(end/start, 1.0/n_samps);

    for (int i = 0; i < n_samps; i++) {
        samp = amp * sin(angle_incr * i);
        samp *= start;
        start *= fac;
        
        fprintf(fp, "%.8lf\n", samp);
        
        if (fabs(samp) > max_samp) {
            max_samp = fabs(samp);
        }
    }

    fclose(fp);
    printf("Done. Max sample value = %.8lf\n", max_samp);

    return 0;
}

