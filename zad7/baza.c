#include "baza.h"

Student * wczytaj_studentow(FILE *fin) 
{
    char bufor[255];
    int n, i;
    char *s;
    Student *last_student = NULL;
    Student *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);

    for (i = 0; i < n; i++) 
    
    {
        Student *stud = (Student*) malloc(sizeof(Student));
        stud->nast = NULL;

        if (last_student == NULL)
            glowa = stud;
        else
            last_student->nast = stud;
        last_student = stud;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        stud->imie = (char*) malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(stud->imie, s);

        s = strtok(NULL, ";");
        stud->nazwisko = (char*) malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(stud->nazwisko, s);

        s = strtok(NULL, ";");
        stud->nr_albumu = (char*) malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(stud->nr_albumu, s);

        s = strtok(NULL, "\n");
        stud->email = (char*) malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(stud->email, s);
    }

    return glowa;
}

SBaza * wczytaj_baze(char *nazwa_pliku) 
{
    FILE *fin = fopen(nazwa_pliku, "r");
    if (fin == NULL) 
    {
        printf("Nie mozna otworzyc pliku: %s.\n", nazwa_pliku);
        exit(-1);
    }

    SBaza *baza = (SBaza*) malloc( sizeof(SBaza) );
    baza->lista_studentow = wczytaj_studentow(fin);
    baza->lista_przedmiotow = wczytaj_przedmioty(fin);
    baza ->lista_ocen = wczytaj_oceny(fin);
    fclose(fin);
    return baza;
}

Przedmiot * wczytaj_przedmioty(FILE *fin) 
{
    char bufor[255];
    int n, i;
    char *s;
    Przedmiot *last_przedmiot = NULL;
    Przedmiot *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Przedmiot *przed = (Przedmiot*) malloc(sizeof(Przedmiot));
        przed->nast = NULL;

        if (last_przedmiot == NULL)
            glowa = przed;
        else
            last_przedmiot->nast = przed;
        last_przedmiot = przed;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        przed->kod_przed = (char*) malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(przed->kod_przed, s);

        s = strtok(NULL, ";");
        przed->nazwa_przed = (char*) malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(przed->nazwa_przed, s);

        s = strtok(NULL, "\n");
        przed->sem = (char*) malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(przed->sem, s);

    }

    return glowa;
}

Ocena * wczytaj_oceny(FILE *fin) {

    char bufor[255];
    int n, i;
    char *s;
    Ocena *last_ocena = NULL;
    Ocena *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Ocena *o = (Ocena*) malloc(sizeof(Ocena));
        o->nast = NULL;

        if (last_ocena == NULL)
            glowa = o;
        else
            last_ocena->nast = o;
        last_ocena = o;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        o->kod_przed = (char*) malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(o->kod_przed, s);

        s = strtok(NULL, ";");
        o->nr_albumu = (char*) malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(o->nr_albumu, s);
        
        s = strtok(NULL, ";");
        o->ocena = (char*) malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(o->ocena, s);

        s = strtok(NULL, ";");
        o->komentarz = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(o->komentarz, s);
    }

    return glowa;
}

SBaza * zapisz_baze(char *nazwa_pliku, SBaza * baza) 
{
    FILE *fin = fopen(nazwa_pliku, "w+");
  	fprintf(fin, "%d\n", ile_studentow(baza));
      Student * stud = baza->lista_studentow;
      Przedmiot *przed = baza->lista_przedmiotow;
      Ocena * oc = baza->lista_ocen;
		
  	int i, j, k;
    for(i=0; i<ile_studentow(baza); i++)
        {
         fprintf(fin, "%s;%s;%s;%s\n", stud->imie, stud->nazwisko, stud->nr_albumu, stud->email);
         stud = stud->nast;
        }
    fprintf(fin, "%d\n", ile_przedmiotow(baza));

    
  	for(j=0; j<ile_przedmiotow(baza); j++)
        {
         fprintf(fin, "%s;%s;%s\n", przed->kod_przed, przed->nazwa_przed, przed->sem);
         przed = przed ->nast;
        }

    fprintf(fin, "%d\n", ile_ocen(baza));
  	
  	for(k=0; k<ile_ocen(baza); k++)
        {
         fprintf(fin, "%s;%s;%s;%s\n", oc->kod_przed, oc->nr_albumu, oc->ocena, oc->komentarz);
         oc = oc->nast;
        }
  	fclose(fin);
  
  	return NULL;
}

SBaza * dodaj_studentow(SBaza * baza, char *imie, char *nazwisko, char *nr_albumu, char *email)
{
    Student *nowy = (Student*) malloc(sizeof(Student));
  	Student *obecny = NULL;
  	nowy->nast = NULL;
  	nowy->imie = (char*) malloc(sizeof(char) * (strlen(imie) + 1));
    strcpy(nowy->imie, imie);
    nowy->nazwisko = (char*) malloc(sizeof(char) * (strlen(nazwisko) + 1));
    strcpy(nowy->nazwisko, nazwisko);
    nowy->nr_albumu = (char*) malloc(sizeof(char) * (strlen(nr_albumu) + 1));
    strcpy(nowy->nr_albumu, nr_albumu);
    nowy->email = (char*) malloc(sizeof(char) * (strlen(email) + 1));
    strcpy(nowy->email, email);
    obecny=baza->lista_studentow;
    
    if(ile_studentow(baza) == 0)
    {
      baza->lista_studentow = nowy;
    }
    else
    {
      for(int i=1; i<ile_studentow(baza); i++)
      {
        obecny = obecny->nast;
      }
      obecny->nast = nowy;
    }   
    return NULL;
}

