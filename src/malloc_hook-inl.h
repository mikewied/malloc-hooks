
#ifndef MALLOC_HOOK_INL_H
#define MALLOC_HOOK_INL_H

#include <cstdlib>
#include <mi_hooks/malloc_hook.h>
#include <iostream>

extern MallocHook_NewHook mi_new_hook;
extern MallocHook_DeleteHook mi_del_hook;

inline void MallocHook::InvokeNewHook(const void* p, size_t s) {
    if (mi_new_hook == NULL) {
        return;
    }
    (mi_new_hook)(p, s);
}

inline void MallocHook::InvokeDeleteHook(const void* p) {
    if (mi_del_hook == NULL) {
        return;
    }
    (mi_del_hook)(p);
}

#endif /* MALLOC_HOOK_INL_H */