#ifndef RAJZOL_H_INCLUDED
#define RAJZOL_H_INCLUDED

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <string.h>
#include "main.h"

extern SDL_Color utasitas_betuszin;
extern SDL_Color ABCbetuszin;
extern SDL_Color piros;
extern int ablakmag;
extern int ablakszel;

void hatter_kirajzol(void);
void vonalak_rajzol(int db);
void ablak_megnyit(void);
void betutipus_betolt(int betumeret);
void ABC_kirir(void);
void szoveg_kiir(char *szoveg, int hely_x, int hely_y,int betumeret, SDL_Color betuszin);
void akasztofa_darab_rajzol(int darab);
void ABCbol_kihuz(char *betu);
void kiir_betuk(int betuszam, SDL_Color szin);
void kiir_megfejtes(int betuszam, szavak *szo);


#endif // RAJZOL_H_INCLUDED
