#pragma once
#include <stdlib.h>

#define mKE 0x100000000LL
#define cKE 0xB16
#define aKE 0x5DEECE66DLL

static unsigned long long seed = 1;

double drand48(void);

void srand48(unsigned int i);
