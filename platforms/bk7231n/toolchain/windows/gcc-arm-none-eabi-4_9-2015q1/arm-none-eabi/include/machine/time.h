#ifndef	_MACHTIME_H_
#define	_MACHTIME_H_

#if defined(__rtems__)
#define _CLOCKS_PER_SEC_  sysconf(_SC_CLK_TCK)
#elif defined(__aarch64__) || defined(__arm__) || defined(__thumb__)
#define _CLOCKS_PER_SEC_ 100
#elif defined (__VISIUM__)
#define _CLOCKS_PER_SEC_ 1000000
#endif

#ifdef __SPU__
#include <sys/types.h>
int nanosleep (const struct timespec *, struct timespec *);
#endif

#endif	/* _MACHTIME_H_ */
