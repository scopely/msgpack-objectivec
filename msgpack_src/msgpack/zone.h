/*
 * MessagePack for C memory pool implementation
 *
 * Copyright (C) 2008-2010 FURUHASHI Sadayuki
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#ifndef MSGPACK_ZONE_H__
#define MSGPACK_ZONE_H__

#include "sysdep.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup msgpack_zone Memory zone
 * @ingroup msgpack
 * @{
 */

typedef struct msgpack_zone_finalizer {
	void (*func)(void* data);
	void* data;
} msgpack_zone_finalizer;

typedef struct msgpack_zone_finalizer_array {
	msgpack_zone_finalizer* tail;
	msgpack_zone_finalizer* end;
	msgpack_zone_finalizer* array;
} msgpack_zone_finalizer_array;

struct msgpack_zone_chunk;
typedef struct msgpack_zone_chunk msgpack_zone_chunk;

typedef struct msgpack_zone_chunk_list {
	size_t free;
	char* ptr;
	msgpack_zone_chunk* head;
} msgpack_zone_chunk_list;

typedef struct msgpack_zone {
	msgpack_zone_chunk_list chunk_list;
	msgpack_zone_finalizer_array finalizer_array;
	size_t chunk_size;
} msgpack_zone;

#ifndef MSGPACK_ZONE_CHUNK_SIZE
#define MSGPACK_ZONE_CHUNK_SIZE 8192
#endif

bool msgpack_zone_init(msgpack_zone* zone, size_t chunk_size);
void msgpack_zone_destroy(msgpack_zone* zone);

msgpack_zone* msgpack_zone_new(size_t chunk_size);
void msgpack_zone_free(msgpack_zone* zone);

extern void* msgpack_zone_malloc(msgpack_zone* zone, size_t size);
static inline void* msgpack_zone_malloc_no_align(msgpack_zone* zone, size_t size);

extern bool msgpack_zone_push_finalizer(msgpack_zone* zone,
		void (*func)(void* data), void* data);

extern void msgpack_zone_swap(msgpack_zone* a, msgpack_zone* b);

bool msgpack_zone_is_empty(msgpack_zone* zone);

void msgpack_zone_clear(msgpack_zone* zone);

/** @} */


#ifndef MSGPACK_ZONE_ALIGN
#define MSGPACK_ZONE_ALIGN sizeof(int)
#endif

#ifdef __cplusplus
}
#endif

#endif /* msgpack/zone.h */

