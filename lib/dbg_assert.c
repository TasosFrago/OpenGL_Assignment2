#include <stdio.h>
#include <stdlib.h>

#include "dbg_assert.h"


void __dbg_assert(const char *expr, const char *file, int line, const char *func)
{
	fprintf(stderr, "[ERROR]::ASSERT_FAILED: %s\n\tFILE: %s\n\tLINE: %d\n\tFUNCTION: %s\nEXITING...\n", expr, file, line, func);
	exit(-1);
}

void __dbg_log(const char *msg, const char *file, int line, const char *func, errorL_t level)
{
	printf("%d\n", level);
	switch(level) {
	case LOG:
		fprintf(stdout, "[LOG]::%s\n\tFILE: %s\n\tLINE: %d\n\tFUNCTION: %s\n", msg, file, line, func);
		break;
	case WARNING:
		fprintf(stderr, "[WARNING]::%s\n\tFILE: %s\n\tLINE: %d\n\tFUNCTION: %s\n", msg, file, line, func);
		break;
	case ERROR:
		fprintf(stderr, "[ERROR]::%s\n\tFILE: %s\n\tLINE: %d\n\tFUNCTION: %s\n", msg, file, line, func);
		break;
	}
}
