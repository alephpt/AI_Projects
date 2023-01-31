#include "Kernel.h"
#include <stdio.h>

static inline void oneXone (int* r, int* c) { *r = 1; *c = 1; }
static inline void oneXthree (int* r, int* c) { *r = 1; *c = 3; }
static inline void oneXn (int* r, int* c, int n) { *r = 1; *c = n; }
static inline void threeXone (int* r, int* c) { *r = 3; *c = 1; }
static inline void nXone (int* r, int* c, int n) { *r = n; *c = 1; }
static inline void threeXthree (int* r, int* c) { *r = 3; *c = 3; }
static inline void fiveXfive (int* r, int* c) { *r = 5; *c = 5; }

static inline void invalidFilter (int* r, int* c) {
    printf(" [Kernel Filter Error]: Invalid implementation of Kernel Filter for non-N type.\n");
}

static inline void invalidNFilter (int* r, int* c, int n) {
    printf(" [Kernel Filter Error]: Invalid implementation of Kernel Filter for N type.\n");
}

static inline void (*lookupFilter[])(int* r, int* c) = {
    oneXone, oneXthree, invalidFilter, threeXone, invalidFilter, threeXthree, fiveXfive
};

static inline void (*lookupNFilter[])(int* r, int* c, int n) = {
    invalidNFilter, invalidNFilter, oneXn, invalidNFilter, nXone, invalidNFilter, invalidNFilter
};

Kernel* initKernel (FilterDimensions filter) {
    Kernel* k = new Kernel;
    lookupFilter[filter](&k->rows, &k->columns);
    k->values = std::vector(k->rows, std::vector(k->columns, 0.0f));
    return k;
}

Kernel* initKernel (FilterDimensions filter, int n) {
    Kernel* k = new Kernel;
    lookupNFilter[filter](&k->rows, &k->columns, n);
    k->values = std::vector(k->rows, std::vector(k->columns, 0.0f));
    return k;
}