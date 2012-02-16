
#include "malloc_guard.h"
#include "libc_override.h"
#include <iostream>

/* Makes sure windows clients can import these functions */
#ifndef WIN_DLL_DECL
# ifdef _WIN32
#   define WIN_DLL_DECL  __declspec(dllimport)
# else
#   define WIN_DLL_DECL
# endif
#endif

/* Runs before main so no lock needed */
static int mwmallocguard_refcount = 0;

MWMallocGuard::MWMallocGuard() {
    if (mwmallocguard_refcount++ == 0) {
        ReplaceSystemAlloc();
    }
}

MWMallocGuard::~MWMallocGuard() {

}

static MWMallocGuard module_enter_exit_guard;
