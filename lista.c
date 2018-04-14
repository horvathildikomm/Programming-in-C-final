#include "main.h"
#include "lista.h"


szavak *szavak_beolvas(char *file_nev){
    FILE* fp;
    fp = fopen(file_nev, "r");
    if (fp != NULL) {
        szavak *eleje=NULL;
        char temp[30+1];
        while(fscanf(fp,"%s\n",temp)==1){
            szavak *uj=(szavak *)malloc(sizeof(szavak));
            feltolt_adattal(uj,temp);
            uj->kovetkezo=eleje;
            eleje=uj;
        }
        fclose(fp);
        return eleje;
    }
    else {
        perror("Nem sikerült megnyitni a fájlt");
        return NULL;
    }
}


void feltolt_adattal(szavak *elem ,char *szo){

    int i=0;
    int j=0;
    while(szo[i]!='\0'){
        if((szo[i]&0x80)==0x00){ //egy bájtos betű
            elem->szo[j][0]=szo[i++];
            elem->szo[j][1]='\0';
        }
        else if((szo[i]&0xe0)==0xc0){ //két bájtos betű
            elem->szo[j][0]=szo[i++];
            elem->szo[j][1]=szo[i++];
            elem->szo[j][2]='\0';
        }
        else if((szo[i]&0xf0)==0xe0){   //három bájtos betű
            elem->szo[j][0]=szo[i++];
            elem->szo[j][1]=szo[i++];
            elem->szo[j][2]=szo[i++];
            elem->szo[j][3]='\0';
        }
       ++j;
    }
    elem->betuszam=j;

}

szavak *torol_mas_betuszamuak(int betuszam,szavak *eleje){
    szavak *mozgo=eleje;
    szavak *lemarado=NULL;
    while(mozgo!=NULL){
        if(mozgo->betuszam!=betuszam){  //ha törölni kell
            if(lemarado==NULL){      //ha az elsőt kell
                eleje=mozgo->kovetkezo;
                free(mozgo);
                mozgo=eleje;
            }
            else{   //a közepéről vagy végéről kell
                lemarado->kovetkezo=mozgo->kovetkezo;
                free(mozgo);
                mozgo=lemarado->kovetkezo;

            }
        }
        else{    //ha nem kellett
            lemarado=mozgo;
            mozgo=mozgo->kovetkezo;
        }
    }
    return eleje;
}


szavak *torol_ha_van_benne(char *betu,szavak *eleje){
    szavak *mozgo=eleje;
    szavak *lemarado=NULL;
    while(mozgo!=NULL){
        if(tartalmazza(mozgo,betu)>0){  //ha törölni kell
            if(lemarado==NULL){      //ha az elsőt kell
                eleje=mozgo->kovetkezo;
                free(mozgo);
                mozgo=eleje;
            }
            else{   //a közepéről vagy végéről kell
                lemarado->kovetkezo=mozgo->kovetkezo;
                free(mozgo);
                mozgo=lemarado->kovetkezo;

            }
        }
        else{    //ha nem kellett
            lemarado=mozgo;
            mozgo=mozgo->kovetkezo;
        }
    }
    return eleje;
}


int tartalmazza(szavak *szo, char* betu){
    int i;
    int db=0;
    for(i=0;i<szo->betuszam;++i){
        if(strcmp(szo->szo[i],betu)==0){
            db+=1;
        }
    }
    return db;
}

szavak *torol_nem_min(int minimum,char *betu, szavak *eleje){
    szavak *mozgo=eleje;
    szavak *lemarado=NULL;
    while(mozgo!=NULL){
        if(tartalmazza(mozgo,betu)!=minimum){  //ha törölni kell
            if(lemarado==NULL){      //ha az elsőt kell
                eleje=mozgo->kovetkezo;
                free(mozgo);
                mozgo=eleje;
            }
            else{   //a közepéről vagy végéről kell
                lemarado->kovetkezo=mozgo->kovetkezo;
                free(mozgo);
                mozgo=lemarado->kovetkezo;

            }
        }
        else{    //ha nem kellett
            lemarado=mozgo;
            mozgo=mozgo->kovetkezo;
        }
    }
    return eleje;

}



void felszabadit_lista(szavak *eleje){
    szavak *mozgo=eleje;
    szavak *kovetkezo;
    while(mozgo!=NULL){
        kovetkezo=mozgo->kovetkezo;
        free(mozgo);
        mozgo=kovetkezo;
    }
}


bool jo_helyen_van(szavak *szo){
    int i;
    for(i=0;i<szo->betuszam;++i){
        if(strcmp(megfejtes[i]," ")!=0){
            if(strcmp(szo->szo[i],megfejtes[i])!=0)
                return false;
        }
    }
    return true;

}

szavak *torol_ha_rossz_helyen(szavak *eleje){
    szavak *mozgo=eleje;
    szavak *lemarado=NULL;
    while(mozgo!=NULL){
        if(!jo_helyen_van(mozgo)){
            if(lemarado==NULL){      //ha az elsőt kell
                eleje=mozgo->kovetkezo;
                free(mozgo);
                mozgo=eleje;
            }
            else{   //a közepéről vagy végéről kell
                lemarado->kovetkezo=mozgo->kovetkezo;
                free(mozgo);
                mozgo=lemarado->kovetkezo;

            }
        }
        else{    //ha nem kellett
            lemarado=mozgo;
            mozgo=mozgo->kovetkezo;
        }
    }
    return eleje;
}


