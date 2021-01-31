#include "p_err.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef HAVE_PROGRAM_NAME
#include "program_name.h"
#endif

#ifndef HAVE_ERR_H

static void
internal_err(int show_error, int eval, const char *fmt, va_list varargs) {
	fprintf(stderr, "%s: ", get_short_program_name());
	if (fmt) {
		vfprintf(stderr, fmt, varargs);
		if (show_error)
			fprintf(stderr, ": %s", strerror(errno));
	}
	fprintf(stderr, "\n");
}

void err(int eval, const char *fmt, ...) {
	va_list varargs;
	va_start(varargs, fmt);
	internal_err(1, eval, fmt, varargs);
	va_end(varargs);
	exit(eval);
}

void errx(int eval, const char *fmt, ...) {
	va_list varargs;
	va_start(varargs, fmt);
	internal_err(0, eval, fmt, varargs);
	va_end(varargs);
	exit(eval);
}
#endif