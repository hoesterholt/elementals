//
//  memblock.h
//  
//
//  Created by fam. Oesterholt on 15-02-13.
//
//

#ifndef _memblock_h
#define _memblock_h

#include <stdio.h>

#ifndef EL_LINUX

#ifdef __off_t_defined
#define MEMBLOCK_OFF_T
#endif

#ifdef _OFF_T
#define MEMBLOCK_OFF_T
#endif

#ifndef MEMBLOCK_OFF_T
typedef long off_t;
#endif

#endif // EL_LINUX

typedef struct {
  void *block;
  size_t size;
  off_t pos;
} memblock_t;

memblock_t *memblock_new();
void        memblock_clear(memblock_t *blk);
void        memblock_write(memblock_t *blk, const void *bytes, size_t size);
size_t      memblock_read(memblock_t *blk, void *buf, size_t size);
off_t       memblock_seek(memblock_t *blk, off_t pos);
void        memblock_destroy(memblock_t *blk);
size_t      memblock_size(memblock_t *blk);
off_t       memblock_pos(memblock_t *blk);

// beware! memblock needs to be '\0' terminated!
const char* memblock_as_str(memblock_t* blk);
void memblock_concat(memblock_t* blk, const char* str);

#endif
