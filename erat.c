#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  //
  // time data (with printf overhead):
  // start - number interval: time - average time per function call
  // 0 - 10k: 0.362 s - 36.2 us
  // 10k - 10k: 0.653 s - 65.3 us
  // 0 - 100k: 12.6 s - 0.126 ms
  // 100k - 100k: 32.6 s - 0.326 ms
  // 500k - 10k: 8.73 s - 0.873 ms
  // 1M - 10k: 16.5 s - 1.65 ms
  // 2M - 10k: 29.6 s - 2.96 ms
  // 2M - 1k: 3.04 s - 3.04 ms
  // 5M - 1k: 6.52 s - 6.52 ms
  // 10M - 1k: 12.33 s - 12.33 ms
  // 50M - 1k: 59.8 s - 59.8 ms
  if (p < 2) return 0;
  unsigned long long factorial = 1;
  for (unsigned long i = 2; i < p; i++){
    factorial *= i;
    factorial = (factorial >= p) ? factorial % p : factorial;
    if (factorial == 0) return 0; // <= this line reduces average runtime by a factor of 4
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
  clock_t start, end;
  double cpu_time_used;
  //unsigned long n = 5000000;
  //unsigned long nstart = n;
  //unsigned primes_found = 0;
  unsigned istart = 50000000;
  unsigned interval = 1000;
  start = clock();
  for (unsigned i = istart; i < istart + interval; i++){
    if (wilson_check(i) != 0){
      printf("%lu\n", i);
      ;
    }
  }
  /*while (primes_found < 10){
    if (wilson_check(n) != 0){
      printf("%lu\n", n);
      primes_found++;
    }
    n--;
  }
  */
  /*while (nstart - n < 1000){
    if (wilson_check(n) != 0){
      printf("%lu\n", n);
    }
    n--;
  }
  */
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used: %f seconds\n", cpu_time_used);
  return 0;
}
