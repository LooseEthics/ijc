// no-comment.h
// Řešení IJC-DU1, příklad b), 19.3.2024
// Autor: Jan Kugler, FIT
// Přeloženo: gcc 6.3.0
//
// Header pro no-comment.c
// DO_TRIGRAPHS určuje zda se ?? / interpretuje jako backslash

#include <stdio.h>
#include <stdlib.h>

#include "error.h"

#define DO_TRIGRAPHS 1

enum State{
  CODE,
  SLASH,
  SLASH_BS,
  SLASH_Q1,
  SLASH_Q2,
  LINE_COM,
  LINE_BS,
  LINE_Q1,
  LINE_Q2,
  MULTILINE_COM,
  MULTILINE_STAR,
  MLS_BS,
  MLS_Q1,
  MLS_Q2,
  STRLIT,
  STRLIT_BS,
  STRLIT_Q1,
  STRLIT_Q2,
  CHARLIT,
  CLBS,
  CLQ1,
  CLQ2,
  CLBSQ1,
  CLBSQ2,
  CLDONE
};

const char *state_name[] = {
  "CODE",
  "SLASH",
  "SLASH_BS",
  "SLASH_Q1",
  "SLASH_Q2",
  "LINE_COM",
  "LINE_BS",
  "LINE_Q1",
  "LINE_Q2",
  "MULTILINE_COM",
  "MULTILINE_STAR",
  "MLS_BS",
  "MLS_Q1",
  "MLS_Q2",
  "STRLIT",
  "STRLIT_BS",
  "STRLIT_Q1",
  "STRLIT_Q2",
  "CHARLIT",
  "CLBS",
  "CLQ1",
  "CLQ2",
  "CLBSQ1",
  "CLBSQ2",
  "CLDONE"
};

typedef struct Buffer{
  // technically you could have a source code that goes / \ \n \ \n \ \n ...
  // that alone could be solved with a repetition counter
  // but replace some of those \ with trigraphs and this thing becomes incompressible
  // of course I could just store trigraphs as \, but that could transform the input in a way that's outside the specification, so let's not do that
  // the biggest thing that's not something stupid like that that could get stored here is the following
  // / ? ? / \n
  // 47 63 63 47 10
  char b[16];
  unsigned i;
  unsigned imax;
} buffer_t;

int trigraphs_exist();
void buffer_add(buffer_t *buffer, char c);
void buffer_write(buffer_t *buffer);
void buffer_clean(buffer_t *buffer);
