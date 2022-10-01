/* Program to document and demostrate the use of pointers */

#include <stdio.h>

int main() {
	/* The '*' can be used as a 'content-of' operator. */

    /* a "pointer to double" variable that contains the
	 * the machine address of another variable.
	 */
	double* ptr;
	double buffer[1024], val;

	/* sets ptr to point to the beginner of buffer */
	ptr = buffer;
	
	/* now instead of writing buffer[0] = 1.0594631, we can write */
	*ptr = 1.0594631 /* buffer[0] now contains 1.0594631 */
	/* In the line above, we say "set the contents of ptr to 1.0594631*/

	/* read the contents of ptr, now val = 1.0594631 */
	val = *ptr;

	/* The '&' is an 'address-of' operator. */

	/* find the address of val, assign it to ptr */
	ptr = &val;
	/* In the line above, we say "set ptr to the address of val" */ 

	/* using this, we can intialise variables indirectly */
	ptr = &buffer[0];
	/* In the line above, we say "set ptr to the address of element 0 of buffer" */

	/**
	 * this way of indirectly initialising variable allows all sorts of
	 * "mass-production" techniques to be used at high efficiency in
	 * conjunction with loops.
	 *
	 * Because addresses can themselves be treated as variables, C enables
	 * us to avoid a great deal of costly copying of data by manipulating
	 * pointers and addresses.
	 */

	/* the section below sets each element of buffer_two to 0.0 */
	double buffer_two[1024];
	ptr = buffer_two; /* set ptr to point to the start of buffer_two*/
	for (int i = 0; i < 1024; i++) {
		*ptr++ = 0.0; /* move pointer to next element of the array */
	}

	return 0;
}
