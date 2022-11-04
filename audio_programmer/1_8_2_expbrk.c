/* Listing 1.8.2. P.152. */

/* expbrk.c generate exponential attack or decay breakpoint data */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char** argv) {
    int npoints;
    double start_val, end_val;
    double dur, step, start, end, this_step;
    double fac, val_range, offset;
    const double very_small = 1.0e-4; /* ~-80dB */

    if (argc != 5) {
        fprintf(stderr,
                "usage: %s duration npoints start_val end_val\n",
                argv[0]);
        return 1;
    }

    dur = atof(argv[1]);
    if (dur <= 0.0) {
        fprintf(stderr, "error: duration must be > 0.0\n");
    }

    npoints = atoi(argv[2]);
    if (npoints <= 0) {
        fprintf(stderr, "error: npoints must be > 0\n");
        return 1;
    }
    
    start_val = atof(argv[3]);
    end_val = atof(argv[4]);
    val_range = end_val - start_val;

    if (val_range == 0.0) {
        fprintf(stderr, 
                "warning: start and end values are the same!\n");
    }

    if (start_val > end_val) {
        start = 1.0;
        end = very_small;
        offset = end_val;
        val_range = -val_range;
    } else {
        start = very_small;
        end = 1.0;
        offset = start_val;
    }

    step = dur/npoints;
    this_step = 0.0;

    /* make normalized curve, scale output to input values, range */
    fac = pow(end/start, 1.0/npoints);

    for (int i = 0; i < npoints; i++) {
        fprintf(stdout, "%.4lf\t%.8lf\n",
                this_step, offset+(start*val_range));
        start *= fac;
        this_step += step;
    }

    /* print final value */
    fprintf(stdout, "%.4lf\t%.8lf\n",
            this_step, offset+(start*val_range));
    fprintf(stderr, "done\n");

    return 0;
}

