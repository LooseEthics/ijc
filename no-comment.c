#include <stdio.h>
#include <stdlib.h>

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

/*
int trigraphs_exist(){
  // funny function ?? /
  return 0;
  return 1;
}
*/

/*\*/
/**\
/

void buffer_add(buffer_t *buffer, char c){
  //printf("buffer add %c to %u\n", c, buffer->i);
  if (buffer->i >= buffer->imax) exit(EXIT_FAILURE);
  buffer->b[buffer->i++] = c;
}

void buffer_write(buffer_t *buffer){
  for (unsigned i = 0; i < buffer->i; i++){
    putchar(buffer->b[i]);
    buffer->b[i] = 0;
  }
  buffer->i = 0;
}

void buffer_clean(buffer_t *buffer){
  for (unsigned i = 0; i < buffer->i; i++){
    buffer->b[i] = 0;
  }
  buffer->i = 0;
}

int main(int argc, char *argv[]){
  FILE *fp;
  if (argc > 1){
    fp = fopen(argv[1], "r");
  } else {
    fp = stdin;
  }

  char c;
  buffer_t buffer = {.b = {0}, .i = 0, .imax = 16};
  enum State s = CODE, olds;
  while ((c = getc(fp)) != EOF){
    //printf("%c %i\n", c, c);
    //printf("%c", c);
    olds = s;
    //continue;
    switch (s){
      case CODE:
        if (c == '/'){
          s = SLASH;
          buffer_add(&buffer, c);
        } else if (c == '"'){
          s = STRLIT;
          putchar(c);
        } else if (c == '\''){
          s = CHARLIT;
          putchar(c);
        } else {
          putchar(c);
        }
        break;
      case SLASH:
        //printf("in state SLASH with %c\n", c);
        if (c == '/'){
          s = LINE_COM;
          buffer_clean(&buffer);
        } else if (c == '*'){
          s = MULTILINE_COM;
          buffer_clean(&buffer);
        } else if (c == '\\'){
          s = SLASH_BS;
          buffer_add(&buffer, c);
        } else if (DO_TRIGRAPHS && c == '?'){
          s = SLASH_Q1;
          buffer_add(&buffer, c);
        } else {
          // not a comment start
          s = CODE;
          buffer_write(&buffer);
        }
        break;
      case SLASH_BS:
        if (c == '\n'){
          s = SLASH;
          buffer_add(&buffer, c);
        } else {
          s = CODE;
          buffer_write(&buffer);
        }
        break;
      case SLASH_Q1:
        if (c == '?'){
          s = SLASH_Q2;
          buffer_add(&buffer, c);
        } else {
          s = CODE;
          buffer_write(&buffer);
        }
        break;
      case SLASH_Q2:
        if (c == '/'){
          s = SLASH_BS;
          buffer_add(&buffer, c);
        } else {
          s = CODE;
          buffer_write(&buffer);
        }
        break;
      case LINE_COM:
        if (c == '\n'){
          s = CODE;
          putchar('\n'); // line comments can have code on the same line, so let's preserve the line breaks and not squish two code lines into one
        } else if (c == '\\'){
          s = LINE_BS;
        } else if (DO_TRIGRAPHS && c == '?'){
          s = LINE_Q1;
        } else {
          // line comment continues - do nothing here
          ;;
        }
        break;
      case LINE_BS:
        // eat any char
        s = LINE_COM;
        break;
      case LINE_Q1:
        if (c == '?'){
          s = LINE_Q2;
        } else {
          s = LINE_COM;
        }
        break;
      case LINE_Q2:
        if (c == '/'){
          s = LINE_BS;
        } else {
          s = LINE_COM;
        }
        break;
      case MULTILINE_COM:
        if (c == '*'){
          s = MULTILINE_STAR;
        } else {
          // comment continues - do nothing here
          ;;
        }
        break;
      case MULTILINE_STAR:
        if (c == '/'){
          // multiline end
          s = CODE;
        } else if (c == '\\'){
          s = MLS_BS;
        } else if (c == '?'){
          s = MLS_Q1;
        } else {
          // false flag
          s = MULTILINE_COM;
        }
        break;
      case MLS_BS:
        if (c == '\n'){
          s = MULTILINE_STAR;
        } else {
          s = MULTILINE_COM;
        }
        break;
      case MLS_Q1:
        if (c == '?'){
          s = MLS_Q2;
        } else {
          s = MULTILINE_COM;
        }
        break;
      case MLS_Q2:
        if (c == '/'){
          s = MLS_BS;
        } else {
          s = MULTILINE_COM;
        }
        break;
      case STRLIT:
        if (c == '"'){
          s = CODE;
        } else if (c == '\\'){
          s = STRLIT_BS;
        } else if (DO_TRIGRAPHS && c == '?'){
          s = STRLIT_Q1;
        } else {
          // continue string - do nothing here
          ;;
        }
        putchar(c);
        break;
      case STRLIT_BS:
        // eat any char
        s = LINE_COM;
        putchar(c);
        break;
      case STRLIT_Q1:
        if (c == '?'){
          s = STRLIT_Q2;
        } else {
          s = STRLIT;
        }
        putchar(c);
        break;
      case STRLIT_Q2:
        if (c == '/'){
          s = STRLIT_BS;
        } else {
          s = STRLIT;
        }
        putchar(c);
        break;
      case CHARLIT:
        if (c == '\\'){
          s = CLBS;
        } else if (DO_TRIGRAPHS && c == '?'){
          s = CLQ1;
        } else {
          s = CLDONE;
        }
        putchar(c);
        break;
      case CLBS:
        if (c == '\n'){
          s = CHARLIT;
        } else if (DO_TRIGRAPHS && c == '?'){
          s = CLBSQ1;
        } else {
          s = CLDONE;
        }
        putchar(c);
        break;
      case CLQ1:
        if (c == '?'){
          s = CLQ2;
        } else {
          s = CLDONE;
        }
        putchar(c);
        break;
      case CLQ2:
        if (c == '/'){
          s = CLBS;
        } else {
          s = CLDONE;
        }
        putchar(c);
        break;
      case CLBSQ1:
        if (c == '?'){
          s = CLBSQ2;
        } else {
          s = CLDONE;
        }
        putchar(c);
        break;
      case CLBSQ2:
        if (c == '\n'){
          s = CLBS;
        } else {
          s = CLDONE;
        }
        putchar(c);
        break;
      case CLDONE:
        // this should always be the final '
        s = CODE;
        putchar(c);
        break;
    }
    if (olds != s){
      //printf("\nState change %u -> %u on char %c(%u)\n", olds, s, c, c);
      ;
    }
  }

  if (argc > 1) fclose(fp);
}
