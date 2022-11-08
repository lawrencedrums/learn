/* Listing 1.9.1. P.159
 *
 * Generate single-cycle sine wave
 * Simple version
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/* condisiontal compilation - is M_PI defined? */
#ifndef M_PI
#define M_PI (3.141592654)
#endif

int simple_sine() {
    int n_samps;
    double samp;
    double two_pi = 2.0 * M_PI;
    double angle_incr;

    /* set number of points to create */
    n_samps = 50;

    /* make one complete cycle */
    angle_incr = two_pi / n_samps;
    for (int i = 0; i < n_samps; i++) {
        samp = sin(angle_incr * i);
        fprintf(stdout, "%.8lf\n", samp);
    }

    fprintf(stderr, "done\n");

    return 0;
}


/* Listing 1.9.2. P.161.
 * 
 * Generate single-cycle sine wave with args
 */

/* define our program argument list */
enum {ARG_NAME, ARG_NSAMPS, ARG_FREQ, ARG_SR, ARG_NARGS};

int main(int argc, char **argv) {
    // simple_sine();
    
    int n_samps;
    double samp, freq, s_rate;
    double two_pi = 2.0 * M_PI;
    double angle_incr;

    if (argc != ARG_NARGS) {
        fprintf(stderr,
                "usage: %s n_samps freq s_rate\n",
                argv[ARG_NAME]);
        return 1;
    }

    n_samps     = atoi(argv[ARG_NSAMPS]);
    freq        = atof(argv[ARG_FREQ]);
    s_rate      = atof(argv[ARG_SR]);
    angle_incr  = two_pi * freq / s_rate;

for (int i = 0; i < n_samps; i++) {
        samp = sin(angle_incr * i);
        fprintf(stdout, "%.8lf\n", samp);
    }

    fprintf(stderr, "done\n");

    return 0;
}

