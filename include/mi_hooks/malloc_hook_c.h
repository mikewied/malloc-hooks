
#ifndef MALLOC_HOOK_C_H
#define MALLOC_HOOK_C_H

#include "config.h"
#include <stddef.h>
#include <sys/types.h>

#ifndef WIN_DLL_DECL
# ifdef _WIN32
#   define WIN_DLL_DECL  __declspec(dllimport)
# else
#   define WIN_DLL_DECL
# endif
#endif

#ifndef __cplusplus
extern "C" {
#endif

typedef void (*MallocHook_NewHook)(const void* ptr, size_t size);
typedef void (*MallocHook_DeleteHook)(const void* ptr);

WIN_DLL_DECL
int MallocHook_AddNewHook(MallocHook_NewHook hook);
WIN_DLL_DECL
int MallocHook_RemoveNewHook(MallocHook_NewHook hook);

WIN_DLL_DECL
int MallocHook_AddDeleteHook(MallocHook_DeleteHook hook);
WIN_DLL_DECL
int MallocHook_RemoveDeleteHook(MallocHook_DeleteHook hook);

#ifndef __cplusplus
}
#endif

#endif /* MALLOC_HOOK_C_H */