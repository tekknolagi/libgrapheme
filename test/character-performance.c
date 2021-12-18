/* See LICENSE file for copyright and license details. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../grapheme.h"
#include "../gen/character-test.h"
#include "util.h"

#define NUM_ITERATIONS 1000

int
main(int argc, char *argv[])
{
	struct timespec start, end;
	size_t i, j, bufsiz, off;
	uint32_t *buf;
	GRAPHEME_STATE state;
	double cp_per_sec;

	(void)argc;

	/* allocate and generate buffer */
	for (i = 0, bufsiz = 0; i < LEN(character_test); i++) {
		bufsiz += character_test[i].cplen;
	}
	if (!(buf = calloc(bufsiz, sizeof(*buf)))) {
		fprintf(stderr, "%s: calloc: Out of memory.\n", argv[0]);
		return 1;
	}
	for (i = 0, off = 0; i < LEN(character_test); i++) {
		for (j = 0; j < character_test[i].cplen; j++) {
			buf[off + j] = character_test[i].cp[j];
		}
		off += character_test[i].cplen;
	}

	/* run test */
	printf("%s: Running benchmark ", argv[0]);
	fflush(stdout);

	clock_gettime(CLOCK_MONOTONIC, &start);
	for (i = 0; i < NUM_ITERATIONS; i++) {
		memset(&state, 0, sizeof(state));
		for (j = 0; j < bufsiz - 1; j++) {
			(void)grapheme_character_isbreak(buf[j], buf[j+1], &state);
		}
		if (i % (NUM_ITERATIONS / 10) == 0) {
			printf(".");
			fflush(stdout);
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);

	cp_per_sec = (double)(NUM_ITERATIONS * bufsiz) /
	             time_diff(&start, &end);

	printf(" %.2e CP/s\n", cp_per_sec);

	return 0;
}