void dodaj_przedmiot(SBaza *baza, char *kod_przed, char *nazwa_przed, char *sem)
{
 	Przedmiot *nowy = (Przedmiot*) malloc(sizeof(Przedmiot));
  	Przedmiot *obecny = NULL;
  	nowy->nast = NULL;
  	nowy->kod_przed = (char*) malloc(sizeof(char) * (strlen(kod_przed) + 1));
    strcpy(nowy->kod_przed, kod_przed);
    nowy->nazwa_przed = (char*) malloc(sizeof(char) * (strlen(nazwa_przed) + 1));
    strcpy(nowy->nazwa_przed, nazwa_przed);
    nowy->sem = (char*) malloc(sizeof(char) * (strlen(sem) + 1));
    strcpy(nowy->sem, sem);
    obecny = baza->lista_przedmiotow;
    
    if(ile_przedmiotow(baza) == 0)
    {
      baza->lista_przedmiotow = nowy;
    }
    else
    {
      for(int i=1; i<ile_przedmiotow(baza); i++)
      {
        obecny = obecny->nast;
      }
      obecny->nast = nowy;
    }
    
}

SBaza * dodaj_studenta_do_przedmiotu(SBaza * baza, char *kod_przed, char *nr_albumu)
{
	Ocena *nowy = (Ocena*) malloc(sizeof(Ocena));
  	Ocena *obecny = NULL;
  	nowy->nast = NULL;
  	nowy->kod_przed = (char*) malloc(sizeof(char) * (strlen(kod_przed) + 1));
    strcpy(nowy->kod_przed, kod_przed);
    nowy->nr_albumu = (char*) malloc(sizeof(char) * (strlen(nr_albumu) + 1));
    strcpy(nowy->nr_albumu, nr_albumu);
    obecny = baza->lista_ocen;
    
    if(ile_ocen(baza) == 0)
    {
      baza->lista_ocen = nowy;
    }
    else
    {
      for(int i=1; i<ile_ocen(baza); i++)
      {
        obecny = obecny->nast;
      }
      obecny->nast = nowy;
    }
    return NULL;
}

int ile_studentow(SBaza *baza) 
{
    
    int n = 0;
    Student * stud = baza->lista_studentow;
    while (stud != NULL) 
    {
        n++;
        stud = stud->nast;
    }
    return n;
}

int ile_przedmiotow(SBaza *baza)
{
	int n = 0;
    Przedmiot * przed = baza->lista_przedmiotow;
    while (przed != NULL) 
    {
        n++;
        przed = przed->nast;
    }
    return n;
}

int ile_ocen(SBaza *baza)
{
	int n = 0;
    Ocena * ocen = baza->lista_ocen;
    while (ocen != NULL) 
    {
        n++;
        ocen = ocen->nast;
    }
    return n;
}

void listuj_studentow(SBaza *baza) 
{
    Student * stud = baza->lista_studentow;
    while (stud != NULL) 
    {
        printf("%s %s %s %s\n", stud->imie, stud->nazwisko, stud->nr_albumu, stud->email);
        stud = stud->nast;
    }
}

void zwolnij_student(Student *s) 
{
    free(s->imie);
    free(s->nazwisko);
    free(s->nr_albumu);
    free(s->email);
    free(s);
}

void zwolnij_przedmiot(Przedmiot *s) 
{
    free(s->kod_przed);
    free(s->nazwa_przed);
    free(s->sem);
    free(s);
}

void zwolnij_ocena(Ocena *s) 
{
    free(s->kod_przed);
    free(s->nr_albumu);
    free(s->ocena);
    free(s->komentarz);
    free(s);
}

void zwolnij_liste_studentow(Student *s) 
{
    Student *n;
    while (s != NULL) 
    {
        n = s->nast;
        zwolnij_student(s);
        s = n;
    }
}

void zwolnij_liste_przedmiotow(Przedmiot *s) 
{
    Przedmiot *n;
    while (s != NULL) 
    {
        n = s->nast;
        zwolnij_przedmiot(s);
        s = n;
    }
}

void zwolnij_liste_ocen(Ocena *s) 
{
    Ocena *n;
    while (s != NULL) 
    {
        n = s->nast;
        zwolnij_ocena(s);
        s = n;
    }
}

void zwolnij(SBaza *baza) 
{
    zwolnij_liste_studentow(baza->lista_studentow);
    zwolnij_liste_przedmiotow(baza->lista_przedmiotow);
    zwolnij_liste_ocen(baza->lista_ocen);
    free(baza);
} 