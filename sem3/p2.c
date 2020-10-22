#include<stdio.h>
#include<stdlib.h>
int main(argc, char *argv[]) {
    char n[100];
    int i;
    char n2[] = "hello";
    strcpy(n, "Ala");
    printf("%s", n);

    for(i=0; i<3;i++) {
        printf("[%d] %c, %d\n",i, n[i], n[i])
    }
    return 0;
}