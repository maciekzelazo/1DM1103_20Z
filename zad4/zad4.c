#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _student {
    char imie[25];
    char nazwisko[50];
    char nr_albumu[10];
    char kod_przed[10];
    char nazwa_przed[255];
    float ocena;
    int ects;
} student, *pstudent;

int wczytaj(student dane[100], char *fnazwa) {
    FILE * fin = fopen(fnazwa, "r");
    int cnt, i;
    char bufor[1024];
    char *w;

    fgets(bufor, 1023, fin);
    sscanf(bufor, "%d", &cnt);
 
    for (i=0; i<cnt; i++) {
        fgets(bufor, 1023, fin);
        // printf("%s", bufor);
        w = strtok(bufor, "|");
        strncpy(dane[i].imie, w, 24);

        w = strtok(NULL, "|");
        strncpy(dane[i].nazwisko, w, 49);
        
        w = strtok(NULL, "|");
        strncpy(dane[i].nr_albumu, w, 9);

        w = strtok(NULL, "|");
        strncpy(dane[i].kod_przed, w, 9);

        w = strtok(NULL, "|");
        strncpy(dane[i].nazwa_przed, w, 254);

        w = strtok(NULL, "|");
        dane[i].ocena = atof(w);

        w = strtok(NULL, "|");
        dane[i].ects = atoi(w);
    }

    fclose(fin);
    return cnt;
}

void wypisz(student dane[100], int n) {
    int i;
    for (i=0; i<n;i++) {
        printf("{ Student: %s - %s %s, z przedmiotu: [%s] %s za ECTS: %d otrzymaĹ‚ %.1f\n",
            dane[i].nr_albumu, dane[i].imie, dane[i].nazwisko,
            dane[i].kod_przed, dane[i].nazwa_przed,
            dane[i].ects, dane[i].ocena
        );
    }
}

int znajdz(char *szukany_kod, char kod_przedm[100][10], int n) {
    int i;
    for (i=0; i<n; i++) {
        if (strcmp(szukany_kod, kod_przedm[i]) == 0)
            return i;
    }
    return -1;
}

int znajdz_przedmioty(char kod_przedm[100][10], student dane[100], int n) {
    int ile_znalazlem = 0;
    int i;

    for (i=0; i <n; i++) {
        if (znajdz(dane[i].kod_przed, kod_przedm, ile_znalazlem) == -1) {
            strncpy(kod_przedm[ile_znalazlem], dane[i].kod_przed, 9);
            ile_znalazlem++;
        }
    }
    return ile_znalazlem;
}


void najlepszy_przedmiot(student dane[100], int ile_rekordow)
{
    char kod_przedm[100][10];
    char nazwa_przed[100][255];
    int ile_przedmiotow;
    float srednie[100];
    int ile_wystapien[100];
    int i;
    int pozycja;
    int najlepsza_pozycja;
    float najlepsza = 0.0f;

    for(int p=0; p<100; p++)
        srednie[p]=0;

    for(int p=0; p<100; p++)
        ile_wystapien[p]=0;

    ile_przedmiotow = znajdz_przedmioty(kod_przedm, dane, ile_rekordow);

    for (i=0; i<ile_rekordow; i++)
    {
        pozycja = znajdz(dane[i].kod_przed, kod_przedm, ile_przedmiotow);
        strcpy(nazwa_przed[pozycja],dane[i].nazwa_przed);
        ile_wystapien[pozycja]++;
        srednie[pozycja] += dane[i].ocena;
    }    

    for (i=0; i<ile_przedmiotow; i++) 
        srednie[i] = srednie[i]/ile_wystapien[i];

    for (i=0; i < ile_przedmiotow; i++)
    {
        if (najlepsza<srednie[i])
        {
            najlepsza = srednie[i];
            najlepsza_pozycja = i;
        }
    }
    printf("Najlepsza średnia: %s - %s: %.2f \n", kod_przedm[najlepsza_pozycja], nazwa_przed[najlepsza_pozycja], srednie[najlepsza_pozycja]);
}

void najgorszy_przedmiot(student dane[100], int ile_rekordow)
{
    char kod_przedm[100][10];
    char nazwa_przed[100][255];
    int ile_przedmiotow;
    float srednie[100];
    int ile_wystapien[100];
    int i;
    int pozycja;
    int najlepsza_pozycja;
    float najlepsza = 6.0f;

    for(int p=0; p<100; p++)
        srednie[p]=0;

    for(int p=0; p<100; p++)
        ile_wystapien[p]=0;

    ile_przedmiotow = znajdz_przedmioty(kod_przedm, dane, ile_rekordow);

    for (i=0; i < ile_rekordow; i++)
        {
        pozycja = znajdz( dane[i].kod_przed, kod_przedm, ile_przedmiotow );
        strcpy(nazwa_przed[pozycja], dane[i].nazwa_przed);
        ile_wystapien[pozycja]++;
        srednie[pozycja] += dane[i].ocena;
        }   

    for (i=0; i < ile_przedmiotow; i++) 
        srednie[i] = srednie[i]/ile_wystapien[i];

    for (i=0; i < ile_przedmiotow; i++)
        {
            if (najlepsza>srednie[i])
                {
                najlepsza = srednie[i];
                najlepsza_pozycja = i;
                }
        }
    printf("Najgorsza średnia: %s - %s: %.2f \n", kod_przedm[najlepsza_pozycja], nazwa_przed[najlepsza_pozycja], srednie[najlepsza_pozycja]);
}

int main(int argc, char ** argv) {
    student dane[100];
    int ile;
    ile = wczytaj(dane, argv[1]);
    //wypisz(dane, ile);
    najlepszy_przedmiot(dane, ile);
    najgorszy_przedmiot(dane, ile);
    return 0;
}