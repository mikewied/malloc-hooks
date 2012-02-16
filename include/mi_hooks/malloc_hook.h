
#ifndef MALLOC_HOOK_H
#define MALLOC_HOOK_H

extern "C" {
#include <mi_hooks/malloc_hook_c.h>
}

/* Makes sure windows clients can import these functions */
#ifndef WIN_DLL_DECL
# ifdef _WIN32
#   define WIN_DLL_DECL  __declspec(dllimport)
# else
#   define WIN_DLL_DECL
# endif
#endif

/* The C++ methods below call the C version (MallocHook_*), and thus
 * convert between an int and a bool.  Windows complains about this
 * (a "performance warning") which we don't care about, so we suppress.
 */
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4800)
#endif

class WIN_DLL_DECL MallocHook {
public:
    typedef MallocHook_NewHook NewHook;
    typedef MallocHook_DeleteHook DeleteHook;

    inline static bool AddNewHook(NewHook hook) {
        return MallocHook_AddNewHook(hook);
    }

    inline static bool RemoveNewHook(NewHook hook) {
        return MallocHook_RemoveNewHook(hook);
    }

    inline static void InvokeNewHook(const void* p, size_t s);

    inline static bool AddDeleteHook(DeleteHook hook) {
        return MallocHook_AddDeleteHook(hook);
    }

    inline static bool RemoveDeleteHook(DeleteHook hook) {
        return MallocHook_RemoveDeleteHook(hook);
    }

    inline static void InvokeDeleteHook(const void* p);
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif /* MALLOC_HOOK_H */