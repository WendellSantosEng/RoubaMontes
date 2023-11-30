#include "roubamonte.h"

/*
NAIPES:
1 - PAUS 
2 - COPAS
3 - ESPADAS
4 - OURO

VALOR:
1 - AS
11 - VALETE
12 - DAMA
13 - REI
*/

void imprimircarta(Carta *carta){

    int valor = carta->valor;
    int naipe = carta->naipe;

    if(valor == 1){
        printf("AS de ");
    }else if(valor == 11){
        printf("VALETE de ");
    }else if(valor == 12){
        printf("DAMA de ");
    }else if(valor == 13){
        printf("REI de ");
    }else if(valor >= 1 || valor <= 10){
        printf("%d de ",valor);
    }else{
        printf("Nao foi possivel imprimir essa carta, conteudo inexistente\n\n");
    }

    if(naipe == 1){
        printf("PAUS\n");
        return;
    }else if(naipe == 2){
        printf("COPAS\n");
        return;
    }else if(naipe == 3){
        printf("ESPADAS\n");
        return;
    }else if(naipe == 4){
        printf("OURO\n");
        return;
    }else{
        printf("Nao foi possivel imprimir essa carta, conteudo inexistente\n\n");
    }
}