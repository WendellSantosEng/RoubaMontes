#include "roubamonte.h"

/*--------------------------------FUNÇÕES DO JOGO--------------------------------*/

MontePlayer *criaMontePlayer(){
    MontePlayer *monte;
    monte = (MontePlayer *)malloc(sizeof(MontePlayer));
    monte->topo = NULL;
    monte->quant = 0;
    return monte;
}

void deletaMontePlayer(ListaPlayer *lp){
    while(lp->inicio != NULL){
        CartaMontePlayer *carta_delete;
        while(lp->inicio->monte->topo != NULL){
            carta_delete = lp->inicio->monte->topo;
            lp->inicio->monte->topo = lp->inicio->monte->topo->anterior;
            free(carta_delete);
        }
        lp->inicio = lp->inicio->prox;
    }
    free(lp);
}

void deletaMonte(MontePlayer *monte) {
    if(monte == NULL){
        return;
    }
    CartaMontePlayer *atual = monte->topo;
    CartaMontePlayer *proximo;
    while(atual != NULL){
        proximo = atual->anterior;
        free(atual);
        atual = proximo;
    }
    monte->topo = NULL;
}

int empilhaCarta(ListaPlayer *lista_jogador, int vez, Carta *carta_comprada){

    printf("\n-------------------CARTA COMPRADA-------------------\n");
    printf(" %d de %d\n\n", carta_comprada->valor, carta_comprada->naipe);

    Jogador *atual;
    atual = lista_jogador->inicio;

    if(lista_jogador->inicio == NULL){
        return 0;
    }
    if(atual->monte->topo == NULL){
        return 0;
    }
    CartaMontePlayer *carta_nova;
    carta_nova = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

    while(atual->num_jogador != vez && atual != NULL){
        atual = atual->prox;
    }
    
    if(atual->num_jogador == vez && atual->monte->topo != NULL){

        printf("\n-------------------CARTA COMPRADA-------------------\n");
        printf(" %d de %d\n\n", carta_comprada->valor, carta_comprada->naipe);

        if(atual->monte->topo->carta->valor == carta_comprada->valor){

            carta_nova->carta = carta_comprada;
            carta_nova->anterior = atual->monte->topo;

            atual->monte->topo = carta_nova;
            atual->monte->quant ++;

            printf("\n\n-------------------CARTA NO SEU MONTE-------------------\n\n");
            printf("\n----------QUANTIDADE DE CARTAS NO SEU MONTE e: %d-------------------\n\n",atual->monte->quant);

            return 1;
        }
    }else{
        return 0;
    }
    return 0;
}

int empilhaDescarte(ListaPlayer *lista_jogador, int vez, Carta *carta_comprada, Carta *carta_descarte) {


    printf("\n-------------------CARTA COMPRADA-------------------\n");
    printf(" %d de %d\n", carta_comprada->valor, carta_comprada->naipe);

    if(carta_descarte != NULL){
        printf("\n------------------CARTA DO COMPRADA-----------------\n");
        printf(" %d de %d\n", carta_descarte->valor, carta_descarte->naipe);
    }

    if(carta_descarte != NULL){
        Jogador *atual;
        atual = lista_jogador->inicio;

        if(atual->monte->topo == NULL){
            CartaMontePlayer *carta_nova = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));
            carta_nova->carta = carta_descarte;
            carta_nova->anterior = atual->monte->topo;
            atual->monte->topo = carta_nova;
            atual->monte->quant++;

            // Criação e empilhamento da carta comprada
            CartaMontePlayer *carta_nova2 = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));
            carta_nova2->carta = carta_comprada;
            carta_nova2->anterior = carta_nova; // Agora a segunda carta é empilhada sobre a primeira
            atual->monte->topo = carta_nova2;
            atual->monte->quant++;

            printf("--------------AMBAS ESTAO EM SEU MONTES---------------\n");
            printf("\n-------QUANTIDADE DE CARTAS NO SEU MONTE e: %d-------\n",atual->monte->quant);

            return 1;
        }

        while (atual->num_jogador != vez && atual->prox != NULL) {
            atual = atual->prox;
        }

        if (atual->num_jogador == vez) {
            // Criação e empilhamento da carta do descarte
            CartaMontePlayer *carta_nova = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));
            carta_nova->carta = carta_descarte;
            carta_nova->anterior = atual->monte->topo;
            atual->monte->topo = carta_nova;
            atual->monte->quant++;

            // Criação e empilhamento da carta comprada
            CartaMontePlayer *carta_nova2 = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));
            carta_nova2->carta = carta_comprada;
            carta_nova2->anterior = carta_nova; // Agora a segunda carta é empilhada sobre a primeira
            atual->monte->topo = carta_nova2;
            atual->monte->quant++;

            printf("--------------AMBAS ESTAO EM SEU MONTES---------------\n");
            printf("\n-------QUANTIDADE DE CARTAS NO SEU MONTE e: %d-------\n",atual->monte->quant);

            return 1;
        }
    }

    return 0;
}

