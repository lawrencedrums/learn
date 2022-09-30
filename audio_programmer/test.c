#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[]) {
	char* message = argv[1];	

	for (int i = 0; i < strlen(message); i++) {
		if (message[i] == '\0') {
			break;
		} else {
			printf("isdigit('%c') returns %d\n", message[i], isdigit(message[i]));
			if (!isdigit(message[i])) {
				printf("Found a non-digit. Exiting program.\n");
				return 1;
			}
		}
	}

	return 0;
}
