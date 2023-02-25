/* Chapter 2.3. P.220-233. */
/* sfpan.c */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <portsf.h>


enum {ARG_PROGNAME, ARG_INFILE, ARG_OUTFILE, ARG_BRKFILE, ARG_NARGS};
#define BUFFER (1024)

typedef struct panpos {
    double left;
    double right;
} PANPOS;


PANPOS simple_pan(double position) {
    PANPOS pos;

    position *= 0.5;
    pos.left = position - 0.5;
    pos.right = position + 0.5;

    return pos;
}


PANPOS const_power(double position) {
    PANPOS pos;
    
    /* pi/2: 1/4 cycle of a sinusoid */
    const double piover2 = 4.0 * atan(1.0) * 0.5;
    const double root2over2 = sqrt(2.0) * 0.5;
    
    /* scale position to fit the pi/2 range */
    double this_pos = position * piover2;

    /* each channel uses a 1/4 of a cycle */
    double angle = this_pos * 0.5;
    
    pos.left = root2over2 * (cos(angle) - sin(angle));
    pos.right = root2over2 * (cos(angle) + sin(angle));
    return pos;
}

int main(int argc, char** argv) {
    if (argc != ARG_NARGS) {
        printf("insufficient arguments\n"
               "usages:\t\n%s infile outfile posfile.brk\n"
               "\tposfile.brk is breakpoint file"
               "with values in range -1.0 <= pos <= 1.0)\n"
               "where -1.0 = full left, 0 = centre, +1.0 = full right",
               argv[ARG_PROGNAME]);
        return 1;
    }

    PSF_PROPS in_props, out_props;
    long frames_read;
    double position, time_incr, sample_time;
    PANPOS curr_pos;
    
    FILE* fp = NULL;
    unsigned long size;
    BREAKPOINT* points = NULL;
    int ifd = -1, ofd = -1;
    int error = 0;
    psf_format out_format = PSF_FMT_UNKNOWN;
    PSF_CHPEAK* peaks = NULL;
    float *p_inframe = NULL, *p_outframe = NULL;
    long frame_buf = BUFFER;

    if (psf_init()) {
        printf("unable to start portsf\n");
        return 1;
    }

    // position = atof(argv[ARG_PANPOS]);
    // if (position < -1.0 || position > 1.0) {
    // if (in_range(position, -1.0, 1.0
    //     printf("Error: panpos out of range -1 to +1\n");
    //     error++;
    //     goto exit;
    // }

    /* read breakpoint file and verify it */
    fp = fopen(argv[ARG_BRKFILE], "r");
    if (fp == NULL) {
        printf("Error: unable to open"
               "breakpoint file %s\n",
               argv[ARG_BRKFILE]);
        error++;
        goto exit;
    }

    points = get_breakpoints(fp, &size);
    if (points == NULL) {
        printf("No breakpoints read.\n");
        error++;
        goto exit;
    }

    if (size < 2) {
        printf("Error: at least two breakpoints required\n");
        free(points);
        fclose(fp);
        return 1;
    }

    /* we require breakpoints to start from 0 */
    if (points[0].time != 0.0) {
        printf("Error in breakpoint data: "
               "first time must be 0.0\n");
        error+;
        goto exit;
    }

    if (!in_range(points, -1, 1.0, size)) {
        printf("Error in breakpoint file: "
               "values out of range -1 to +1 \n");
        error++;
        goto exit;
    }

    ifd = psf_sndOpen(argv[ARG_INFILE], &in_props, 0);
    if (ifd < 0) {
        printf("Error: unable to open infile %s\n",
                argv[ARG_INFILE]);
        error++;
        goto exit;
    }

    if (in_props.chans != 1) {
        printf("Error: infile must be mono.\n");
        error++;
        goto exit;
    }

    out_format = psf_getFormatExt(argv[ARG_OUTFILE]);
    if (out_format == PSF_FMT_UNKNOWN) {
        printf("outfile name %s has unknown format.\n"
               "use .wav, .aiff, .aif, .afc, .aifc\n",
               argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }
    out_props = in_props;
    out_props.format = out_format;
    out_props.chans = 2;
    
    ofd = psf_sndCreate(argv[ARG_OUTFILE], &out_props, 0, 0, PSF_CREATE_RDWR);
    if (ofd < 0) {
        printf("Error: unable to open outfile %s\n",
                argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }

    p_inframe = (float*) malloc(frame_buf * in_props.chans * sizeof(float));
    p_outframe = (float*) malloc(frame_buf * out_props.chans * sizeof(float));
    if (p_inframe == NULL || p_outframe == NULL) {
        puts("No memory!\n");
        error++;
        goto exit;
    }
    
    time_incr = 1.0 / in_props.srate;
    sample_time = 0.0;

    while ((frames_read = psf_sndReadFloatFrames(ifd, p_inframe, frame_buf)) > 0) {
        int i, out_i;
        double stereo_pos;

        for(i = 0, out_i = 0; i < frames_read; i++) {
            stereo_pos = val_at_brktime(points, size, sample_time);
            curr_pos = simple_pan(stereo_pos);
            p_outframe[out_i++] = (float) (p_inframe[i] * curr_pos.left);
            p_outframe[out_i++] = (float) (p_inframe[i] * curr_pos.right);
            sample_time += time_incr;
        }

        if (psf_sndWriteFloatFrames(ofd, p_outframe, frames_read) != frames_read) {
            printf("Error writing to outfile\n");
            error++;
            break;
        }
    }

    // curr_pos = simple_pan(position);
    // while ((frames_read = psf_sndReadFloatFrames(ifd, p_inframe, frame_buf)) > 0) {
    //     for (int i = 0, out_i = 0; i < frames_read; i++) {
    //         p_outframe[out_i++] = (float) (p_inframe[i] * curr_pos.left);
    //         p_outframe[out_i++] = (float) (p_inframe[i] * curr_pos.right);
    //     }
       
    //     if (psf_sndWriteFloatFrames(ofd, p_outframe, frames_read) != frames_read) {
    //        printf("Error writing to outfile\n");
    //        error++;
    //        break;
    //     }
    // }

    if (frames_read < 0) {
        printf("Error reading infile. Outfile is imcomplete.\n");
        error++;
    } else {
        printf("Done.\n");
    }

    exit:
        if (ifd >= 0) psf_sndClose(ifd);
        if (ofd >= 0) psf_sndClose(ofd);
        if (p_inframe) free(p_inframe);
        if (p_outframe) free(p_outframe);
        psf_finish();

    return error;
}

