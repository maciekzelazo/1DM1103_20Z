#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matma.h"
#include "funkcje.h"

int main(int argc, char *argv[])
{
    if(strcmp(argv[1], "sum") == 0)
    {
        struct macierz m;
        struct macierz n;
        struct macierz wynik;
        FILE *fin1;
        FILE *fin2;
        fin1 = fopen(argv[2], "r");
        fin2 = fopen(argv[3], "r");
        wczytaj1(fin1, &m);
        wczytaj1(fin2, &n);
        wynik = sum(m,n);
        fclose(fin1);
        fclose(fin2);
        if(argc == 5)
        {
            zapisz(argv[4], wynik);
        }
        else
        {
            wypisz1(wynik);
        }
        zwolnij(&m);
        zwolnij(&n);
        zwolnij(&wynik);
    }
    else if(strcmp(argv[1], "subtract") == 0)
    {
        struct macierz m;
        struct macierz n;
        struct macierz wynik;
        FILE *fin1;
        FILE *fin2;
        fin1 = fopen(argv[2], "r");
        fin2 = fopen(argv[3], "r");
        wczytaj1(fin1, &m);
        wczytaj1(fin2, &n);
        wynik = subtract(m,n);
        fclose(fin1);
        fclose(fin2);
        if(argc == 5)
        {
            zapisz(argv[4], wynik);
        }
        else
        {
            wypisz1(wynik);
        }
        zwolnij(&m);
        zwolnij(&n);
        zwolnij(&wynik);
    }
    else if(strcmp(argv[1], "norm") == 0)
    {
        struct macierz m;
        float wynik;
        FILE *fin;
        fin = fopen(argv[2], "r");
        wczytaj1(fin, &m);
        wynik = norm(m);
        fclose(fin);
        if(argc == 4)
        {
            FILE *fout = fopen(argv[3], "w+");
            fprintf(fout, "%f", wynik);
            fclose(fout);
        }
        else
        {
            printf("%f\n", wynik);
        }
        zwolnij(&m);
    }
    else if(strcmp(argv[1], "prod") == 0)
    {
        struct macierz m;
        struct macierz n;
        struct macierz wynik;
        FILE *fin1;
        FILE *fin2;
        fin1 = fopen(argv[2], "r");
        fin2 = fopen(argv[3], "r");
        wczytaj1(fin1, &m);
        wczytaj1(fin2, &n);
        wynik = prod(m,n);
        fclose(fin1);
        fclose(fin2);
        if(argc == 5)
        {
            zapisz(argv[4], wynik);
        }
        else
        {
            wypisz1(wynik);
        }
        zwolnij(&m);
        zwolnij(&n);
        zwolnij(&wynik);
    }
    else if(strcmp(argv[1], "multiply") == 0)
    {
        struct macierz m;
        struct macierz wynik;
        FILE *fin;
        float skalar;
        fin = fopen(argv[2], "r");
        wczytaj1(fin, &m);
        skalar = atof(argv[3]);
        wynik = multiply(m, skalar);
        fclose(fin);
        if(argc == 5)
        {
            zapisz(argv[4], wynik);
        }
        else
        {
            wypisz1(wynik);
        }
        zwolnij(&m);
        zwolnij(&wynik);
    }
    else
    {
        printf("Nieprawidłowe polecenie, wpisz sum, subtract, norm, prod lub multiply.\n");
        exit(-4);
    }
}