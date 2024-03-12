#include "bitset.h"
#include <stdio.h>

void print_hex_char(char c){
  char ntop = (c >> 4) & 0xf;
  char htop = (ntop < 0x9) ? ntop + '0' : ntop + 'a' - 0xa;
  char nbot = c & 0xf;
  char hbot = (nbot < 0x9) ? nbot + '0' : nbot + 'a' - 0xa;
  printf("%c%c ", htop, hbot);
}

void print_bs(bitset_t bs){
  printf("Size: %i", bs.size);
  for (unsigned i = 0; i < BIT_TO_BYTE(bs.size); i++){
    if (!(i & 0x7)) printf("\n");
    print_hex_char(bs.bytes[i]);
  }
  printf("\n");
}

int main(){
    bitset_create(a, 250);
    print_bs(a);
    bitset_fill(a, 1);
    print_bs(a);
    bitset_fill(a, 0);
    print_bs(a);
    bitset_free(a);
    return 0;
}