int verificaCartaTopo(Jogador *atual,Carta *carta_comprada){

    if(atual->monte->topo == NULL){
        return 0;
    }
    if(atual->monte->topo->carta->valor == carta_comprada->valor){
        return 1;
    }else{
        return 0;
    }
    return 0;
}

int verificaTopoMonte(ListaPlayer *lista_jogador,Carta *carta_comprada,int vez){

    Jogador *atual;
    atual = lista_jogador->inicio;
    int ver = 0;
    MontePlayer *monte_dps_roubo;

    printf("\n-------------------CARTA COMPRADA-------------------\n");
    printf(" %d de %d\n", carta_comprada->valor, carta_comprada->naipe);

    if(lista_jogador->inicio == NULL){
        return 0;
    }

    while(atual->num_jogador != vez && atual->prox != NULL){
        atual = atual->prox;
    }

    //chama a função de verificar topo
    //se retornou 1 , rouba o monte
    MontePlayer *monte_da_vez;
    monte_da_vez = (MontePlayer *)malloc(sizeof(MontePlayer));
    MontePlayer *monte_saida;
    monte_saida = (MontePlayer *)malloc(sizeof(MontePlayer));

    if(atual->num_jogador == vez){
        monte_da_vez = atual->monte;
    }

    int quant_roubo;

    Jogador *aux2 = lista_jogador->inicio;

    while(aux2 != NULL){

        if(aux2->num_jogador != vez){

            ver = verificaCartaTopo(aux2, carta_comprada);

            if(ver == 1){
                monte_saida = aux2->monte;

                monte_dps_roubo = roubaMonte(monte_da_vez, monte_saida, carta_comprada, &quant_roubo);

                if(monte_dps_roubo != NULL){ // usado apenas pra ter 100% de certeza

                    atual->monte = monte_dps_roubo; //iguala o monte ao do jogador
                    atual->monte->quant = quant_roubo; // iguala a qauntidade
                    aux2->monte->quant = 0; // zera o roubado

                    return 1;
                }else{
                    return 0;
                }
            }
        }
        aux2 = aux2->prox;
    }

    return 0;
}

MontePlayer *roubaMonte(MontePlayer *monte_destino, MontePlayer *monte_saida, Carta *carta_comprada, int *quant_roubo){

    // DESEMPILHA PRA UMA PILHA AUX

    MontePlayer *monte_aux;
    monte_aux = criaMontePlayer();

    while(monte_saida->topo != NULL){

        CartaMontePlayer *aux;
        CartaMontePlayer *novo;
        novo = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

        novo->carta = monte_saida->topo->carta;

        if(monte_aux->topo == NULL){
            novo->anterior = NULL;
            monte_aux->topo = novo;
        }else{
            novo->anterior = monte_aux->topo;
            monte_aux->topo = novo;
        }

        aux = monte_saida->topo;

        monte_saida->topo = monte_saida->topo->anterior;

        free(aux);
    };

    while(monte_aux->topo != NULL){

        CartaMontePlayer *aux;
        CartaMontePlayer *novo;
        novo = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

        novo->carta = monte_aux->topo->carta;

        if(monte_destino->topo == NULL){
            novo->anterior = NULL;
            monte_destino->topo = novo;
        }else{
            novo->anterior = monte_destino->topo;
            monte_destino->topo = novo;
        }

        aux = monte_aux->topo;
        monte_aux->topo = monte_aux->topo->anterior;
        monte_destino->quant++;
        
        monte_aux->quant --;

        free(aux);
    };

    // COLOCA A CARTA COMPRADA NO TOPO

    CartaMontePlayer *novo;
    novo = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

    novo->carta = carta_comprada;
    novo->anterior = monte_destino->topo;
    monte_destino->topo = novo;
    monte_destino->quant ++;

    (*quant_roubo) = monte_destino->quant;

    return monte_destino;
}
