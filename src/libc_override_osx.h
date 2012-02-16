
#ifndef LIBC_OVERRIDE_OSX
#define LIBC_OVERRIDE_OSX

#include "config.h"
#include "malloc_hook-inl.h"

#include <iostream>
#include <cstring>
#include <AvailabilityMacros.h>
#include <malloc/malloc.h>
#include <mi_hooks/malloc_hook.h>

static void* (*system_calloc)(malloc_zone_t*, size_t, size_t);
static void* (*system_malloc)(malloc_zone_t*, size_t);
static void* (*system_realloc)(malloc_zone_t*, void*, size_t);
static void* (*system_valloc)(malloc_zone_t*, size_t);
static void  (*system_free)(malloc_zone_t*, void*);
static void  (*system_free_definite_size)(malloc_zone_t*, void*, size_t);

namespace  {
    void* mz_calloc(malloc_zone_t* zone, size_t num_items, size_t size) {
        void* ptr = (system_calloc)(zone, num_items, size);
        MallocHook::InvokeNewHook(ptr, num_items * size);
        return ptr;
    }

    void* mz_malloc(malloc_zone_t* zone, size_t size) {
        void* ptr = (system_malloc)(zone, size);
        MallocHook::InvokeNewHook(ptr, size);
        return ptr;
    }

    void* mz_realloc(malloc_zone_t* zone, void* ptr, size_t size) {
        // Need to add hook stuff here.
        return (system_realloc)(zone, ptr, size);
    }

    void* mz_valloc(malloc_zone_t* zone, size_t size) {
        return (system_valloc)(zone, size);
    }

    void mz_free(malloc_zone_t* zone, void* ptr) {
        MallocHook::InvokeDeleteHook(ptr);
        (system_free)(zone, ptr);
    }

    void  mz_free_definite_size(malloc_zone_t* zone, void* ptr, size_t size) {
        MallocHook::InvokeDeleteHook(ptr);
        (system_free_definite_size)(zone, ptr, size);
    }
}

static void ReplaceSystemAlloc() {
    static malloc_zone_t* default_zone = malloc_default_zone();
    system_calloc = default_zone->calloc;
    system_malloc = default_zone->malloc;
    system_realloc = default_zone->realloc;
    system_valloc = default_zone->valloc;
    system_free = default_zone->free;

    default_zone->calloc = &mz_calloc;
    default_zone->malloc = &mz_malloc;
    default_zone->realloc = &mz_realloc;
    default_zone->valloc = &mz_valloc;
    default_zone->free = &mz_free;

#if defined(MAC_OS_X_VERSION_10_6) && \
    MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
    if (default_zone->version >= 6 && default_zone->free_definite_size) {
        system_free_definite_size = default_zone->free_definite_size;
        default_zone->free_definite_size = mz_free_definite_size;
    }
#endif

}

#endif /* LIBC_OVERRIDE_OSX */