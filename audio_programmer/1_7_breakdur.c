/* Listing 1.7.4. P.145. */

/* Validate a text file of breakpoints
 * Prints the duration and max value of the breakpoints  
 */

#include<stdio.h>
#include<stdlib.h>


typedef struct breakpoint {
    double value;
    double time;
} BREAKPOINT;


/* input: points = array of BREAKPOINTS,
 *        npoints gives the length of the array 
 * output: copy of the BREAKPOINT containing largest value 
 */
BREAKPOINT maxpoint(const BREAKPOINT* points, long npoints) {
    BREAKPOINT maxpoint;

    maxpoint.time = points[0].time; /* initialize from first point */
    maxpoint.value = points[0].value;
    
    for (int i = 1; i < npoints; i++) {
        if (maxpoint.value < points[i].value) {
            maxpoint.value = points[i].value;
            maxpoint.time = points[i].time;
        }
    }
    return maxpoint;
}


BREAKPOINT* get_breakpoints(FILE* fp, long* psize) {
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

        if (got < 0) continue; /* empty line */
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
        printf("%f %f\n", points[npoints].time, points[npoints].value);
    
        if (++npoints == size) {
            BREAKPOINT* tmp;
            size += npoints;
            tmp = (BREAKPOINT*) realloc(points, sizeof(BREAKPOINT) * size);

            if (tmp == NULL) {
                /* have to release the memory, and return NULL */
                npoints = 0;
                free(points);
                points = NULL;
                break;
            }
            points = tmp;
        }
    }

    if (npoints) *psize = npoints;
    return points;
}


void normalize(BREAKPOINT* points, BREAKPOINT maxpoint, long size) {
    double minvalue = 1;

    for (int i = 0; i < size; i++) {
        if (points[i].value < minvalue) {
            minvalue = points[i].value;
        }
    }

    for (int i = 0; i < size; i++) {
        points[i].value = (points[i].value - minvalue)
            / (maxpoint.value - minvalue) * maxpoint.value;
    }

    printf("\nNormalized against %f\n", maxpoint.value);
    for (int i = 0; i < size; i++) {
        printf("%f %f\n", points[i].time, points[i].value);
    }
}


void scalevalue(BREAKPOINT* points, long size, double scale) {
    printf("\nScaling all values by %f...\n", scale);

    for (int i = 0; i < size; i++) {
        printf("%f %f\n", points[i].time, points[i].value * scale);
    }
}


int main(int argc, char* argv[]) {
	long size;
    double dur;
    BREAKPOINT point, *points;
    FILE* fp;

    printf("breakdur: find duration of breakpoint file\n");
    
    if (argc < 2) {
        printf("usage: breakdur infile.txt\n");
        return 0;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) return 0;

    size = 0;
    points = get_breakpoints(fp, &size);

    if (points == NULL) {
        printf("No breakpoints read.\n");
        fclose(fp);
        return 1;
    }
    if (size < 2) {
        printf("Error: at least two breakpoints required\n");
        free(points);
        fclose(fp);
        return 1;
    }

    /* we require breakpoints to start from 0 */
    if (points[0].time != 0.0) {
        printf("Error in breakpoint data: first time must be 0.0\n");
        free(points);
        fclose(fp);
        return 1;
    }
 
    printf("read %d breakpoints\n", size);

    dur = points[size-1].time;
    printf("duration: %f seconds\n", dur);
    
    point = maxpoint(points, size);
    printf("maximum value: %f at %f secs\n", point.value, point.time);
    
    // normalize(points, point, size);
    scalevalue(points, size, 0.3);

    free(points);
    fclose(fp);
    
    return 0;
}

