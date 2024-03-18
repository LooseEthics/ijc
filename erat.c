#include <stdio.h>
#include <stdlib.h>

#include "erat.h"

unsigned long modular_exp(unsigned long base, unsigned long exponent, unsigned long mod){
  // (a * b) mod m = (a mod m)*(b mod m) mod m
  // therefore
  // a^n mod m = product of [a^((2^i)*c_i) mod m] mod m
  // where c_i is 0 or 1 based on the bits of n
  if (exponent == 0) return 1;
  unsigned long long nth_square = (base >= mod) ? (base % mod) : base;
  unsigned long long out = (exponent & 0x1) ? nth_square : 1;
  unsigned i = 1;
  exponent >>= 1;
  while (exponent > 0){
    i++;
    nth_square *= nth_square;
    nth_square = (nth_square >= mod) ? (nth_square % mod) : nth_square;
    if (exponent & 0x1){
      out *= nth_square;
      out = (out >= mod) ? (out % mod) : out;
    }
    exponent >>= 1;
  }
  return out;
}

unsigned long wilson_check(unsigned long p){
  // Wilson's theorem
  // p>1 is prime <=> (p-1)! = p-1 mod p
  if (p < 2) return 0;
  unsigned long long factorial = 1;
  for (unsigned long i = 2; i < p; i++){
    factorial *= i;
    factorial = (factorial >= p) ? factorial % p : factorial;
  }
  return (factorial == p - 1) ? p : 0;
}

unsigned long primorial(unsigned k){
  // product of first k primes
  // primorial(10) doesn't fit into 32 bits
  // primorial(16) doesn't fit into 64 bits
  if (k > 15 || (k > 9 && (sizeof(unsigned long) <= 4))) return ~0;
  unsigned long out = 1;
  for (unsigned i = 0; i < k; i++) out *= first_twenty_primes[i];
  return out;
}

int main(){
  /*for (int i = 0; i < 11; i++){
    printf("%u %lu\n", i, primorial(i));
  }*/
  //printf("%lu\n", modular_exp(2, 41, 42));
  //printf("%lu\n", modular_exp(1350421767, 1238954434, 1890836600));
  for (int i = 15485863; i < 15485864; i++){
    printf("%i is %sprime\n", i, wilson_check(i) ? "" : "not ");
  }
  unsigned a[] = {2, 3, 5, 7, 11, 13};
  generate_euclidean_primes(a, 4);
  return 0;
}
