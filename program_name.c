#include "program_name.h"
#ifndef HAVE_PROGRAM_NAME
#include <string.h>
#include <windows.h>

#define MAX_PROGRAM_NAME_BUFFER_SIZE 2048

char *program_name                  = NULL;
char *short_program_name            = NULL;
static int program_name_initialized = 0;

static void
__init_program_name() {
	HMODULE h;
	DWORD dw;
	char *p;
	size_t program_name_size = 255;
	size_t l;
	ssize_t i;

	if (program_name_initialized)
		return;

	program_name_initialized = 1;
	h                        = GetModuleHandle(NULL);
	if (NULL == h)
		return;

	do {
		p = malloc(program_name_size);
		if (!p)
			ExitProcess(1024);
		SetLastError(0);
		dw = GetModuleFileNameA(h, p, program_name_size);
		if (dw >= program_name_size || (0 == dw && GetLastError() != ERROR_SUCCESS)) {
			dw = 0;
			free(p);
			p = NULL;
			program_name_size *= 2;
			if (program_name_size > MAX_PROGRAM_NAME_BUFFER_SIZE)
				break;
		} else
			break;
	} while (1);

	if (!p)
		return;

	p[dw]        = '\0';
	program_name = strdup(p);

	l = strlen(p);
	for (i = l - 1; i >= 0 && p[i] != '\\' && p[i] != '/'; i--) {
	}
	if (i >= 0) {
		short_program_name = strdup(&p[i + 1]);
	} else
		short_program_name = strdup(p);
	free(p);
}

const char *
get_program_name() {
	if (!program_name_initialized)
		__init_program_name();
	return (const char *)program_name;
}

const char *
get_short_program_name() {
	if (!program_name_initialized)
		__init_program_name();
	return (const char *)short_program_name;
}

#endif