#ifndef PROGRAM_NAME_H
#define PROGRAM_NAME_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef HAVE_PROGRAM_NAME
const char *
get_short_program_name();

const char *
get_program_name();
#endif
#endif