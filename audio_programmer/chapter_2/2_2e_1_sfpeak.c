/* Chapter 2 Exercise 2.2.4. P.218(PDF P.245). */
/* sfpeak.c: find the peak amplitude of a sound file */

#include <stdio.h>
#include <stdlib.h>
#include <portsf.h>
#include <math.h>

#define BUFFER_SIZE (1024)

enum{ARG_PROGNAME, ARG_INFILE, ARG_NARGS};


double max_samp(float* buf, unsigned long blocksize) {
    double abs_val, peak = 0.0;

    for (unsigned long i = 0; i < blocksize; i++) {
        abs_val = fabs(buf[i]);

        if (abs_val > peak) {
            peak = abs_val;
        }
    }

    return peak;
}


int main(int argc, char** argv) {
    printf("sfpeak.c: find the peak amplitude of a sound file\n");
    
    if (argc != ARG_NARGS) {
        printf("usage:\n\t%s soundfile\n",
                argv[ARG_NARGS]);
        return 1;
    }

    PSF_PROPS props;
    long frames_read;
    double sfd_peak = 0.0;

    int sfd = -1;
    int error = -1;
    PSF_CHPEAK* peaks = NULL;
    float *p_frame = NULL;
    unsigned long blocksize, nframes = BUFFER_SIZE;

    if (psf_init()) {
        printf("unable to start portsf\n");
        return 1;
    }

    sfd = psf_sndOpen(argv[ARG_INFILE], &props, 0);
    if (sfd < 0) {
        printf("Error: unable to open sound file %s\n",
                argv[ARG_INFILE]);
        return 1;
    }

    p_frame = (float*) malloc(BUFFER_SIZE * props.chans * sizeof(float));
    if (p_frame == NULL) {
        puts("No memory!\n");
        error++;
        goto exit;
    }

    peaks = (PSF_CHPEAK*) malloc(props.chans * sizeof(PSF_CHPEAK));
    if (peaks == NULL) {
        puts("No memory!\n");
        error++;
        goto exit;
    }

    if (psf_sndReadPeaks(sfd, peaks, NULL) > 0) {
        for (long i = 0; i < props.chans; i++) {
            if (peaks[i].val > sfd_peak) {
                sfd_peak = peaks[i].val;
            }
        }
    } else {
        frames_read = psf_sndReadFloatFrames(sfd, p_frame, nframes);
        while (frames_read > 0) {
            blocksize = props.chans;
            double this_peak = max_samp(p_frame, blocksize);

            if (this_peak > sfd_peak) {
                sfd_peak = this_peak;
            }

            frames_read = psf_sndReadFloatFrames(sfd, p_frame, nframes);
        }
    }

    if (sfd_peak == 0.0) {
        printf("Error: sound file is silent\n");
        goto exit;
    }

    printf("The peak amplitude of %s is %0.5lf.\n",
            argv[ARG_INFILE], sfd_peak);
    
    exit:
        if (sfd >= 0) psf_sndClose(sfd);
        if (p_frame) free(p_frame);
        if (peaks) free(peaks);
        psf_finish();
    
    return error;
}

