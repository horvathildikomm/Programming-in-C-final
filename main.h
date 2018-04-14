#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <SDL.h>
#include <stdbool.h>



typedef struct szavak{
    char szo[30][3+1];
    int betuszam;
    struct szavak *kovetkezo;
}szavak;

extern char ABC[35][4];
extern char megfejtes[30+1][4];

bool poziciobol_betu(char* eredmeny, int x, int y);
int random_betuszam(szavak *eleje);
bool van_rossz_szo(szavak *eleje, char *betu);
int min_db_betu(szavak *eleje, char *betu);
void megfejtesbe_beir(char *betu, szavak *eleje);
void inicializal_megfejtes(int betuszam);



#endif // MAIN_H_INCLUDED
