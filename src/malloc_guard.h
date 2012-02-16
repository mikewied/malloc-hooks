
#ifndef MW_MALLOC_H
#define MW_MALLOC_H

class MWMallocGuard {
public:
    MWMallocGuard();
    ~MWMallocGuard();
};

#endif /* MW_MALLOC */