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

int empilhaCarta(ListaPlayer *lista_jogador, int vez, Carta *carta_comprada){

    printf("A Carta comprada e: %d de %d\n", carta_comprada->valor, carta_comprada->naipe);
    vez = vez+1;

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

    while(atual->num_jogador != vez && atual->prox != NULL){
        atual = atual->prox;
    }
    
    if(atual->num_jogador == vez){

        printf("A carta do topo do monte do jogador %d e: %d de %d\n", atual->num_jogador+1 , atual->monte->topo->carta->valor, atual->monte->topo->carta->naipe);

        if(atual->monte->topo->carta->valor == carta_comprada->valor){

            carta_nova->carta = carta_comprada;
            carta_nova->anterior = atual->monte->topo;

            atual->monte->topo = carta_nova;
            atual->monte->quant ++;

            printf("A carta esta em seu monte agora.\n");

            printf("A quantidade de cartas no seu monte e: %d",atual->monte->quant);

            return 1;
        }
    }else{
        return 0;
    }
    return 0;
}

int empilhaDescarte(ListaPlayer *lista_jogador, int vez, Carta *carta_comprada, Carta *carta_descarte) {

    vez = vez+1;

    printf("A Carta comprada e: %d de %d\n", carta_comprada->valor, carta_comprada->naipe);
    if(carta_descarte != NULL){
        printf("A Carta do descarte e: %d de %d\n", carta_descarte->valor, carta_descarte->naipe);
    }else{
        printf("DEU RUIM\n");
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

            printf("Ambas agora estão em meu monte.\n");
            printf("A quantidade de cartas no seu monte é: %d\n", atual->monte->quant);

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

            printf("Ambas agora estão em meu monte.\n");
            printf("A quantidade de cartas no seu monte é: %d\n", atual->monte->quant);

            return 1;
        }
    }

    return 0;
}








int verificaCartaTopo(Jogador *atual,Carta *carta_comprada){

    if(atual->monte->topo->carta->valor == carta_comprada->valor){
        return 1;
    }

    return 0;
}



int verificaTopoMonte(ListaPlayer *lista_jogador,Carta *carta_comprada,int vez){

    Jogador *atual;
    atual = lista_jogador->inicio;
    int cont = 0, ver = 0;
    vez = vez+1;

    printf("A carta comprada e: %d de %d\n",  carta_comprada->valor, carta_comprada->naipe);

    if(lista_jogador->inicio == NULL){
        return 0;
    }

    while(atual->num_jogador != vez && atual->prox != NULL){
        atual = atual->prox;
    }

    //chama a função de verificar topo
    //se retornou 1 , rouba o monte
    MontePlayer *monte_da_vez;
    MontePlayer *monte_saida;

    if(atual->num_jogador == vez){
        monte_saida = atual->monte;
    }

    Jogador *aux2 = lista_jogador->inicio;
    Jogador *aux3 = lista_jogador->inicio;

    if(aux3->num_jogador != vez && aux3->monte->topo != NULL){
        printf("Topo do monte do jogador %d: %d de %d", aux3->num_jogador, aux3->monte->topo->carta->valor, aux3->monte->topo->carta->naipe);
        ver = verificaCartaTopo(aux3, carta_comprada);
        if(ver == 1){
            monte_da_vez = aux3->monte;
            roubaMonte(monte_da_vez, monte_saida, carta_comprada);
            return 1;
        }
    }

    while(aux2->prox != NULL && aux2->monte->topo != NULL){
        aux3 = aux3->prox;

        if(aux3->num_jogador != vez && aux3->monte->topo != NULL){
            printf("Topo do monte do jogador %d: %d de %d", aux3->num_jogador, aux3->monte->topo->carta->valor, aux3->monte->topo->carta->naipe);
            ver = verificaCartaTopo(aux3, carta_comprada);
            if(ver == 1){
                monte_da_vez = aux3->monte;
                roubaMonte(monte_da_vez, monte_saida, carta_comprada);
                return 1;
            }
        }
        aux2 = aux2->prox;
    }


    /*if(atual->num_jogador == vez){

        MontePlayer *monte_da_vez;
        monte_da_vez = atual->monte;
        printf("TOPO DA SAIDA: %d de %d\n",monte_da_vez->topo->carta->valor, monte_da_vez->topo->carta->naipe);
        Jogador *jog_atual;
        
        jog_atual = lista_jogador->inicio;

        if (monte_da_vez != NULL && monte_da_vez->topo != NULL) {
            printf("TOPO QUE GANHA CARTA: %d de %d\n", monte_da_vez->topo->carta->valor, monte_da_vez->topo->carta->naipe);
        } else {
            printf("Monte vazio ou ponteiros nulos.\n");
        }

        while(jog_atual->prox != NULL){

            if(jog_atual->monte->topo != NULL){
                printf("Topo do monte do jogador %d: %d de %d\n", jog_atual->num_jogador, jog_atual->monte->topo->carta->valor, jog_atual->monte->topo->carta->naipe);
            }

            jog_atual = jog_atual->prox;
            cont ++;

            if(jog_atual->monte->topo == NULL){
                printf("Monte do jogador %d vazio\n", jog_atual->num_jogador);

            }else{

                printf("Topo do monte do jogador dentro do else: jogador%d: %d de %d\n", jog_atual->num_jogador, jog_atual->monte->topo->carta->valor, jog_atual->monte->topo->carta->naipe);

                if(jog_atual->monte->topo->carta->valor == carta_comprada->valor){

                    printf("entrou no if\n");

                    monte_saida = jog_atual->monte;

                    roubaMonte(monte_da_vez, monte_saida, carta_comprada);

                    printf("Roubou\n");

                    printf("A quantidade de cartas no seu monte e: %d",atual->monte->quant);
                    printf("A quantidade de cartas no monte do oponente e: %d", jog_atual->monte->quant);

                    return 1;
                }
            }
            
            
            cont++;
        }
    }else{
        printf("ELSE DA FUNÇÂO\n");
        return 0;
    }*/
    return 0;
}
















