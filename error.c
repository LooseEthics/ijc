// error.c
// Řešení IJC-DU1, příklad b), 19.3.2024
// Autor: Jan Kugler, FIT
// Přeloženo: gcc 6.3.0
//
// Obsahuje funkce pro tisk varování a chyb

#include "error.h"

void warning(const char *fmt, ...){
  va_list vl;
  va_start(vl, fmt);
  vfprintf(stderr, "Warning: ", NULL);
  vfprintf(stderr, fmt, vl);
}

void error_exit(const char *fmt, ...){
  va_list vl;
  va_start(vl, fmt);
  vfprintf(stderr, "Error: ", NULL);
  vfprintf(stderr, fmt, vl);
  exit(1);
}
