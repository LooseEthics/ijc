#include <stdlib.h>
#include <assert.h>
#include <malloc.h>

typedef unsigned long bitset_index_t;

typedef struct {
    bitset_index_t size; // size in bits, not bytes
    char* bytes;
} bitset_t;

#define BIT_TO_BYTE(size) ((size >> 3) + ((size & 0x7) != 0))

#if defined(_WIN32) || defined(_WIN64) // windows
#define MALLOC_SIZE(ptr) _msize(ptr)
#else // linux
#define MALLOC_SIZE(ptr) malloc_usable_size(ptr)
#endif

// I'd rather wrap bitset_create and bitset_alloc inside a do-while, but then the structs don't persist
// I guess just don't use these as the body of single line ifs and fors
#define bitset_create(_name, _size) \
  bitset_index_t _bitset_size = BIT_TO_BYTE(_size); \
  char _bitset_bytes[_bitset_size]; \
  for (unsigned i = 0; i < _bitset_size; i++) _bitset_bytes[i] = 0x0; \
  bitset_t _name = {_size, _bitset_bytes};

#define bitset_alloc(_name, _size) \
  bitset_index_t _bitset_size = BIT_TO_BYTE(_size); \
  bitset_t _name = {_size, NULL}; \
  _name.bytes = (char *)calloc(_bitset_size, sizeof(char)); \
  assert(((void)"bitset_alloc: Chyba alokace paměti", \
    _name.bytes != NULL && \
    MALLOC_SIZE(_name.bytes) == BIT_TO_BYTE(_name.size) * sizeof(_name.bytes[0]) ));

#define bitset_free(_name) free(_name.bytes)

#define bitset_size(_name) (_name.size)

#define bitset_fill(_name, _bool) \
  do { \
    unsigned char _fill = (_bool) ? 0xff : 0x0; \
    for (unsigned i = 0; i < BIT_TO_BYTE(_name.size); i++) _name.bytes[i] = _fill; \
  } while (0);

#define bitset_setbit(_name, _index, _bool) \
  do { \
    unsigned char _mask = 0x1 << (_index % 8); \
    bitset_index_t _byte_index = _index >> 3; \
    _name.bytes[_byte_index] = (_bool) ? (_name.bytes[_byte_index] | _mask) : (_name.bytes[_byte_index] & (~_mask)); \
  } while (0);

#define bitset_getbit(_name, _index) (((_name.bytes[(_index >> 3)] & (0x1 << (_index % 8))) == 0) ? 0 : 1)
