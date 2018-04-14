#include "rajzol.h"
#include "main.h"
#include <string.h>

SDL_Color utasitas_betuszin = {25, 150, 140}, ABCbetuszin ={0,0,0}, piros={255, 0, 0};
int ablakszel=1360;
int ablakmag=690;

SDL_Surface *screen;
TTF_Font *font;

void hatter_kirajzol(void){
    int i;
    boxRGBA(screen,0, 0, ablakszel, ablakmag, 230,230,240,255);
    for(i=0;i<ablakszel;i=i+20){
        lineRGBA(screen, i, 0, i, ablakmag, 70, 70, 70, 100);
    }
    for(i=0;i<ablakmag;i=i+20){
        lineRGBA(screen, 0, i, ablakszel, i, 70, 70, 70, 100);
    }
    SDL_Flip(screen);
}


void vonalak_rajzol(int db){
    int i;
    if(db<=16){
        for(i=1; i<=db;++i){
            thickLineRGBA(screen, 500+50*i, 600, 540+50*i, 600, 2, 0,0,0, 255);
        }
    }   //Ha nem fér ki egy sorba
    else{
        for(i=1; i<db/2+1;++i){
            thickLineRGBA(screen, 500+50*i, 550, 540+50*i, 550, 2, 0,0,0, 255);
        }
        thickLineRGBA(screen, 505+50*i, 530, 520+50*i, 530, 2, 0,0,0, 255); //kötőjel
        for(i=1; i<=db-db/2;++i){
            thickLineRGBA(screen, 500+50*i, 600, 540+50*i, 600, 2, 0,0,0, 255);
        }
    }

    SDL_Flip(screen);
}


void ablak_megnyit(void){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen = SDL_SetVideoMode(ablakszel, ablakmag, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("Gonosz akasztófa", "Gonosz akasztófa");
}





void betutipus_betolt(int betumeret){
    TTF_Init();
    font = TTF_OpenFont("LiberationSerif-Bold.ttf", betumeret);
    if (!font) {
        fprintf(stderr, "Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }
}






void ABC_kirir(void){
    betutipus_betolt(32);
    SDL_Surface *felirat;
    int i;

    for(i=0;i<35;++i){
        felirat = TTF_RenderUTF8_Solid(font, ABC[i], ABCbetuszin);
        SDL_Rect hova = { i%7*60+50, i/7*40+ablakmag-220, 0, 0 };
        SDL_BlitSurface(felirat, NULL, screen, &hova);
    }
    SDL_FreeSurface(felirat);
    TTF_CloseFont(font);
    SDL_Flip(screen);
}






void szoveg_kiir(char *szoveg, int hely_x, int hely_y,int betumeret, SDL_Color betuszin){
    betutipus_betolt(betumeret);
    SDL_Surface *felirat;
    felirat = TTF_RenderUTF8_Solid(font, szoveg, betuszin);
    SDL_Rect hova = { hely_x, hely_y, 0, 0 };
    SDL_BlitSurface(felirat, NULL, screen, &hova);
    SDL_FreeSurface(felirat);
    TTF_CloseFont(font);
    SDL_Flip(screen);
}






void akasztofa_darab_rajzol(int darab){
    switch(darab){
        case 1:  thickLineRGBA(screen, 850, 500, 1100, 500, 2, 0,0,0, 255); break;      //alap
        case 2:  thickLineRGBA(screen, 975, 500, 975, 100, 2, 0,0,0, 255); break;       //pozna
        case 3:  thickLineRGBA(screen, 975, 100, 820, 100, 2, 0,0,0, 255); break;       //teteje
        case 4:  thickLineRGBA(screen, 900, 100, 975, 180, 2, 0,0,0, 255); break;
        case 5:  thickLineRGBA(screen, 820, 100, 820, 130, 2, 0,0,0, 255); break;       //kotel
        case 6:  aacircleRGBA(screen, 820, 170, 39, 0, 0, 0, 255);                      //fej
                 aacircleRGBA(screen, 820, 170, 40, 0, 0, 0, 255);
                 aacircleRGBA(screen, 820, 170, 41, 0, 0, 0, 255); break;
        case 7:  thickLineRGBA(screen, 820, 210, 820, 340, 2, 0,0,0, 255); break;       //test
        case 8:  thickLineRGBA(screen, 820, 340, 770, 420, 2, 0,0,0, 255); break;       //jobblab
        case 9:  thickLineRGBA(screen, 820, 340, 870, 420, 2, 0,0,0, 255); break;       //ballab
        case 10: thickLineRGBA(screen, 820, 250, 760, 210, 2, 0,0,0, 255); break;       //jobbkez
        case 11: thickLineRGBA(screen, 820, 250, 880, 210, 2, 0,0,0, 255); break;       //balkez
        case 12: filledCircleRGBA(screen, 805, 160, 3, 0,0,0,255); break;               //jobb szeme
        case 13: filledCircleRGBA(screen, 835, 160, 3, 0,0,0,255); break;               //bal szeme
        case 14: thickLineRGBA(screen, 805, 190, 835, 190, 2, 0,0,0, 255); break;
    }
    SDL_Flip(screen);
}


void ABCbol_kihuz(char *betu){
    int i;
    for(i=0;i<35;++i){
        if(strcmp(ABC[i],betu)==0){
            szoveg_kiir("X", i%7*60+45, i/7*40+ablakmag-225 ,40, piros);
            SDL_Flip(screen);
            strcpy(ABC[i]," ");
        }
    }
}

void kiir_betuk(int betuszam, SDL_Color szin){
    int i=0;
    int x,y;
    while(strcmp(megfejtes[i],"0")!=0){
        if(strcmp(megfejtes[i]," ")!=0){
            if(betuszam<=16){
                x=560+50*i;
                y=560;
            }
            else if(i<betuszam/2){
                x=560+50*i;
                y=510;
            }
            else{
                x=510+50*(i-betuszam/2+1);
                y=560;
            }
            szoveg_kiir(megfejtes[i],x,y,35,szin);
        }
    ++i;
    }

}

void kiir_megfejtes(int betuszam, szavak *szo){
    int i=0;
    while(strcmp(megfejtes[i],"0")!=0){
        if(strcmp(megfejtes[i]," ")!=0)
            strcpy(megfejtes[i]," ");
        else
            strcpy(megfejtes[i],szo->szo[i]);
        ++i;
    }
    kiir_betuk(betuszam,utasitas_betuszin);
}
