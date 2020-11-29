#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "funkcje.h"

struct macierz sum(struct macierz m, struct macierz n)
{
   if((m.r!=n.r)||(m.c!=n.c))
   {
       printf("Nie można dodawać macierzy o różnych rozmiarach.\n");
       exit(-1);
   }
   else
   {
       struct macierz wynik;
       wynik.r = m.r;
       wynik.c = m.c;
       for(int i=0;i<m.r;i++)
            for(int j=0;j<m.c;j++)
             wynik.tab[i][j]=m.tab[i][j]+n.tab[i][j];
        return wynik;
   }
   
}

struct macierz subtract(struct macierz m, struct macierz n)
{
   if((m.r!=n.r)||(m.c!=n.c))
   {
       printf("Nie można odejmować macierzy o różnych rozmiarach.\n");
       exit(-2);
   }
   else
   {
       struct macierz wynik;
       wynik.r = m.r;
       wynik.c = m.c;
       for(int i=0;i<m.r;i++)
            for(int j=0;j<m.c;j++)
             wynik.tab[i][j]=m.tab[i][j]-n.tab[i][j];
        return wynik;
   }
   
}

float norm(struct macierz m)
{
    float wynik = 0;

    for (int i = 0; i < m.r; i++) {
        for (int j = 0; j < m.c; j++) {
            wynik += m.tab[i][j] * m.tab[i][j];
        }
    }
    return sqrt(wynik);
}

struct macierz prod(struct macierz m, struct macierz n)
{
    if(m.c!=n.r)
    {
        printf("Nie można pomnożyć podanych macierzy.\n");
        exit(-3);
    }
    else
    {
        struct macierz wynik;
        wynik.r=m.r;
        wynik.c=n.c;
        for(int i=0;i<n.r;i++)
            for(int j=0;j<m.c;j++)
                for(int p=0;p<n.r;p++)
                {
                    wynik.tab[i][j] += m.tab[i][p]*n.tab[p][j];
                }
        return wynik; 
    }
    
}

struct macierz multiply(struct macierz m, float skalar)
{
    struct macierz wynik;
    wynik.r=m.r;
    wynik.c=m.c;
    for(int i=0;i<m.r;i++)
        for(int j=0;j<m.c;j++)
        {
            wynik.tab[i][j] = m.tab[i][j]*skalar;
        }
       return wynik; 
}