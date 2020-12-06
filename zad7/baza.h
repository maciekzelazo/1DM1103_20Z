#ifndef _BAZA_H
#define _BAZA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Student 
{
    char * imie;
    char * nazwisko;
    char * nr_albumu;
    char * email;

    struct _Student *nast;
} Student;

typedef struct _Przedmiot 
{
     char * kod_przed;
     char * nazwa_przed;
     char * sem;

     struct _Przedmiot *nast;
} Przedmiot;

 typedef struct _Ocena 
 {
    char * nr_albumu;
    char * kod_przed;
    char * ocena;
    char * komentarz;
    struct _Ocena *nast;
 } Ocena;

typedef struct _SBaza 
{
    Student * lista_studentow; 
    Przedmiot * lista_przedmiotow;
    Ocena * lista_ocen;    
} SBaza;

SBaza * wczytaj_baze(char *nazwa_pliku);
SBaza * zapisz_baze(char *nazwa_pliku, SBaza * baza);
Ocena * wczytaj_oceny(FILE *fin);
Przedmiot * wczytaj_przedmioty(FILE *fin);
int ile_studentow(SBaza *baza);
int ile_przedmiotow(SBaza *baza);                    
int ile_ocen(SBaza *baza);
SBaza * dodaj_studentow (SBaza * baza, char *imie, char *nazwisko, char *nr_albumu, char *email);
void dodaj_przedmiot (SBaza * baza, char *kod_przed, char *nazwa_przed, char *sem);
SBaza * dodaj_studenta_do_przedmiotu(SBaza * baza, char *kod_przed, char *nr_albumu);
void listuj_studentow(SBaza *baza);
void zwolnij_liste_studentow(Student *s);
void zwolnij_liste_przedmiotow(Przedmiot *s);
void zwolnij_liste_ocen(Ocena *s);
void zwolnij(SBaza *baza);

#endif
