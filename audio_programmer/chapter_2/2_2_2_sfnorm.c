/* Chapter 2.2.3. P.212. */
/* sfnorm.c: normalise level of a sound file */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <portsf.h>

#define NFRAMES (1024)

enum {ARG_PROGNAME, ARG_INFILE, ARG_OUTFILE, ARG_DB, ARG_NARGS};

double max_samp(float *buf, unsigned long blocksize) {
    /* Return the value of the absolute peak sample in the input buffer.
     * Input:
     *     float *buf - pointer to a buffer of samples
     *     unsigned long blocksize - full size of the buffer
     * Output:
     *     double peak - the peak value in input buffer
     */

    double abs_val, peak = 0.0;
    unsigned long i;

    for (i = 0; i < blocksize; i++) {
        abs_val = fabs(buf[i]);

        if (abs_val > peak) {
            peak = abs_val;
        }
    }

    return peak;
}

int main(int argc, char **argv) {
    printf("sfnorm.c: normalise a sound file level.\n");

    if (argc != ARG_NARGS) {
        printf("Insufficient arguments\n"
               "usage:\n\tinfile outfile dB\n"
               "\twhere dB <= 0.0\n");
        return 1;
    }

    PSF_PROPS props;
    long frames_read;
    float amp_fac, scale_fac;
    double db_val, infile_peak = 0.0;

    int ifd = -1, ofd = -1;
    int error = 0;
    psf_format out_format = PSF_FMT_UNKNOWN;
    PSF_CHPEAK* peaks = NULL;
    float *p_frame = NULL;
    unsigned long blocksize, nframes = NFRAMES;

    if (psf_init()) {
        printf("unable to start portsf\n");
        return 1;
    }

    db_val = atof(argv[ARG_DB]);
    if (db_val > 0.0) {
        printf("Error: dB value cannot be positive\n");
        return 1;
    }
    amp_fac = (float) pow(10.0, db_val/20.0);

    ifd = psf_sndOpen(argv[ARG_INFILE], &props, 0);
    if (ifd < 0) {
        printf("Error: unable to open infile %s\n",
                argv[ARG_INFILE]);
        return 1;
    }
       
    p_frame = (float*) malloc(NFRAMES * props.chans * sizeof(float));
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

    /* get peak info: scan file if required */
    if (psf_sndReadPeaks(ifd, peaks, NULL) > 0) {
        for (long i = 0; i < props.chans; i++) {
            if (peaks[i].val > infile_peak) {
                infile_peak = peaks[i].val;
            }
        }
    } else {
        /* scan file, and rewind */
        frames_read = psf_sndReadFloatFrames(ifd, p_frame, nframes);
        while (frames_read > 0) {
            blocksize = props.chans;
            double this_peak = max_samp(p_frame, blocksize);

            if (this_peak > infile_peak) {
                infile_peak = this_peak;
            }
        
            frames_read = psf_sndReadFloatFrames(ifd, p_frame, nframes);
        }

        if ((psf_sndSeek(ifd, 0, PSF_SEEK_SET)) < 0) {
            printf("Error: unable to rewind infile\n");
            error++;
            goto exit;
        }
    }

    if (infile_peak == 0.0) {
        printf("Error: infile is silent\n");
        goto exit;
    }

    ofd = psf_sndCreate(argv[ARG_OUTFILE], &props, 0, 0, PSF_CREATE_RDWR);
    if (ofd < 0) {
        printf("Error: unable to create outfile %s\n",
                argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }

    scale_fac = (float) (amp_fac / infile_peak);
    frames_read = psf_sndReadFloatFrames(ifd, p_frame, nframes);
    while (frames_read > 0) {
        for (int i = 0; i < props.chans; i++) {
            p_frame[i] *= scale_fac;
        }

        if (psf_sndWriteFloatFrames(ofd, p_frame, nframes) < 0) {
            printf("Error writing to outfile\n");
            error++;
            break;
        }

        frames_read = psf_sndReadFloatFrames(ifd, p_frame, nframes);
    }

    if (frames_read < 0) {
        printf("Error read infile. Outfile is incomplete.\n");
        error++;
    } else {
        printf("Done.\n");
    }

    exit:
        if (ifd >= 0) psf_sndClose(ifd);
        if (ofd >= 0) psf_sndClose(ofd);
        if (p_frame) free(p_frame);
        if (peaks) free(peaks);
        psf_finish();

    return error;
}

