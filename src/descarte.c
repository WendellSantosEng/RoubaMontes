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

int RetiraCarta(ListaPlayer *lista_jogador, int vez, Descarte *descarte, Carta *carta_comprada) {
    
    printf("\n--------------*DESCARTE ATUAL*--------------\n\n");
    imprimeDescarte(descarte);

    int ver;
    CartaDescarte *atual = descarte->inicio;
    CartaDescarte *anterior = NULL;
    Carta *retorno;
    retorno = (Carta *)malloc(sizeof(Carta));

    if(atual == NULL){
        return 0;
    }

    while (atual->prox != NULL && atual->carta->valor != carta_comprada->valor) {
        anterior = atual;
        atual = atual->prox;
    }

    if(atual->carta->valor == carta_comprada->valor){
        if(anterior == NULL){
            descarte->inicio = atual->prox;
        }else{
            anterior->prox = atual->prox;
        }
        retorno = atual->carta;
    }else{
        retorno = NULL;
    }

    ver = empilhaDescarte(lista_jogador, vez, carta_comprada, retorno);

    if (ver == 1) {
        return 1;
    } else {
        return 0;
    }
}


void imprimeDescarte(Descarte *descarte){
    CartaDescarte *aux;
    aux = descarte->inicio;
    int cont = 0;

    if (descarte->inicio == NULL) {
        printf("\n\nDESCARTE VAZIO\n\n");
        return;
    }

    while (aux != NULL) {
        cont++;
        aux = aux->prox;
    }

    aux = descarte->inicio;  // Reinicializa aux para o início da lista

    for (int i = 0; i < cont; i++) {
        printf("Carta Descarte numero %d: %d de %d\n", i + 1, aux->carta->valor, aux->carta->naipe);
        aux = aux->prox;
    }
}