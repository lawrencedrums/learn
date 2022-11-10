/* Chapter 2.1 Exercises. P.207. */

/* Exercise 2.1.1. */
/* Modify main loop to copy samples per block rather than per frame */

/* Exercise 2.1.2. */
/* Modify sf2float to show progress at some regular interval */

/* Exercise 2.1.3. */
/* Modify sf2float to copy to some limit defined by the command line */

/* Exercise 2.1.4. */
/* sfprop.c: reports the format information of a sound-file */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <portsf.h>

enum {ARG_PROGNAME, ARG_SFILE, ARG_NARGS};

int main(int argc, char  **argv) {
    PSF_PROPS props;
    PSF_CHPEAK* peaks = NULL;
    int sfd = -1;
    long size;

    char *file_format;
    char *samp_type;
    char *ch_format;
    
    if (argc != ARG_NARGS) {
        printf("insufficient arguments.\n"
               "usage:\n\t%s sfile\n",
               argv[ARG_PROGNAME]);
        return 1;
    }

    if (psf_init()) {
        printf("unable to start portsf\n");
        return 1;
    }

    sfd = psf_sndOpen(argv[ARG_SFILE], &props, 0);
    if (sfd < 0) {
        printf("Error: unable to open infile %s\n",
                argv[ARG_SFILE]);
        return 1;
    }

    switch(props.format) {
        case (PSF_STDWAVE || PSF_WAVE_EX):
            file_format = "wav";
            break;
        case (PSF_AIFF):
            file_format = "aiff";
            break;
        case (PSF_AIFC):
            file_format = "aifc";
            break;
        default:
            file_format = "unknown";
    }

    switch(props.samptype) {
        case (PSF_SAMP_16):
            samp_type = "16-bit";
            break;
        case (PSF_SAMP_24):
            samp_type = "24-bit";
            break;
        case (PSF_SAMP_32):
            samp_type = "32-bit int";
            break;
        case (PSF_SAMP_IEEE_FLOAT):
            samp_type = "32-bit Floating point";
            break;
        default:
            samp_type = "unknown";
    }

    switch(props.chformat) {
        case (STDWAVE):
            ch_format = "Stardard";
            break;
        case (MC_MONO):
            ch_format = "Mono";
            break;
        case (MC_STEREO):
            ch_format = "Stereo";
            break;
        case (MC_DOLBY_5_1):
            ch_format = "Dolby 5.1";
            break;
        default:
            ch_format = "unknown";
    }

    printf("The sound file %s has the following properties:\n"
           "Format: %s\n"
           "Sample rate: %ld\n"
           "Sample type: %s\n"
           "Channels: %ld\n"
           "Channel format: %s\n",
           argv[ARG_SFILE], file_format, props.srate,
           samp_type, props.chans, ch_format);

    return 0;
}

/* Exercise 2.1.5. */
/* Modify sf2float.c to display PEAK in dB */

/* Exercise 2.1.6.  */
/* Program that creates loop N times */

