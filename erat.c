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

unsigned count_bits(unsigned num){
  unsigned out = 0;
  while (num > 0){
    out += (num & 0x1) ? 1 : 0;
    num >>= 1;
  }
  return out;
}

void generate_euclidean_primes(unsigned *initial_primes, unsigned initial_len){
  unsigned pick_size = 1;
  unsigned mask = 0;
  unsigned tmp_mask, j, product;
  unsigned mask_max = 0x1 << initial_len;
  unsigned euclideans[20] = {0}, e = 0;
  printf("initials: ");
  for (unsigned i = 0; i < initial_len; i++){
    printf("%u, ", initial_primes[i]);
  }
  printf("\n");
  while (pick_size <= initial_len){
    //printf("pick size %u\n", pick_size);
    while (mask < mask_max){
      //printf("%u\n", mask);
      if (count_bits(mask) == pick_size){
        //printf("%u\n", mask);
        //printf("primes selected: ");
        tmp_mask = mask;
        j = 0;
        product = 1;
        while (tmp_mask > 0){
          if (tmp_mask & 0x1){
            //printf("%u, ", initial_primes[j]);
            product *= initial_primes[j];
          }
          tmp_mask >>= 1;
          j++;
        }
        //printf("\nproduct: %u\n", product);
        if (wilson_check((unsigned long)product + 1)){
          euclideans[e++] = product + 1;
        }
      } // count_bits
      mask++;
    } //mask
    mask = 0;
    pick_size++;
  } //pick_size
  printf("euclideans: ");
  for (unsigned i = 0; euclideans[i] != 0; i++){
    printf("%u, ", euclideans[i]);
  }
  printf("\n");
}

int APR_check(unsigned long p){
  // APR test
  // as described in 10.2307/2006975
  //unsigned long initial_primes[] = {2}, euclidean_primes[] = {3}; // P(E) = 3, P(E)^2 = 9
  //unsigned long initial_primes[] = {2, 3}, euclidean_primes[] = {3, 7}; // P(E) = 21, P(E)^2 = 441
  //unsigned long initial_primes[] = {2, 5}, euclidean_primes[] = {3, 11}; // P(E) = 33, P(E)^2 = 1089
  // {2, 7} useless
  //unsigned long initial_primes[] = {2, 11}, euclidean_primes[] = {3, 23}; // P(E) = 69, P(E)^2 = 4761
  //unsigned long initial_primes[] = {2, 3, 5}, euclidean_primes[] = {3, 7, 11, 31}; // P(E) = 7161, P(E)^2 = 51 279 921
  //unsigned long initial_primes[] = {2, 5, 7}, euclidean_primes[] = {3, 11, 23, 71}; // P(E) = 53 889, P(E)^2 = 2 904 024 321
  //unsigned long initial_primes[] = {2, 3, 5, 7}, euclidean_primes[] = {3, 7, 11, 31, 43, 71, 211}; // P(E) = 4 612 994 463, P(E)^2 > 21*10^18
  return p;
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
