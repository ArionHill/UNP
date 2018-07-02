#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define bufsize 80

void print_err(char *fmt, ...){
    va_list ap;
    char buf[bufsize];

    va_start(ap, fmt);
    vsnprintf(buf, bufsize, fmt, ap);
    va_end(ap);
    fprintf(stderr, buf);
    exit(1);
}