#include <stdio.h>
#include <stdlib.h>
#include <breakpoints.h>


BREAKPOINT maxpoint(const BREAKPOINT* points, long npoints) {
    BREAKPOINT maxpoint;

    maxpoint.time = points[0].time;
    maxpoint.value = points[0].value;

    for (int i = 1; i < npoints; i++) {
        if (maxpoint.value < points[i].value) {
            maxpoint.value = points[i].value;
            maxpoint.time = points[i].time;
        }
    }
    return maxpoint;
}


BREAKPOINT* get_breakpoints(FILE* fp, long* p_size) {
    int got;
    unsigned long npoints = 0, size = 64;
    double lasttime = 0.0;
    BREAKPOINT* points = NULL;
    char line[80];

    if (fp == NULL) return NULL;

    points = (BREAKPOINT*) malloc(sizeof(BREAKPOINT) * size);
    if (points == NULL) return NULL;

    while (fgets(line, 80, fp)) {
        got = sscanf(line, "%lf %lf",
                &points[npoints].time, &points[npoints].value);

        if (got < 0) continue;
        if (got == 0) {
            printf("Line %lu has non-numeric data\n", npoints+1);
            break;
        }
        if (got == 1) {
            printf("Incomplete breakpoint found at point %lu\n",
                    npoints+1);
            break;
        }

        lasttime = points[npoints].time;
        printf("%lf %f\n", points[npoints].time, points[npoints].value);

        if (++npoints == size) {
            BREAKPOINT* tmp;
            size += npoints;
            tmp = (BREAKPOINT*) realloc(points, sizeof(BREAKPOINT) * size);

            if (tmp == NULL) {
                npoints = 0;
                free(points);
                points = NULL;
                break;
            }
            points = tmp;
        }
    }

    if (npoints) *p_size = npoints;
    return points;
}


int in_range(const BREAKPOINT* points,
        double min_val,
        double max_val,
        unsigned long npoints) {
    int is_in_range = 1;

    for (unsigned long i = 0; i < npoints; i++) {
        if (points[i].value < min_val || points[i].value > max_val) {
            is_in_range = 0;
            break;
        }
    }
    return is_in_range;
}


double val_at_brktime(const BREAKPOINT* points, unsigned long n_points, double time) {
    unsigned long i;
    BREAKPOINT left, right;
    double frac, val, width;

    /* scan until we find a span containing our time */
    for (i = 0; i < n_points; i++) {
        if (time <= points[i].time) break;
    }

    /* maintain final value if time beyond end of data */
    if (i == n_points) return points[i-1].value;
    left = points[i-1];
    right = points[i];
    
    /* check for instant jump - two points with same time */
    width = right.time - left.time;
    if (width == 0.0) return right.value;

    /* get value from this span using linear interpolation */
    frac = (time - left.time) / width;
    val = left.value + ((right.value - left.value) * frac);

    return val;
}

