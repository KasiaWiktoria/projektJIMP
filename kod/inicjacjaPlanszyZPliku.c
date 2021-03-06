#include "inicjacjaPlanszyZPliku.h"

plansza_t wczytajZPliku(const char* plik){

    FILE* in = fopen(plik, "r");

    plansza_t a;

    policz(plik, &a);
    a.tablica = malloc(sizeof(int) * a.wiersze * a.kolumny);

    if( sprawdz(plik, &a) == -1 )
        return inicjacjaLosowa(10, 10);

	else if (sprawdz(plik, &a) == 0) {

		wypelnij(plik, &a);
	}
	fclose(in);
	return a;
}

void wypelnij(const char* plik, plansza_t* x ){

	FILE* in = fopen(plik, "r");

    int n = 0;
	char znak;
    while ((znak = getc(in)) != EOF){
		if (znak != '\n' && znak != 13) {
			x->tablica[n++] = znak - '0';
		}
    }
	fclose(in);
}

void policz(const char* plik, plansza_t* x){

	FILE* in = fopen(plik, "r");
    int k=0, w;
    char znak;
    while ( ((znak = getc(in)) != EOF) && (znak != '\n') && (znak != 13))
        k++;
    
    x->kolumny=k;

    w=1; //bo przeczytano juz 1 linie
    while ( (znak=getc(in)) != EOF )
        if(znak == '\n')
            w++;
    
    x->wiersze=w;

	fclose(in);
}

int sprawdz(const char* plik, plansza_t* x)
{	
	FILE* in = fopen(plik, "r");
    int k = x->kolumny, w = 0, k2;
	char d;
	while ( (d = getc(in)) != EOF)
    {
		if(w ==0) k2 = 1;
		else k2 = 0;
        while (((d = getc(in)) != '\n') && (d != EOF) && (d != 13))
            k2++;
        
		if (k2 != k) {
			//printf("Liczba wierszy: %d \n", w);
			printf("Liczba znakow w wierszu %d jest nieprawidlowa, wiersz powinien zawierac %d znakow, a znaleziono %d \n", w, k, k2);
			return -1;
		}
        w++;
    }
	fclose(in);
	
    return 0;
}
