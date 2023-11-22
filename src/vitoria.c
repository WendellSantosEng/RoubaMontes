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
    printf("Entrou copia cartas\n");

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
    printf("Entrou 1\n");

    printf("\nIMPRESSAO DAS CARTAS: \n");

    for(int i=0;i<quant;i++){
        printf("VALOR %d <-> NAIPE %d\n", vetor[i].valor, vetor[i].naipe);
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
    printf("Entrou 2\n");

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

    printf("Entrou 3\n");

    free(vetor);

    printf("Saiu copia cartas\n");
}

void imprimeCartasVencedor(ListaPlayer *lista_jogador){

    Jogador *aux;
    aux = lista_jogador->inicio;

    while(aux != NULL && aux->venceu != 1){
        aux = aux->prox;
    }

    printf("\nIMPRESSAO DAS CARTAS DO VENCEDOR: \n");

    while(aux->monte->topo != NULL){
        printf("VALOR %d <-> NAIPE %d\n", aux->monte->topo->carta->valor, aux->monte->topo->carta->naipe);
        aux->monte->topo = aux->monte->topo->anterior;
    }
}

void ordenarJogadoresPorQuantidadeDeCartas(ListaPlayer *lista_jogadores) {
    Jogador *i, *j, *min;

    // Percorre a lista de jogadores
    for (i = lista_jogadores->inicio; i != NULL; i = i->prox) {
        min = i;

        // Percorre os jogadores restantes
        for (j = i->prox; j != NULL; j = j->prox) {
            // Comparação considerando a quantidade de cartas
            if (j->quant_carta < min->quant_carta) {
                min = j;
            }
        }
        // Troca os dados dos jogadores
        Jogador temp = *i;
        *i = *min;
        *min = temp;
    }
}

void imprimirRanking(ListaPlayer *lista){

    Jogador *atual = lista->inicio;
    while (atual != NULL) {
        printf("Nome: %s, Quantidade de Cartas: %d\n", atual->nome, atual->quant_carta);
        atual = atual->prox;
    }
}

// FIM DAS FUNÇOES