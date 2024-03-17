#include "bitset.h"
#include <stdio.h>

void print_hex_ul(unsigned long ul){
  char nibble;
  char hibble;
  for (int i = 28; i >= 0; i -= 4){
    nibble = (ul >> i) & 0xf;
    hibble = (nibble <= 0x9) ? nibble + '0' : nibble + 'a' - 0xa;
    printf("%c", hibble);
  }
  printf(" ");
}

void print_bits(unsigned long ul){
  for (int i = sizeof(unsigned long)*8 - 1; i >= 0; i--){
    printf("%i", (ul & (0x1 << i)) != 0);
  }
  printf(" ");
}

void print_bs(bitset_t bs){
  printf("Size: %lu\n", bs.stuff[0]);
  print_bits(bs.stuff[0]);
  for (unsigned i = 1; i < BIT_TO_UL(bs.stuff[0]); i++){
    if (!((i - 1) & 0x3)) printf("\n");
    print_bits(bs.stuff[i]);
  }
  printf("\n");
  print_hex_ul(bs.stuff[0]);
  for (unsigned i = 1; i < BIT_TO_UL(bs.stuff[0]); i++){
    if (!((i - 1) & 0x3)) printf("\n");
    print_hex_ul(bs.stuff[i]);
  }
  printf("\n");
}

int main(){
    bitset_index_t size = 241;
    printf("bitset_create(a, %i);\n", size);
    bitset_create(a, size);
    print_bs(a);
    printf("bitset_fill(a, 1);\n");
    bitset_fill(a, 1);
    print_bs(a);
    printf("bitset_fill(a, 0);\n");
    bitset_fill(a, 0);
    print_bs(a);
    printf("bitset_setbit(a, 10, 1);\nbitset_setbit(a, 20, 1);\n");
    bitset_setbit(a, 10, 1);
    bitset_setbit(a, 20, 1);
    print_bs(a);
    unsigned bit = (bitset_getbit(a, 10));
    printf("%u\n", bit);
    bitset_free(a);
    return 0;
}
