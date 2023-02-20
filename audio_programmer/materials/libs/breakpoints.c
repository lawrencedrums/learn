#include <stdio.h>
#include <stdlib.h>


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

