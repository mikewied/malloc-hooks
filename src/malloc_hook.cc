
#include <mi_hooks/malloc_hook.h>
#include "malloc_hook-inl.h"
#include <iostream>

MallocHook_NewHook mi_new_hook = 0;
MallocHook_DeleteHook mi_del_hook = 0;

extern "C"
int MallocHook_AddNewHook(MallocHook_NewHook hook) {
    if (mi_new_hook != NULL) {
        return 0;
    }
    mi_new_hook = hook;
    return 1;
}

extern "C"
int MallocHook_RemoveNewHook(MallocHook_NewHook hook) {
    if (mi_new_hook == NULL) {
        return 0;
    }
    mi_new_hook = NULL;
    return 1;
}

extern "C"
int MallocHook_AddDeleteHook(MallocHook_DeleteHook hook) {
    if (mi_del_hook != NULL) {
        return 0;
    }
    mi_del_hook = hook;
    return 1;
}

extern "C"
int MallocHook_RemoveDeleteHook(MallocHook_DeleteHook hook) {
    if (mi_del_hook == NULL) {
        return 0;
    }
    mi_del_hook = NULL;
    return 1;
}