#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    /* to jest rzeczywista liczba bajtów przekazanych przez curl */
    size_t realsize = size * nmemb;

    /* jawnie konwertujemy (void*) na naszą strukturę, bo wiemy, że będziemy ją tutaj otrzymywać */
    Memory *mem = (Memory *) userp;

    char *ptr = NULL;

    /* Sprawdzamy czy pierwszy raz wywołujemy funkcję i trzeba zaalokować pamięć po raz pierwszy,
    czy trzeba zrobić reallokację (która kopiuje automatycznie starą zawartość w nowe miejsce) */
    if (mem->response != NULL)
        ptr = realloc(mem->response, mem->size + realsize + 1);
    else
        ptr = malloc(mem->size + realsize + 1);

    if (ptr == NULL)
        return 0; /* brak pamięci! */

    /* teraz zapamiętujemy nowy wskaźnik i doklejamy na końcu dane przekazane przez curl w 
       obszarze pamięci wskazywanym przez data */
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0; // to na końcu dodajemy bo to w końcu string, i zawsze powinien się skończyć!

    return realsize;
}

int make_request(char *url){
    CURL *curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;
    int status;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

        /* to jest funkcja 'callback', która będzie wywołana przez curl gdy odczyta on kawałek danych
       ta funkcja musi mieć wywołanie zgodne z wymaganiami, które możesz sprawdzić tutaj:
       https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        /* to jest adress struktury, który będzie przekazywany do naszej funkcji 'callback',
       do tej struktury nasz funkcja 'callback' będzie dopisywać wynik */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        /* Wykonaj zapytanie 'synchronicznie', to znaczy następna linijka kodu nie wykona się
       dopóki nie nadejdzie odpowiedź z serwera. */
        res = curl_easy_perform(curl);

        /* Sprawdzamy czy wystapił jakis błąd? */
        if (res != CURLE_OK){
            fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
            status=0;
        }
        else
        {
            printf("%s", chunk.response);
            status=1;
        }

        /* zawsze po sobie sprzątaj */
        free(chunk.response);
        curl_easy_cleanup(curl);

    }
    return status;
}

int info(char *token) {
    char *url; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/";
    int status;
    url = (char*) malloc((sizeof(char) * strlen(url1)) + (sizeof(char) *strlen((token) + 1)));
    strcpy(url,url1);
    strncat(url,token,9);
    printf("%s\n",url);
    printf("Informacje o świecie:\n");
    status=make_request(url);
    return status;
}

int move(char *token) {
    char *url; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/";
    int status;
    url = (char*) malloc((sizeof(char) * strlen(url1)) + (sizeof(char) *strlen((token) + 1)));
    strcpy(url,url1);
    strncat(url,token,9);
    printf("%s\n",url);
    printf("Ruch do przodu.\n");
    status=make_request(url);
    return status;
}

int rotate(char *token, char *direction){
    char *url; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
    int status;
    url = (char*) malloc((sizeof(char) * strlen(url1)) + (sizeof(char) * strlen((token) + 1)) + (sizeof(char) * strlen((direction) + 1)));
    strcpy(url,url1);
    strncat(url,token,9);
    strncat(url, "/", 1);
    strncat(url,direction,5);
    printf("%s\n",url);
    if(strcmp(direction, "left")==0)
        printf("Obrót w lewo.\n");
    if(strcmp(direction, "right")==0)
        printf("Obrót w prawo.\n");
    status=make_request(url);
    return status;
}

int explore(char *token){
    char *url; 
    char *url1="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/";
    int status;
    url = (char*) malloc((sizeof(char) * strlen(url1)) + (sizeof(char) *strlen((token) + 1)));
    strcpy(url,url1);
    strncat(url,token,9);
    printf("%s\n",url);
    printf("Eksploracja.\n");
    status=make_request(url);
    return status;
}

int main(int argc, char **argv)
{
    char *url;
    char *token;
    int status;
    token=argv[1];

    if(argc<3)
    {
        status=info(token);
        printf("\n");
    }
    else
    {

        int i;
        for(i=2;i<argc;i++){
            if(strcmp(argv[i],"m")==0){
                status=move(token);
                printf("\n");
            }
            else if(strcmp(argv[i],"rr")==0){
                status=rotate(token,"right");
                printf("\n");
            }
            else if(strcmp(argv[i],"rl")==0){
                status=rotate(token,"left");
                printf("\n");
            }
            else if(strcmp(argv[i],"e")==0){
                status=explore(token);
                printf("\n");
            }
            else
            {
                printf("Wpisz m, rr, rl, lub e\n");
                exit(-1);
            } 
        }
    }
    return 0;
}