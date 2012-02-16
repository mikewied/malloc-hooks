
#include "config.h"
#include <iostream>
#include <assert.h>
#include <mi_hooks/malloc_hook.h>
#include "../src/malloc_hook-inl.h"

static int allocations = 0;

static void new_hook(const void* ptr, size_t size) {
    allocations++;
}

static void delete_hook(const void* ptr) {
    allocations--;
}

static void testAddAndRemoveNewHook() {
    if (!MallocHook::AddNewHook(&new_hook)) {
        std::cout << "Failed to register a new hook";
        exit(1);
    }
    if (!MallocHook::RemoveNewHook(&new_hook)) {
        std::cout << "Failed to remove a new hook";
        exit(1);
    }
}

static void testAddAndRemoveDeleteHook() {
    if (!MallocHook::AddDeleteHook(&delete_hook)) {
        std::cout << "Failed to register a delete hook";
        exit(1);
    }
    if (!MallocHook::RemoveDeleteHook(&delete_hook)) {
        std::cout << "Failed to remove a delete hook";
        exit(1);
    }
}

static void testMallocAndFree() {
    int *x = (int*)malloc(sizeof(int));
    free(x);
}

static void testCallocAndFree() {
    int *x = (int*)calloc(sizeof(int), 10);
    free(x);
}

static void testBasicAllocation() {
    MallocHook::AddNewHook(&new_hook);
    MallocHook::AddDeleteHook(&delete_hook);

    int numAllocs = allocations;
    int *x = (int*)malloc(sizeof(int));
    assert(allocations == numAllocs + 1);
    free(x);
    assert(allocations == numAllocs);

    MallocHook::RemoveNewHook(&new_hook);
    MallocHook::RemoveDeleteHook(&delete_hook);
}
// Test all the different malloc functions


int main() {
    testAddAndRemoveNewHook();
    testAddAndRemoveDeleteHook();
    testMallocAndFree();
    testCallocAndFree();
    testBasicAllocation();
    return 0;
}