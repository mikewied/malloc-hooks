
#ifndef LIBC_OVERRIDE_H
#define LIBC_OVERRIDE_H

#include "config.h"
#include "malloc_guard.h"

static void ReplaceSystemAlloc();

#if defined(__APPLE__)
#include "libc_override_osx.h";

#else
#error Need to add support for your libc/os here
#endif

#endif /* LIBC_OVERRIDE_H */