/*int verificaTopoMonte(ListaPlayer *lista_jogador,Carta *carta_comprada,int vez){

    Jogador *atual;
    atual = lista_jogador->inicio;
    int cont = 0;
    vez = vez+1;

    printf("A carta comprada e: %d de %d\n",  carta_comprada->valor, carta_comprada->naipe);

    if(lista_jogador->inicio == NULL){
        return 0;
    }

    while(atual->num_jogador != vez && atual->prox != NULL){
        atual = atual->prox;
    }
    if(atual->num_jogador == vez){

        MontePlayer *monte_da_vez;
        monte_da_vez = atual->monte;
        printf("TOPO DA SAIDA: %d de %d\n",monte_da_vez->topo->carta->valor, monte_da_vez->topo->carta->naipe);
        Jogador *jog_atual;
        MontePlayer *monte_saida;
        jog_atual = lista_jogador->inicio;

        if (monte_da_vez != NULL && monte_da_vez->topo != NULL) {
            printf("TOPO QUE GANHA CARTA: %d de %d\n", monte_da_vez->topo->carta->valor, monte_da_vez->topo->carta->naipe);
        } else {
            printf("Monte vazio ou ponteiros nulos.\n");
        }

        while(jog_atual->prox != NULL){

            if(jog_atual->monte->topo != NULL){
                printf("Topo do monte do jogador %d: %d de %d\n", jog_atual->num_jogador, jog_atual->monte->topo->carta->valor, jog_atual->monte->topo->carta->naipe);
            }

            jog_atual = jog_atual->prox;
            cont ++;

            if(jog_atual->monte->topo == NULL){
                printf("Monte do jogador %d vazio\n", jog_atual->num_jogador);

            }else{

                printf("Topo do monte do jogador dentro do else: jogador%d: %d de %d\n", jog_atual->num_jogador, jog_atual->monte->topo->carta->valor, jog_atual->monte->topo->carta->naipe);

                if(jog_atual->monte->topo->carta->valor == carta_comprada->valor){

                    printf("entrou no if\n");

                    monte_saida = jog_atual->monte;

                    roubaMonte(monte_da_vez, monte_saida, carta_comprada);

                    printf("Roubou\n");

                    printf("A quantidade de cartas no seu monte e: %d",atual->monte->quant);
                    printf("A quantidade de cartas no monte do oponente e: %d", jog_atual->monte->quant);

                    return 1;
                }
            }
            
            
            cont++;
        }
    }else{
        printf("ELSE DA FUNÇÂO\n");
        return 0;
    }
    return 0;
}

*/int roubaMonte(MontePlayer *monte_destino, MontePlayer *monte_saida, Carta *carta_comprada){

    // DESEMPILHA PRA UMA PILHA AUX

    CartaMontePlayer *aux;

    while(monte_saida->topo != NULL){
        CartaMontePlayer *novo;
        novo = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

        novo->carta = monte_saida->topo->carta;
        novo->anterior = aux;
        aux = novo;

        free(monte_saida->topo);

        monte_saida->topo = monte_saida->topo->anterior;

        monte_saida->quant --;
    };

    // DESMPILHA AUX PARA A PILHA DO JOGADOR QUE ROUBOU

    while(aux != NULL){
        CartaMontePlayer *novo;
        novo = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

        novo->carta = aux->carta;
        novo->anterior = monte_destino->topo;
        monte_destino->topo = novo;

        CartaMontePlayer *temp = aux;

        aux = aux->anterior;
        free(temp);
        monte_destino->quant ++;
    };

    // COLOCA A CARTA COMPRADA NO TOPO

    CartaMontePlayer *novo;
    novo = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

    novo->carta = carta_comprada;
    novo->anterior = monte_destino->topo;
    monte_destino->topo = novo;
    monte_destino->quant ++;

    return 1;
}
