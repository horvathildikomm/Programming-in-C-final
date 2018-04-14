#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdbool.h>

szavak *szavak_beolvas(char *file_nev);
szavak *torol_mas_betuszamuak(int betuszam,szavak *eleje);
szavak *torol_ha_van_benne(char *betu,szavak *eleje);
szavak *torol_nem_min(int minimum, char *betu ,szavak *eleje);
szavak *torol_ha_rossz_helyen(szavak *eleje);
void felszabadit_lista(szavak *eleje);
int tartalmazza(szavak *szo, char* betu); //visszatérési érték: hányszor

void feltolt_adattal(szavak *elem ,char *szo);

#endif // LISTA_H_INCLUDED
