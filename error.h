// error.h
// Řešení IJC-DU1, příklad b), 19.3.2024
// Autor: Jan Kugler, FIT
// Přeloženo: gcc 6.3.0
//
// Header pro error.c

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void warning(const char *fmt, ...);
void error_exit(const char *fmt, ...);
