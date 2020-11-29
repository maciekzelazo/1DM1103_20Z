#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studenci.h"
#include "dziekanat.h"
//to na gorze do studenci.c
//to na dole do dziekanat.c

typedef struct _student {
    char imie[25];
    char nazwisko[50];
    char nr_albumu[10];
    char kod_przed[10];
    char nazwa_przed[255];
    float ocena;
    int ects;
} student, *pstudent;

int main(int argc, char ** argv)
{
    if(strcmp(argv[2], "student") == 0)
    {
        student dane[100];
        int ile;
        ile = wczytaj(dane, argv[1]);
        //wypisz(dane, ile);
        najlepszy_student(dane, ile);
    }
    else if(strcmp(argv[2], "przedmioty") == 0)
    {
        student dane[100];
        int ile;
        ile = wczytaj(dane, argv[1]);
        //wypisz(dane, ile);
        najlepszy_przedmiot(dane, ile);
        najgorszy_przedmiot(dane, ile);
    }

    return 0;
}