// eratosthenes.c
// Řešení IJC-DU1, příklad a), 19.3.2024
// Autor: Jan Kugler, FIT
// Přeloženo: gcc 6.3.0
//
// Obsahuje implementaci Eratosthenova síta pomocí bitset.h
// Implementuje také integer odmocninu použitou v Eratosthenes

#include "eratosthenes.h"

unsigned long isqrt(unsigned long num){
  // integer square root
  // returns highest integer <= sqrt(num)
  if (num <= 1) return num;
  unsigned long x0, x1, tmpnum;

  // start at the highest power of 2 less than sqrt(num)
  unsigned char shift = 0;
  tmpnum = num;
  while (tmpnum > 1){
    shift++;
    tmpnum >>= 1;
  }
  shift >>= 1;

  x0 = 0x1 << shift;
  x1 = x0 >> 1;
  while (x1 > 0){
    if ((tmpnum = (x0 | x1) * (x0 | x1)) == num) return (x0 | x1);
    x0 = (tmpnum > num) ? x0 : x0 | x1;
    x1 >>= 1;
  }
  return x0;
}

void Eratosthenes(bitset_t bs){
  bitset_index_t bs_size = bitset_size(bs);
  bitset_index_t size_sqrt = isqrt(bs_size);
  bitset_fill(bs, 1);
  bitset_index_t read_ptr = 1, write_ptr = 0, write_step;
  unsigned char read_bit;
  bitset_setbit(bs, 0, 0); // 1 is not prime

  // sieving loop
  while (read_ptr < size_sqrt){
    read_bit = bitset_getbit(bs, read_ptr);
    if (read_bit == 1){
      // start from p^2
      write_ptr = (read_ptr + 1)*(read_ptr + 1) - 1;
      // step size p for 2, 2*p for all others
      write_step = ((read_ptr & 0x1) != 0) ? (read_ptr + 1) : 2*(read_ptr + 1);
      while (write_ptr < bs_size){
        bitset_setbit(bs, write_ptr, 0);
        write_ptr += write_step;
      }
    }
    read_ptr += ((read_ptr & 0x1) != 0) ? 1 : 2;
  }
}

void eratosthenes_get_primes(bitset_t bs, unsigned long *prime_buffer, unsigned prime_target){
  Eratosthenes(bs);
  bitset_index_t bs_size = bitset_size(bs);
  bitset_index_t read_ptr = bs_size - 1;
  unsigned char read_bit;
  // read_ptr is unsigned, so checking for underflow
  while (read_ptr < bs_size && prime_target > 0){
    read_bit = bitset_getbit(bs, read_ptr);
    if (read_bit == 1){
      prime_buffer[--prime_target] = read_ptr + 1;
    }
    read_ptr--;
  }
}
