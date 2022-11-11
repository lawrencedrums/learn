/* Chapter 2.2.1. P.209. */
/* sfgain.c: change level of a sound file */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <portsf.h>

enum {ARG_PROGNAME, ARG_INFILE, ARG_OUTFILE, ARG_GAIN, ARG_NARGS};

int main(int argc, char **argv) {
    printf("sfgain.c: change level of sound file\n");
    
    if (argc != ARG_NARGS) {
        printf("Insufficient arguments\n"
               "usage:\t\n%s infile outfile gain\n");
        return 1;
    }
    
    PSF_PROPS props;
    long frames_read, total_read;
    float amp_fac;

    int ifd = -1, ofd = -1;
    int error = 0;
    psf_format out_format = PSF_FMT_UNKNOWN;
    PSF_CHPEAK* peaks = NULL;
    float* frame = NULL;

    if (psf_init()) {
        printf("unable to start portsf\n");
        return 1;
    }

    ifd = psf_sndOpen(argv[ARG_INFILE], &props, 0);
    if (ifd < 0) {
        printf("Error: unable to open infile %s\n",
                argv[ARG_INFILE]);
        return 1;
    }

    amp_fac = atof(argv[ARG_GAIN]);
    if (amp_fac <= 0.0) {
        printf("Error: gain must be positive\n");
        error++;
        goto exit;
    } else if (amp_fac == 1.0) {
        printf("Gain of 1.0 results in no change amplitude.\n"
               "Exiting...\n");
        error++;
        goto exit;
    }

    out_format = psf_getFormatExt(argv[ARG_OUTFILE]);
    if (out_format == PSF_FMT_UNKNOWN) {
        printf("outfile name %s has unknown format.\n"
               "use any of .wav, .aiff, .aif, .afc, .aifc\n",
               argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }
    props.format = out_format;

    ofd = psf_sndCreate(argv[2], &props, 0, 0, PSF_CREATE_RDWR);
    if (ofd < 0) {
        printf("Error unable to create outfile %s\n",
                argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }

    frame = (float*) malloc(props.chans * sizeof(float));
    if (frame == NULL) {
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

    frames_read = psf_sndReadFloatFrames(ifd, frame, 1);
    total_read = 0;
    while (frames_read == 1) {
        total_read++;

        for (int i = 0; i < props.chans; i++) {
            frame[i] *= amp_fac;
        }

        if (psf_sndWriteFloatFrames(ofd, frame, 1) != 1) {
            printf("Error writing to outfile\n");
            error++;
            break;
        }

        frames_read = psf_sndReadFloatFrames(ifd, frame, 1);
    }

    if (frames_read < 0) {
        printf("Error reading infile. Outfile is incomplete.\n");
        error++;
    } else {
        printf("Done.\n");
    }

    exit:
        if (ifd >= 0) psf_sndClose(ifd);
        if (ofd >= 0) psf_sndClose(ofd);
        if (frame) free(frame);
        if (peaks) free(peaks);
        psf_finish();

    return error;
}

