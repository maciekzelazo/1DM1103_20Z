#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dziekanat.h"
#include "studenci.h"

typedef struct _student {
    char imie[25];
    char nazwisko[50];
    char nr_albumu[10];
    char kod_przed[10];
    char nazwa_przed[255];
    float ocena;
    int ects;
} student, *pstudent;

void najlepszy_student(student dane[100], int ile_rekordow) {
    char nr_albumow[100][10];
    int ile_studentow;
    float sumy_wazonych_ocen[100];
    int sumy_ects[100];
    float srednie[100];
    int i;
    int pozycja;
    int najlepsza_pozycja;
    float najlepsza = 0.0f;

    ile_studentow = znajdz_studentow(nr_albumow, dane, ile_rekordow);

    for (i=0; i < ile_rekordow; i++) {
        pozycja = znajdz( dane[i].nr_albumu, nr_albumow, ile_studentow );
        sumy_wazonych_ocen[pozycja] += dane[i].ocena * dane[i].ects;
        sumy_ects[pozycja] += dane[i].ects;
    }    

    for (i=0;i<ile_studentow; i++) 
        printf("Student [%d]: %s - %f:%d - %f \n", i+1, nr_albumow[i], 
        sumy_wazonych_ocen[i], sumy_ects[i], sumy_wazonych_ocen[i] / sumy_ects[i]);

    for (i=0; i < ile_studentow; i++) {
        if (najlepsza < sumy_wazonych_ocen[i] / sumy_ects[i]) {
            najlepsza = sumy_wazonych_ocen[i] / sumy_ects[i];
            najlepsza_pozycja = i;
        }
    }

    printf("Najlepszy student: \n");
    printf("Student [%d]: %s - %f \n", 
        najlepsza_pozycja+1, nr_albumow[najlepsza_pozycja],
        sumy_wazonych_ocen[najlepsza_pozycja] / sumy_ects[najlepsza_pozycja]
    );

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
