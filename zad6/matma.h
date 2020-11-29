#ifndef matma_h
#define matma_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "funkcje.h"

struct macierz sum(struct macierz m, struct macierz n);
struct macierz subtract(struct macierz m, struct macierz n);
float norm(struct macierz m);
struct macierz prod(struct macierz m, struct macierz n);
struct macierz multiply(struct macierz m, float skalar);

#endif