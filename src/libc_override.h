
#ifndef LIBC_OVERRIDE_H
#define LIBC_OVERRIDE_H

#include "config.h"
#include "malloc_guard.h"

static void ReplaceSystemAlloc();

#include "libc_override_osx.h";

#endif /* LIBC_OVERRIDE_H */