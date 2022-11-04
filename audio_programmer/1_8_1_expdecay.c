/* Listing 1.8.1. P.150. */

/* Calculate an exponential decay by implementing the formula
 * x[t] = a exp(-k/t)
 * where a and k are constants, t represents the time.
 *
 * use the command "./a.out 1 0.5 200 > expdecay.txt"
 * to write to a file
 *
 * add the flag -lm if encountering undefined error
 *
 * follow P.154 for plotting in log scale
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int main(int argc, char** argv) {
    int nsteps;
    double step, x, a, T, k;
    double dur;
    
    if (argc != 4) {
        printf("usage: %s dur T steps\n", argv[0]);
    }

    dur = atof(argv[1]);
    T = atof(argv[2]);
    nsteps = atoi(argv[3]);

    x = 1.0; /* starting value for the decay */
    k = dur/nsteps; /* the constant time increment */
    a = exp(-k/T); /* calc the constant ratio value */
    step = 0.0;

    for (int i = 0; i < nsteps; i++) {
        printf("%.4f\t%.8lf\n", step, x);
        x = a * x;
        step += k;
    }

    return 0;
}

