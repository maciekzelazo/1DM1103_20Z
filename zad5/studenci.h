#ifndef _studenci_h
#define _studenci_h
#include "dziekanat.h"



int wczytaj(student dane[100], char *fnazwa);
void wypisz(student dane[100], int n);
int znajdz(char *szukany_nr, char nr_albumow[100][10], int n);
int znajdz2(char *szukany_kod, char kod_przedm[100][10], int n);
int znajdz_przedmioty(char kod_przedm[100][10], student dane[100], int n);
int znajdz_studentow(char nr_albumow[100][10], student dane[100], int n);

#endif
