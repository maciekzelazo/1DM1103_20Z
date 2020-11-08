#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct macierz
{
    int r;
    int c;
    float tab[100][100];
};

void wczytaj1(FILE * fin1, struct macierz *m) 
{
    int i,j;

    fscanf(fin1, "%d", &m->r);
    fscanf(fin1, "%d", &m->c);

    for (i=0; i < m->r; i++) 
        for (j=0; j < m->c; j++) 
            fscanf(fin1, "%f", &m->tab[i][j]);
}

void wypisz1(struct macierz m) {
    int i, j;
    printf("[ ");
    for (i = 0; i < m.r; i++) {
        for (j=0; j < m.c; j++) {
            printf("%5.1f ", m.tab[i][j]);
        }
        if (i < (m.r-1))
            printf("\n  ");
    }
    printf("]\n");
}

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

void zapisz(char nazwa[], struct macierz m)
{
    FILE * fout = fopen(nazwa, "w");
    int i,j;

    fprintf(fout, "%d\n%d\n", m.r, m.c);
    for (i = 0; i < m.r; i++)
    {
        for (j=0; j < m.c; j++)
        {
            fprintf(fout, "%.1f\n", m.tab[i][j]);
        }
    }

    fclose(fout);
}



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
    }
    else
    {
        printf("Nieprawidłowe polecenie, wpisz sum, subtract, norm, prod lub multiply.\n");
        exit(-4);
    }
}