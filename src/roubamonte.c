#include "roubamonte.h"

/*--------------------------------FUNÇÕES DO MONTE DE COMPRAS--------------------------------*/
//INICIO

MonteBaralho *criaMonteCompra(int quant_jog){

    MonteBaralho *monte_baralho;
    monte_baralho = (MonteBaralho *)malloc(sizeof(MonteBaralho));
    monte_baralho->topo = NULL;

    int repeat = 0;

    while(quant_jog >= 2 && repeat < 2){
        for(int j=0;j<4;j++){
            for(int k=0;k<13;k++){
                CartaMonteBaralho *carta_baralho;
                carta_baralho = (CartaMonteBaralho *)malloc(sizeof(CartaMonteBaralho));

                carta_baralho->carta = (Carta *)malloc(sizeof(Carta)); 

                carta_baralho->carta->valor = k+1;
                carta_baralho->carta->naipe = j+1;
                carta_baralho->anterior = monte_baralho->topo;

                monte_baralho->topo = carta_baralho;
            }
        }
        repeat++;
    };
    return monte_baralho;
}

void embaralha(MonteBaralho *monte_compra){

    srand(time(NULL));

    int tamanho = 0;
    CartaMonteBaralho *carta_atual = monte_compra->topo;

    while (carta_atual != NULL) {
        tamanho++;
        carta_atual = carta_atual->anterior;
    }

    // Embaralha as cartas usando o algoritmo de Fisher-Yates
    carta_atual = monte_compra->topo;

    for (int i = tamanho - 1; i > 0; i--) {

        int j = rand() % (i + 1);

        Carta *temp = carta_atual->carta;
        CartaMonteBaralho *carta_j = monte_compra->topo;
        for (int k = 0; k < j; k++) {
            carta_j = carta_j->anterior;
        }
        carta_atual->carta = carta_j->carta;
        carta_j->carta = temp;

        carta_atual = carta_atual->anterior;
    }
}

Carta *compra(MonteBaralho *monte_compra){

    Carta *carta;
    carta = (Carta *)malloc(sizeof(Carta));
    CartaMonteBaralho *aux;
    aux = monte_compra->topo;

    carta = monte_compra->topo->carta;
    monte_compra ->topo = monte_compra->topo->anterior;
    free(aux);

    return carta;
}

void deletaMonteBaralho(MonteBaralho *monte_compra){
    free(monte_compra);
}

//FIM
/*--------------------------------FUNÇÕES DO MONTE DO JOGADOR 1--------------------------------*/
//INICIO

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

    Jogador *atual;
    atual = lista_jogador->inicio;

    CartaMontePlayer *carta_nova;

    while(atual->quant_jogador != vez && atual->prox != NULL){
        printf("A carta do topo do monte do jogador %d e: %d de %d\n", atual->quant_jogador+1 , atual->monte->topo->carta->valor, atual->monte->topo->carta->naipe);
        atual = atual->prox;
    } 
    if(atual->quant_jogador == vez){

        if(atual->monte->topo->carta->valor == carta_comprada->valor){

            carta_nova->carta = carta_comprada;
            carta_nova->anterior = atual->monte->topo;

            atual->monte->topo = carta_nova;
            atual->monte->quant ++;

            printf("A carta esta em seu monte agora.\n");

            return 1;
        }
    }else{
        return 0;
    }
    return 0;
}

int empilhaDescarte(ListaPlayer *lista_jogador, int vez, Carta *carta_comprada, Carta *carta_descarte){

    printf("A Carta comprada e: %d de %d\n", carta_comprada->valor, carta_comprada->naipe);
    printf("A Carta do descarte e: %d de %d\n", carta_descarte->valor, carta_descarte->naipe);

    Jogador *atual;
    atual = lista_jogador->inicio;
    
    CartaMontePlayer *carta_nova;

    while(atual->quant_jogador != vez && atual->prox != NULL){
        atual = atual->prox;
    }
    if(atual->quant_jogador == vez){

        for(int i=0; i<2; i++){

            if(i==0){
                carta_nova->carta = carta_descarte;
            }else{
                carta_nova->carta = carta_comprada;
            }
            carta_nova->anterior = atual->monte->topo;
            atual->monte->topo = carta_nova;
            atual->monte->quant++;
        }
        printf("Ambas agora estao em meu monte.");
        return 1;
    }
    return 0;
}

