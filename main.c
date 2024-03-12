#include "bitset.h"
#include <stdio.h>

void print_hex_ul(char ul){
  char nibble;
  char hibble;
  for (int i = 28; i > 0; i -= 4){
    nibble = (ul >> i) & 0xf;
    hibble = (nibble < 0x9) ? nibble + '0' : nibble + 'a' - 0xa;
    printf("%c", hibble);
  }
  printf(" ");
}

void print_bs(bitset_t bs){
  printf("Size: %lu", bs.stuff[0]);
  for (unsigned i = 1; i < BIT_TO_UL(bs.size); i++){
    if (!(i & 0x7)) printf("\n");
    print_hex_ul(bs.stuff[i]);
    //printf("%lu ", bs.stuff[i]);
  }
  printf("\n");
}

int main(){
    bitset_create(a, 33);
    print_bs(a);
    bitset_fill(a, 1);
    print_bs(a);
    bitset_fill(a, 0);
    print_bs(a);
    bitset_setbit(a, 10, 1);
    bitset_setbit(a, 20, 1);
    print_bs(a);
    bitset_free(a);
    return 0;
}
