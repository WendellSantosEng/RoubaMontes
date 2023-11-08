#include "roubamonte.h"

/*--------------------------------FUNÇÕES DO DESCARTE--------------------------------*/


Descarte *criaDescarte(){
    Descarte *descarte;
    descarte = (Descarte *)malloc(sizeof(Descarte));
    if(descarte != NULL){
        descarte->inicio = NULL;
    }
    return descarte;
}

void deletaDescarte(Descarte *descarte){
    while(descarte->inicio != NULL){
        CartaDescarte *aux;
        aux = descarte->inicio;
        descarte->inicio = descarte->inicio->prox;
        free(aux);
    }
    free(descarte);
}

void descartaCarta(Descarte *descarte, Carta *carta){ // INSERÇÃO NO INICIO O(1)
    CartaDescarte *carta_descarte;
    carta_descarte = (CartaDescarte *)malloc(sizeof(CartaDescarte));

    carta_descarte->carta = carta;
    carta_descarte->prox = descarte->inicio;
    descarte->inicio = carta_descarte;
}

Carta *RetiraCarta(Descarte *descarte, Carta *carta_comprada){

    printf("entrou retiracartas\n");
    CartaDescarte *atual, *anterior, *retorno;
    atual = descarte->inicio;

    if(descarte->inicio == NULL){
        return 0;
    }

    while(atual->carta->valor != carta_comprada->valor && atual->prox != NULL){
        anterior = atual;
        atual = atual->prox;
    }

    if(atual != NULL && atual->carta->valor == carta_comprada->valor){
        if(atual == descarte->inicio){
            descarte->inicio = atual->prox;
        }else{
            anterior->prox = atual->prox;
        }
        retorno = atual;
        free(atual);
    }

    printf("saiu\n");
    return (retorno != NULL) ? retorno->carta : NULL;
}

