#include <stdio.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "rajzol.h"
#include "main.h"
#include "lista.h"

char ABC[35][4]={"a","á","b","c","d","e","é","f","g","h","i","í","j","k","l","m","n","o","ó","ö","ő","p","q","r","s","t","u","ú","ü","ű","v","w","x","y","z"};
char megfejtes[30+1][4];

int main(int argc, char *argv[]) {

    srand(time(NULL));

    SDL_Event event;

    szavak *szo_lista_eleje=szavak_beolvas("szavak_Utf8.txt");
    if(szo_lista_eleje==NULL){
        printf("Nem sikerult szavakat beolvasni, lehetseges, hogy ures a szavakat tartalmazo fajl.");
        return 1;
    }
    ablak_megnyit();
    hatter_kirajzol();
    ABC_kirir();
    szoveg_kiir("Tippelj egy betűt!",40,40,40,utasitas_betuszin);

    int betuszam=random_betuszam(szo_lista_eleje);
    vonalak_rajzol(betuszam);
    inicializal_megfejtes(betuszam);


    szo_lista_eleje=torol_mas_betuszamuak(betuszam,szo_lista_eleje);

    int akasztofa_szamlalo=0;
    int betuszamlalo=0;
    bool kattinthatsz=true;

    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {

        char tippelt_betu[4];
        //Ha egy betűre kattintott:
        if(kattinthatsz&&event.type==SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && poziciobol_betu(tippelt_betu,event.button.x, event.button.y)){
            if(van_rossz_szo(szo_lista_eleje,tippelt_betu)){
                szo_lista_eleje=torol_ha_van_benne(tippelt_betu,szo_lista_eleje);
                if(strcmp(tippelt_betu," ")!=0) //ha benne van még az ABCben
                    akasztofa_darab_rajzol(++akasztofa_szamlalo);
            }
            else{
                int min_db=min_db_betu(szo_lista_eleje,tippelt_betu);
                szo_lista_eleje=torol_nem_min(min_db,tippelt_betu, szo_lista_eleje);
                megfejtesbe_beir(tippelt_betu,szo_lista_eleje);
                kiir_betuk(betuszam,ABCbetuszin);
                szo_lista_eleje=torol_ha_rossz_helyen(szo_lista_eleje);
                betuszamlalo+=min_db;
            }
            ABCbol_kihuz(tippelt_betu);


            if(akasztofa_szamlalo>13){  //ha vesztettél
                szoveg_kiir("VESZTETTÉL!!! :( ", 400, 300,70,piros);
                kattinthatsz=false;
                kiir_megfejtes(betuszam, szo_lista_eleje);
            }
            if(betuszamlalo==betuszam){
                szoveg_kiir("NYERTÉL!!! :) ", 400, 300,70,piros);
                kattinthatsz=false;
            }
        }
    }

    SDL_Quit();
    felszabadit_lista(szo_lista_eleje);

    return 0;


}



bool poziciobol_betu(char* eredmeny, int x, int y){
    int i;
    for(i=0;i<35;++i){
        if(x>i%7*60+50 && x<i%7*60+50+30 && y>i/7*40+ablakmag-220 && y<i/7*40+ablakmag-220+30){
            strcpy(eredmeny,ABC[i]);
            return true;
        }
    }
    return false;
}


int random_betuszam(szavak *eleje){
    int max_betuszam=eleje->betuszam;
    int min_betuszam=eleje->betuszam;
    szavak *mozgo;
    for(mozgo=eleje;mozgo!=NULL;mozgo=mozgo->kovetkezo){
        if(mozgo->betuszam>max_betuszam)
            max_betuszam=mozgo->betuszam;
        if(mozgo->betuszam<min_betuszam)
            min_betuszam=mozgo->betuszam;
    }
    bool van_szo=false; //meg kell nézni, hogy van-e pontosan olyan hosszú szó, mint a generált random szám
    int r;
    while(!van_szo){
        r=rand()%(max_betuszam-min_betuszam+1)+min_betuszam;
        for(mozgo=eleje;mozgo!=NULL;mozgo=mozgo->kovetkezo){
            if(mozgo->betuszam==r)
                van_szo=true;
        }
    }
    return r;

}


bool van_rossz_szo(szavak *eleje, char *betu){
    szavak *mozgo;
    for(mozgo=eleje;mozgo!=NULL;mozgo=mozgo->kovetkezo){
        if(tartalmazza(mozgo,betu)==0)
            return true;
    }
    return false;
}


int min_db_betu(szavak *eleje, char *betu){
    int min=tartalmazza(eleje, betu);
    szavak *mozgo;
    for(mozgo=eleje;mozgo!=NULL;mozgo=mozgo->kovetkezo){
        if(tartalmazza(mozgo, betu)<min)
            min=tartalmazza(mozgo, betu);
    }
    return min;
}

void megfejtesbe_beir(char *betu, szavak *eleje){
    int i;
    for(i=0;i<eleje->betuszam;++i){
        if(strcmp(eleje->szo[i],betu)==0)
            strcpy(megfejtes[i],betu);
    }
}


void inicializal_megfejtes(int betuszam){
    int i;
    for(i=0;i<betuszam;++i){
        strcpy(megfejtes[i]," ");
    }
    strcpy(megfejtes[betuszam],"0"); //lezáró
}













