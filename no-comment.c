#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  FILE *fp;
  if (argc > 1){
    fp = fopen(argv[1], "r");
  } else {
    fp = stdin;
  }
  char c;
  while ((c = getc(fp)) != EOF){
    printf("%c %i %i\n", c, c, EOF);
  }
}
