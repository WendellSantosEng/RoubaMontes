#include "roubamonte.h"

/*--------------------------------FUNÇÕES DA VITORIA--------------------------------*/

ListaPlayer *criaListaJogadores(){
    ListaPlayer *lp;
    lp = (ListaPlayer *)malloc(sizeof(ListaPlayer));
    if(lp != NULL){
        lp->inicio = NULL;
    }
    return lp;
}

void listaJogadores(ListaPlayer *lista_jogador, int quant_jog){

    for(int i=0;i<quant_jog;i++){

        Jogador *novo, *atual;
        novo = (Jogador *)malloc(sizeof(Jogador));
        atual = lista_jogador->inicio;

        novo = preencheJogador(novo, i);
        novo->prox = NULL;

        if(i == 0){
            lista_jogador->inicio = novo;
        }else{
            while(atual->prox != NULL){
                atual = atual->prox;
            }
            atual->prox = novo;
        }
    }
}

Jogador *preencheJogador(Jogador *novo,int i){

    printf("Insira o nome do jogador %d: ", i + 1);
    setbuf(stdin,NULL);
    fgets(novo->nome, 30, stdin);
    setbuf(stdin,NULL);

    novo->num_jogador = i+1;
    novo->venceu = 0;
    novo->monte = criaMontePlayer();

    return novo;
}

Jogador *verificaVencedor(ListaPlayer *lista_jogador){

    if(lista_jogador->inicio == NULL){
        return NULL;
    }

    Jogador *atual = lista_jogador->inicio;
    Jogador *vencedor = atual;
    int mai = atual->monte->quant;

    while(atual != NULL){
        atual->quant_carta = atual->monte->quant;

        if(atual->quant_carta > mai){
            mai = atual->quant_carta;
            vencedor = atual;
        }

        atual = atual->prox;
    }

    return vencedor;
}

ListaBaralhoVencedor *criaBaralhoVencedor(){
    ListaBaralhoVencedor *lbv;
    lbv = (ListaBaralhoVencedor *)malloc(sizeof(ListaBaralhoVencedor));
    if(lbv != NULL){
        lbv->inicio = NULL;
        return lbv;
    }
    return lbv;    
}

void copiaCartasVencedor(ListaPlayer *lista_vencedor){

    // PASSAR TODA A PILHA DO MONTE VENCEDOR PARA A LISTA;
    // PASSANDO PRO INICIO DA LISTA O(1)

    Jogador *aux;
    aux = lista_vencedor->inicio;

    CartaListaBaralhoVencedor *carta_v;


    while(aux->prox != NULL){

        if(aux->venceu == 1){

            ListaBaralhoVencedor *lbv;
            lbv = criaBaralhoVencedor();

            while(aux->monte->topo != NULL){

                CartaListaBaralhoVencedor *aux_carta_v;
                aux_carta_v = (CartaListaBaralhoVencedor *)malloc(sizeof(CartaListaBaralhoVencedor));

                aux_carta_v->carta =  aux->monte->topo->carta;

                if(lbv->inicio == NULL){
                    lbv->inicio = carta_v;
                }else{
                    while(carta_v->prox != NULL){
                        carta_v = carta_v->prox;
                    }
                    carta_v->prox = carta_v;
                }
                aux->monte->topo = aux->monte->topo->anterior;
            }

            aux->lista = lbv;
        }

        aux = aux->prox;
    }
}

// ALGORITMO INSERTION - ORDENAÇÃO DE CARTA


// ALGORITMO INSERTION - ORDENAÇÃO DE JOGADOR

//levar em considerção o parametro da função imprimirRanking, onde ela cria um objeto pra lista de jogadores, 
//mas esse por sua vez esta ordenado por qauntidade de cartas;


// IMPRIMINDO O RANKING DE JOGADORES

void imprimirRanking(ListaPlayer *lista){
    Jogador *atual = lista->inicio;
    while (atual != NULL) {
        printf("Nome: %s, Quantidade de Cartas: %d\n", atual->nome, atual->quant_carta);
        atual = atual->prox;
    }
}

// FIM DAS FUNÇOES