/* Chapter 1.8 Exercises. Ex 1.8.1. P.158.
 * Implement a exponential decay generator. 
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char** argv) {
    if (argc != 5) {
        fprintf(stderr,
                "usage: %s samplePoints levelBegin levelEnd releaseTime\n",
                argv[0]);
        return 1;
    }

    int samplePoints;
    double levelBegin, levelEnd, releaseTime;
    double coeff, currentLevel;
    const double sampleRate = 44100;

    samplePoints = atoi(argv[1]);
    levelBegin = atof(argv[2]);
    levelEnd = atof(argv[3]);
    releaseTime = atof(argv[4]);

    currentLevel = levelBegin;

    /* TODO: find the right way to cal coeff*/
    coeff = 1.0f + (log(levelEnd) - log(levelBegin)) /
            (releaseTime * sampleRate + 1);

    for (int i = 0; i < samplePoints; i++) {
        currentLevel += coeff * currentLevel;
        fprintf(stdout, "%.4f\n", currentLevel);
    }

    return 0;
}

