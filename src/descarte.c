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
    printf("\nO descarte atual e: \n");
    imprimeDescarte(descarte);

    int ver;
    CartaDescarte *atual = descarte->inicio;
    CartaDescarte *anterior = NULL;
    Carta *retorno = NULL;

    while (atual != NULL && atual->carta->valor != carta_comprada->valor) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL && atual->carta->valor == carta_comprada->valor) {
        if (anterior == NULL) {
            descarte->inicio = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }

        retorno = atual->carta;
        free(atual);
    }

    if (retorno != NULL) {
        printf("Verificou: %d de %d\n", retorno->valor, retorno->naipe);
    }

    ver = empilhaDescarte(lista_jogador, vez, carta_comprada, retorno);

    if (ver == 1) {
        printf("Verificou e retornou 1 pro main\n");
        return 1;
    } else {
        // Se necessário, liberar memória alocada para retorno
        // free(retorno);
        printf("Verificou e retornou 0 pro main\n");

        return 0;
    }
}


void imprimeDescarte(Descarte *descarte){

    CartaDescarte *aux;
    aux = descarte->inicio;
    int cont=0;
    if(descarte->inicio == NULL){
        return;
    }
    while(aux->prox != NULL){
        printf("Carta Descarte numero %d: %d de %d\n", cont+1, aux->carta->valor, aux->carta->naipe);
        cont++;
    }
    printf("Carta Descarte numero %d: %d de %d\n", cont+1, aux->carta->valor, aux->carta->naipe);
}
