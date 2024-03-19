// bitset.c
// Řešení IJC-DU1, příklad a), 19.3.2024
// Autor: Jan Kugler, FIT
// Přeloženo: gcc 6.3.0
//
// Header pro bitset.c
// Implementuje bitset_t a makra pro práci s ním

#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

#include "error.h"

// TODO
// formatted assert
// inlines
// clock

typedef unsigned long bitset_index_t;

#define LONG_BSIZE (sizeof(unsigned long) * 8)

typedef struct {
    unsigned long* stuff;
} bitset_t;

// size long + full longs + final long
#define BIT_TO_UL(size) (1 + (size / LONG_BSIZE) + ((size & (sizeof(unsigned long) - 1)) != 0))

#if defined(_WIN32) || defined(_WIN64) // windows
#define MALLOC_SIZE(ptr) _msize(ptr)
#else // linux
#define MALLOC_SIZE(ptr) malloc_usable_size(ptr)
#endif

// Can't put bitset_create and bitset_alloc inside a do-while, the structs don't persist
// I guess just don't use these as the body of single line ifs and fors
#define bitset_create(_name, _size) \
  bitset_index_t _bitset_size = BIT_TO_UL(_size); \
  unsigned long _bitset_stuff[_bitset_size + 1]; \
  _bitset_stuff[0] = (_size); \
  for (unsigned i = 1; i <= _bitset_size; i++) _bitset_stuff[i] = 0x0; \
  bitset_t _name = {_bitset_stuff};

#define bitset_alloc(_name, _size) \
  bitset_index_t _bitset_size = BIT_TO_UL(_size); \
  unsigned long* _bitset_stuff = (unsigned long *)calloc(_bitset_size + 1, sizeof(unsigned long)); \
  assert(((void)"bitset_alloc: Chyba alokace paměti", \
    _bitset_stuff != NULL && \
    MALLOC_SIZE(_bitset_stuff) == (BIT_TO_UL(_size) + 1) * sizeof(_bitset_stuff[0]) )); \
  _bitset_stuff[0] = (_size); \
  bitset_t _name = {_bitset_stuff};

#define bitset_free(_name) free((_name).stuff)

#define bitset_size(_name) ((_name).stuff[0])

#define bitset_fill(_name, _bool) \
  do { \
    unsigned long _fill = (_bool) ? ~0x0 : 0x0; \
    for (unsigned i = 1; i <= BIT_TO_UL((_name).stuff[0]); i++) (_name).stuff[i] = _fill; \
  } while (0);

//TODO somehow shove the formatting into the assert
#define bitset_setbit(_name, _index, _bool) \
  do { \
    if ((_index) >= bitset_size(_name)) error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (_index), bitset_size(_name)); \
    unsigned long _mask = (0x1 << (LONG_BSIZE - 1 - (_index))); \
    bitset_index_t _byte_index = ((_index) / LONG_BSIZE) + 1; \
    (_name).stuff[_byte_index] = (_bool) ? ((_name).stuff[_byte_index] | _mask) : ((_name).stuff[_byte_index] & (~_mask)); \
  } while (0);

//TODO somehow shove the formatting into the assert
#define bitset_getbit(_name, _index) \
  ( \
    (void)(((_index) >= bitset_size(_name)) ? error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (_index), bitset_size(_name)) : (void)printf("")), \
    (unsigned)(((_name).stuff[((_index) / LONG_BSIZE) + 1] & (0x1 << (LONG_BSIZE - 1 - (_index)))) != 0) \
  )


void print_hex_ul(unsigned long ul);
void print_bits(unsigned long ul);
void print_bs(bitset_t bs);
int bitset_test();
