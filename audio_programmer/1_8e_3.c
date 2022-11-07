/* Chapter 1.8 Exercise. P.155.
 *
 * Exercise 1.8.3.
 *   a) i.  The curve grows logarithmically instead of exponentially. 
 *      ii. This attack curve can be seen in fade ins and fade outs, or synths.
 *   b) modify code to eliminate duplicate calculations
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char **argv) {
    int npoints;
    double T, k, a;
    double y_start, y_end;
    double dur, this_val, this_step;

    if (argc != 6) {
        fprintf(stderr,
                "usage: %s duration npoints start_val env_val T\n",
                argv[0]);
        return 1;
    }

    dur = atof(argv[1]);
    if (dur <= 0.0) {
        fprintf(stderr, "duration must be > 0.0\n");
        return 1;
    }

    npoints = atoi(argv[2]);
    if (npoints <= 0) {
        fprintf(stderr, "npoints must be > 0.0\n");
        return 1;
    }

    y_start = atof(argv[3]);
    y_end = atof(argv[4]);
    if (y_start == y_end) {
        fprintf(stderr, "Warning: start and end values are the same!\n");
    }
    
    T = atof(argv[5]);
    k = dur/npoints; /* npoints = "sample rate" */
    a = exp(-k/T); /* T = time constant */

    this_step = 0.0;
    this_val = y_start;

    fprintf(stderr, "a = %.6lf\n", a);
    
    /* make normalized curve, scale output to input values and range */
    for (int i = 0; i < npoints; i++) {
        printf("%.4lf\t%.8lf\n", this_step, this_val);
        this_val = a * this_val + (1.0 - a) * y_end;
        this_step += k;
    }

    printf("%.4lf\t%.8lf\n", this_step, this_val);
    fprintf(stderr, "done\n");

    return 0;
}

