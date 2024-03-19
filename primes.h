// primes.h
// Řešení IJC-DU1, příklad a), 19.3.2024
// Autor: Jan Kugler, FIT
// Přeloženo: gcc 6.3.0
//
// Header pro primes.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "eratosthenes.h"

const unsigned first_twenty_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

unsigned long modular_exp(unsigned long base, unsigned long exponent, unsigned long mod);
unsigned long wilson_check(unsigned long p);
unsigned long primorial(unsigned k);