int verificaTopoMonte(ListaPlayer *lista_jogador,Carta *carta_comprada,int vez){

    Jogador *atual;
    atual = lista_jogador->inicio;

    printf("entrou topo dos montes pra roubar\n");
    printf("A carta comprada e: %d de %d\n",  carta_comprada->valor, carta_comprada->naipe);

    while(atual->quant_jogador != vez && atual->prox != NULL){
        atual = atual->prox;
    }
    if(atual->quant_jogador == vez){

        MontePlayer *monte_da_vez = atual->monte;
        Jogador *jog_atual;
        MontePlayer *monte_saida;
        jog_atual = lista_jogador->inicio;

        while(jog_atual->prox != NULL){

            if(jog_atual->monte->topo->carta->valor == monte_da_vez->topo->carta->valor){

                monte_saida = jog_atual->monte;

                roubaMonte(monte_da_vez, monte_saida, carta_comprada);

                printf("Roubou\n");

                return 1;
            }
            
            jog_atual = jog_atual->prox;
        }
    }
    return 0;
}

int roubaMonte(MontePlayer *monte_destino, MontePlayer *monte_saida, Carta *carta_comprada){

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

    while(atual->carta->valor != carta_comprada->valor){
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

        novo = preencheJogador(lista_jogador, novo, i);
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

Jogador *preencheJogador(ListaPlayer *lista_jogador, Jogador *novo,int i){

    ListaPlayer *aux;

    printf("Insira o nome do jogador %d: ",i+1);
    fgets(novo->nome, 30, stdin);
    setbuf(stdin, NULL);
    novo->quant_jogador = i;
    novo->prox = NULL;

    MontePlayer *monte;
    monte = criaMontePlayer();

    if(lista_jogador->inicio == NULL){
        lista_jogador->inicio->monte = monte;
    }else{
        while(aux->inicio->monte != NULL){
            aux->inicio->monte = aux->inicio->prox->monte;
            aux->inicio = aux->inicio->prox;
        }
        aux->inicio->monte = monte;
    }

    novo->monte = aux->inicio->monte;

    return novo;
}

ListaPlayer *verificaVencedor(ListaPlayer *player, MontePlayer *monte_p1, MontePlayer *monte_p2, MontePlayer *monte_p3, MontePlayer *monte_p4){

    ListaPlayer *vencedores;
    vencedores = (ListaPlayer *)malloc(sizeof(ListaPlayer));

    vencedores->inicio = NULL;

    Jogador *atual;
    atual = player->inicio;
    Jogador *mai = atual;

    while(atual != NULL){

        if(atual->quant_jogador == 1){
            atual->quant_carta = monte_p1->quant;
        }
        if(atual->quant_jogador == 2){
            atual->quant_carta = monte_p2->quant;
        }
        if(atual->quant_jogador == 3){
            atual->quant_carta = monte_p3->quant;
        }
        if(atual->quant_jogador == 4){
            atual->quant_carta = monte_p4->quant;
        }

        atual = atual->prox;
    }

    atual = player->inicio;

    while(atual != NULL){
        if(atual->quant_carta == mai->quant_carta){
            
            Jogador* novo_vencedor = (Jogador*)malloc(sizeof(Jogador));// Adicione o jogador a lista de vencedores
            novo_vencedor->quant_jogador = atual->quant_jogador;
            novo_vencedor->quant_carta = atual->quant_carta;
            novo_vencedor->prox = vencedores->inicio;
            vencedores->inicio = novo_vencedor;
        }
        atual = atual->prox;
    }

    return vencedores;
}

ListaVencedor *criaListaVencedor(){
    ListaVencedor *lv;
    lv = (ListaVencedor *)malloc(sizeof(ListaVencedor));
    if(lv != NULL){
        lv->inicio = NULL;
        return lv;
    }
    return lv;    
}

void copiaCartasVencedor(ListaVencedor *lista_vencedor, MontePlayer *monte_vencedor){

    // PASSAR TODA A PILHA DO MONTE VENCEDOR PARA A LISTA = LISTAVENCEDOR;
    // PASSANDO PRO INICIO DA LISTA O(1)

    while(monte_vencedor->topo != NULL){
        CartaListaVencedor *novo_vencedor;
        novo_vencedor = (CartaListaVencedor *)malloc(sizeof(CartaListaVencedor));

        novo_vencedor->carta = monte_vencedor->topo->carta;
        monte_vencedor->topo = monte_vencedor->topo->anterior;

        if(lista_vencedor->inicio == NULL){
            lista_vencedor->inicio = novo_vencedor;
        }else{
            novo_vencedor->prox = lista_vencedor->inicio;
            lista_vencedor->inicio = novo_vencedor;
        }
    }
}

// ALGORITMO BUBBLE SORT - ORDENAÇÃO DE CARTA

void trocarCarta(Carta *a, Carta *b){
    Carta temp = *a;
    *a = *b;
    *b = temp;
}

void ordenaCartas(ListaVencedor *lista_vencedor){

    int trocado;
    CartaListaVencedor *ptr1;
    CartaListaVencedor *lptr = NULL;

    // Verifica se a lista está vazia
    if (lista_vencedor->inicio == NULL){
        return;
    }

    do{
        trocado = 0;
        ptr1 = lista_vencedor->inicio;

        while (ptr1->prox != lptr) {
            // Compara os valores das cartas
            if(ptr1->carta->valor > ptr1->prox->carta->valor){
                trocarCarta(ptr1->carta, ptr1->prox->carta);
                trocado = 1;
            }
            // Se os valores são iguais, compara os naipes
            else if (ptr1->carta->valor == ptr1->prox->carta->valor && ptr1->carta->naipe > ptr1->prox->carta->naipe){
                trocarCarta(ptr1->carta, ptr1->prox->carta);
                trocado = 1;
            }

            ptr1 = ptr1->prox;
        }
        lptr = ptr1;
    }while(trocado);
}

// IMPRIMINDO A LISTA DE CARTAS

void imprimirLista(ListaVencedor *lista){
    CartaListaVencedor *atual = lista->inicio;
    while(atual != NULL){
        printf("Valor: %d, Naipe: %d\n", atual->carta->valor, atual->carta->naipe);
        atual = atual->prox;
    }
}

// ALGORITMO BUBBLE SORT - ORDENAÇÃO DE JOGADOR

void trocarJogador(Jogador *a, Jogador *b){
    Jogador temp = *a;
    *a = *b;
    *b = temp;
}

void ordenarListaJogadores(ListaPlayer *lista){
    int trocado;
    Jogador *ptr1;
    Jogador *lptr = NULL;

    if (lista->inicio == NULL)
        return;
    do{
        trocado = 0;
        ptr1 = lista->inicio;

        while (ptr1->prox != lptr) {
            // Compara as quantidades de cartas dos jogadores
            if (ptr1->quant_carta > ptr1->prox->quant_carta) {
                trocarJogador(ptr1, ptr1->prox);
                trocado = 1;
            }
            ptr1 = ptr1->prox;
        }
        lptr = ptr1;
    }while(trocado);
}

// IMPRIMINDO O RANKING DE JOGADORES

void imprimirRanking(ListaPlayer *lista){
    Jogador *atual = lista->inicio;
    while (atual != NULL) {
        printf("Nome: %s, Quantidade de Cartas: %d\n", atual->nome, atual->quant_carta);
        atual = atual->prox;
    }
}

// FIM DAS FUNÇOES