#ifndef P_ERR_H
#define P_ERR_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef HAVE_ERR_H
void err(int eval, const char *fmt, ...);

void errx(int eval, const char *fmt, ...);
#endif
#endif