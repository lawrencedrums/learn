#include <stdio.h>
#include <stdlib.h>


typedef breakpoint {
    double value;
    double time;
} BREAKPOINT;


BREAKPOINT* get_breakpoints(FILE* fp, long* p_size);

BREAKPOINT maxpoint(const BREAKPOINT* points, long npoints);

int in_range(const BREAKPOINT* points,
        double min_val;
        double max_val;
        unsigned long npoints);

