/* See LICENSE file for copyright and license details. */
#ifndef UTIL_H
#define UTIL_H

#include <time.h>

#define LEN(x) (sizeof(x) / sizeof(*(x)))

double time_diff(struct timespec *, struct timespec *);

#endif /* UTIL_H */