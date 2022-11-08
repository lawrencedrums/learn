/* Chapter 1.8 Exercises. P.155
 *
 * Exercise 1.8.2. AD envelop. */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char **argv) {
    double signal_floor, x, fac, step, curr_step;
    double attack_dur, decay_dur, maxlevel;
    int npoints, attack_points, decay_points;

    if (argc != 5) {
        fprintf(stderr, "usage: %s attac_dur decay_dur maxlevel npoints\n", argv[0]);
        return 1;
    }

    attack_dur = atof(argv[1]);
    if (attack_dur < 0.0) {
        fprintf(stderr, "attack_dur must be > 0.0\n");
        return 1;
    }
        
    decay_dur = atof(argv[2]);
    if (decay_dur < 0.0) {
        fprintf(stderr, "decay_dur must be > 0.0\n");
        return 1;
    }

    maxlevel = atof(argv[3]);
    if (maxlevel < 0.0) {
        fprintf(stderr, "maxlevel must be > 0.0\n");
        return 1;
    }

    npoints = atoi(argv[4]);
    if (npoints < 1) {
        fprintf(stderr, "npoints must be > 2\n");
        return 1;
    }

    attack_points = (int) (npoints * (attack_dur / (attack_dur+decay_dur)));
    decay_points = npoints - attack_points;

    signal_floor = x = 1.0e-4;
    fac = pow(maxlevel/signal_floor, 1.0/attack_points);

    step = (attack_dur+decay_dur) / npoints;
    curr_step = 0.0;

    for (int i = 0; i < attack_points; i++) {
        fprintf(stdout, "%.4f\t%.4f\n", curr_step, x);
        x *= fac;
        curr_step += step;
    }

    fac = pow(signal_floor/maxlevel, 1.0/decay_points);

    for (int i = 0; i < decay_points; i++) {
        fprintf(stdout, "%.4f\t%.4f\n", curr_step, x);
        x *= fac;
        curr_step += step;
    }

    return 0;
}

