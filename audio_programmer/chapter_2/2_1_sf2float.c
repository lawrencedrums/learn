/* Listing 2.1.3. P.203. 
 *
 * sf2float.c : convert soundfile to floats */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <portsf.h>

enum {ARG_PROGNAME, ARG_INFILE, ARG_OUTFILE, ARG_LIMIT, ARG_NARGS};

int main(int argc, char **argv) {
    PSF_PROPS props;
    long frames_read, total_read;

    /* init all resources vars to default states */
    int ifd = -1, ofd = -1;
    int error = 0;
    psf_format out_format = PSF_FMT_UNKNOWN;
    PSF_CHPEAK* peaks = NULL;
    float* frame = NULL;
    int frame_buffer = 100;
    float peak_dB;
    long copy_limit, infile_size;

    printf("SF2FLOAT: convert sound file to floats format\n");

    if (argc < ARG_NARGS) {
        printf("insufficient arguments.\n"
               "usage:\n\t%s infile outfile\n",
               argv[ARG_PROGNAME]);
        return 1;
    }

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

    /* tell user if source file is already floats */
    if (props.samptype == PSF_SAMP_IEEE_FLOAT) {
        printf("Info: infile is already in floats format.\n");
    }
    
    props.samptype = PSF_SAMP_IEEE_FLOAT;

    /* chech outfile extension is one we support */
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
        printf("Error: unable to create outfile %s\n",
                argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }

    /* allocate space for one sample frame */
    frame = (float*) malloc(frame_buffer * props.chans * sizeof(float));
    if (frame == NULL) {
        puts("No memory!\n");
        error++;
        goto exit;
    }

    /* and allocate space for PEAK info */
    peaks = (PSF_CHPEAK*) malloc(props.chans * sizeof(PSF_CHPEAK));
    if (peaks == NULL) {
        puts("No memory!\n");
        error++;
        goto exit;
    }

    copy_limit = atoi(argv[ARG_LIMIT]);
    infile_size = psf_sndSize(ifd);
    if (copy_limit > infile_size) {
        printf("Error: copy upper limit exceed infile size of %ld samples\n",
                infile_size);
        error++;
        goto exit;
    }

    printf("copying %ld of %ld samples\n", copy_limit, infile_size);

    /* single-frame loop to do copy, report any errors */
    frames_read = psf_sndReadFloatFrames(ifd, frame, frame_buffer);
    total_read = 0; /* running count of sample frames */
    while (frames_read == frame_buffer && total_read < copy_limit) {
        total_read += frame_buffer;
        if (total_read % 10000 == 0 || total_read == infile_size) {
            printf("\r%d samples copied", total_read);
        }

        if (psf_sndWriteFloatFrames(ofd, frame, frame_buffer) != frame_buffer) {
            printf("Error writing to outfile\n");
            error++;
            break;
        }

        /* <---- do any processing here ----> */
        frames_read = psf_sndReadFloatFrames(ifd, frame, frame_buffer);
    }

    printf("\n");

    if (frames_read < 0) {
        printf("Error reading infile. Outfile is incomplete.\n");
        error++;
    } else {
        printf("Done. %d sample frames copied to %s\n",
                total_read, argv[ARG_OUTFILE]);
    }

    /* report PEAK values to user */
    if (psf_sndReadPeaks(ofd, peaks, NULL) > 0) {
        long i;
        double peak_time;

        printf("PEAK information: \n");
        for (int i = 0; i < props.chans; i++) {
            peak_time = (double) peaks[i].pos / props.srate;
            
            peak_dB = 20.0 * log10(peaks[i].val);
            printf("CH %d:\t%.4lfdB at %.4f secs\n",
                   i+1, peak_dB, peak_time);
        }
    }

    /* handle error and cleanup */
    exit:
    if (ifd >= 0) psf_sndClose(ifd);
    if (ofd >= 0) psf_sndClose(ofd);
    if (frame) free(frame);
    if (peaks) free(peaks);
    psf_finish();

    return error;
}

