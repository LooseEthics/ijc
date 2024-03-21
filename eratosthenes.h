// eratosthenes.h
// Řešení IJC-DU1, příklad a), 19.3.2024
// Autor: Jan Kugler, FIT
// Přeloženo: MinGW 6.3.0, Ubuntu 9.4.0
//
// Header pro eratosthenes.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bitset.h"

void Eratosthenes(bitset_t bs);
void eratosthenes_get_primes(bitset_t bs, unsigned long *prime_buffer, unsigned prime_target);
