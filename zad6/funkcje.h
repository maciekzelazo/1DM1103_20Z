#ifndef funkcje_h
#define funkcje_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct macierz
{
    int r;
    int c;
    float **tab;
};

void wczytaj1(FILE * fin1, struct macierz *m);
void wypisz1(struct macierz m);
void zapisz(char nazwa[], struct macierz m);
void zwolnij(struct macierz *m);
#endif
