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

    printf("\n ->->->->->-> NOME DO JOGADOR %d <-<-<-<-<-<- ", i + 1);
    setbuf(stdin,NULL);
    fgets(novo->nome, 30, stdin);
    setbuf(stdin,NULL);

    novo->num_jogador = i;
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

    vencedor->venceu = 1;
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

void copiaCartasVencedor(Jogador *vencedor) {

    int quant = vencedor->monte->quant;
    int cont=0;

    Carta *vetor;
    vetor = (Carta *)malloc(quant * sizeof(Carta));

    while(vencedor->monte->topo != NULL){

        vetor[cont].valor = vencedor->monte->topo->carta->valor;
        vetor[cont].naipe = vencedor->monte->topo->carta->naipe;

        cont ++;
        vencedor->monte->topo = vencedor->monte->topo->anterior;
    }

    deletaMonte(vencedor->monte);

    vencedor->monte = criaMontePlayer();

    Carta *aux;
    aux = (Carta *)malloc(sizeof(Carta));

    // ORDENA
    for(int i = 1;i < quant;i++){
        aux->valor = vetor[i].valor;
        aux->naipe = vetor[i].naipe;

        int j = i - 1;
        while (aux->valor > vetor[j].valor && j >= 0){
            vetor[j+1].valor = vetor[j].valor;
            vetor[j+1].naipe = vetor[j].naipe;
            j--;
        }
        vetor[j+1].valor = aux->valor;
        vetor[j+1].naipe = aux->naipe;
    }

    for (int i = 0; i < quant; i++) {
        CartaMontePlayer *carta_monte;
        carta_monte = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));
        
        carta_monte->carta = (Carta *)malloc(sizeof(Carta));
        carta_monte->carta->naipe = vetor[i].naipe;
        carta_monte->carta->valor = vetor[i].valor;

        if (vencedor->monte->topo == NULL) {
            carta_monte->anterior = NULL;
        } else {
            carta_monte->anterior = vencedor->monte->topo;
        }
        vencedor->monte->topo = carta_monte;
    }

    free(vetor);
}

void imprimeCartasVencedor(ListaPlayer *lista_jogador){

    Jogador *aux;
    aux = lista_jogador->inicio;

    while(aux != NULL && aux->venceu != 1){
        aux = aux->prox;
    }

    printf("\nIMPRESSAO DAS CARTAS DO VENCEDOR ORDENADAS: \n");

    CartaMontePlayer *topo_original = aux->monte->topo;

    while(aux->monte->topo != NULL){
        imprimircarta(aux->monte->topo->carta);
        aux->monte->topo = aux->monte->topo->anterior;
    }

    aux->monte->topo = topo_original;
}


void ordenarJogadoresPorQuantidadeDeCartas(ListaPlayer *lista_jogadores, int quant_jog) {
    
    Jogador *aux;
    aux = lista_jogadores->inicio;

    Jogador *vetor;
    vetor = (Jogador *)malloc(quant_jog*sizeof(Jogador));

    for(int i=0;i<quant_jog;i++){
        vetor[i] = (*aux);
        aux = aux->prox;
    }

    int i, j, min;
    Jogador temp; 

    //usando o insert sort para ordenar o vetor

    for (i = 0; i < quant_jog - 1; i++) {
        min = i;
        for (j = i + 1; j < quant_jog; j++) {
            if (vetor[j].quant_carta < vetor[min].quant_carta) {
                min = j;
            }
        }
        temp = vetor[min];
        vetor[min] = vetor[i];
        vetor[i] = temp;
    }

    //inverte o vetor

    int inicio = 0;
    int fim = quant_jog - 1;

    while (inicio < fim) {

        Jogador temp = vetor[inicio];
        vetor[inicio] = vetor[fim];
        vetor[fim] = temp;

        inicio++;
        fim--;
    }

    imprimirRanking(vetor, quant_jog);
}


void imprimirRanking(Jogador vetor[], int quant_jog){

    for(int i=0; i<quant_jog;i++){

        printf("---------------------------------------------------------------\n");
        printf("|      NOME : %s  <-->  Quantidade de Cartas: %d      |\n", vetor[i].nome, vetor[i].quant_carta);
        printf("---------------------------------------------------------------");
    }

    free(vetor);
}

// FIM DAS FUNÇOES