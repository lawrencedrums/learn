/* Listing 1.6.1. P113. */

/** Find the value and position of the maximum positive sample 
 *  in an array, steping backward one sample at a time.
 */

#include <stdio.h>

int main() {
	double buffer[1024];

	/* point to element immediately beyond the array */
	double *ptr = buffer + 1024;

	double max_val = 0.0;
	unsigned long pos = 0;

	/** the comparison != (or >) is possible because addresses are integral numbers
     *  we compare ptr with the address of the start of the array (buffer).
	 *
	 *  compare against zero is faster than comparsion with non-zero value
	 *  auto decrement is faster than auto increment is faster than for/while loop
	 *  but ultimately it's more important for us to write code we understand, 
	 *  and feel comfortable with.
	 */
	while (--ptr != buffer) {
		if (*ptr >= max_val) {
			max_val = *ptr;

			/** exploiting the name 'buffer' is the address of the first element
			 *  the different between that and the value of ptr gives the
			 *  distance from the start of the buffer to the maximum sample
			 */
			pos = ptr - buffer;
		}
	}

	printf("The maximum sample is %f, at position %li\n",
		   max_val, pos);

	return 0;
}

/* Listing 1.6.3. P.116. */

/** below is an example of pointer increment and do loop in Csound
 *  which uses buffers of samples that are always ksmps in size 
 *  nsmps is initialised to ksmps, the arrakkkky pointed by samp and ar
 *  are both nsmps in size
 *
 *  nsmps = ksmps;
 *  do {
 *      float sample = *samp++;
 *      output = sample - input + (gain * output);
 *      input = sample;
 *      *ar++ = output;
 *  } while (--nsmps);
 */

