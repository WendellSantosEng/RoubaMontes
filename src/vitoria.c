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

void copiaCartasVencedor(Jogador *vencedor){

    // PASSAR TODA A PILHA DO MONTE VENCEDOR PARA A LISTA;
    // PASSANDO PRO INICIO DA LISTA O(1)

    ListaBaralhoVencedor *lista;
    lista = criaBaralhoVencedor();

    CartaListaBaralhoVencedor *aux_lista = lista->inicio;

    while(vencedor->monte != NULL){

        if(aux_lista == NULL){
            aux_lista = vencedor->monte->topo;
        }else{
            CartaListaBaralhoVencedor *carta_v;

            carta_v = vencedor->monte->topo;
            carta_v->prox = vencedor->lista->inicio;
            vencedor->lista->inicio = carta_v;
            vencedor->monte->topo = vencedor->monte->topo->anterior;
        }
    }
}

void selectionSortCartas(ListaPlayer *lista_jogadores) {

    Jogador *aux = lista_jogadores->inicio;

    while (aux != NULL) {
        if (aux->venceu == 1) {
            break;
        }
        aux = aux->prox;
    }

    CartaListaBaralhoVencedor *i, *j, *min;

    for (i = aux->lista; i != NULL; i = i->prox) {
        min = i;

        for (j = i->prox; j != NULL; j = j->prox) {
            
            if (j->carta->valor < min->carta->valor ||
               (j->carta->valor == min->carta->valor && j->carta->naipe < min->carta->naipe)) {
                min = j;
            }
        }

        // Troca os dados dos nós
        Carta *temp = i->carta;
        i->carta = min->carta;
        min->carta = temp;
    }
}


void imprimeCartasVencedor(ListaPlayer *lista_jogador){

    Jogador *aux;
    aux = lista_jogador->inicio;

    while(aux != NULL && aux->venceu != 1){
        aux = aux->prox;
    }

    CartaListaBaralhoVencedor *aux2;
    aux2 = aux->lista->inicio;

    printf("\nIMPRESSAO DAS CARTAS DO VENCEDOR: \n");

    while(aux->lista != NULL){
        printf("VALOR %d <-> NAIPE %d\n", aux2->carta->valor, aux2->carta->naipe);
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