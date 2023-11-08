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

    printf("Insira o nome do jogador %d: ", i + 1);
    setbuf(stdin,NULL);
    fgets(novo->nome, 30, stdin);
    setbuf(stdin,NULL);

    novo->quant_jogador = i;
    novo->monte = criaMontePlayer();

    return novo;
}

ListaVencedor *verificaVencedor(ListaPlayer *lista_jogador){

    ListaVencedor *vencedores;
    vencedores = (ListaVencedor *)malloc(sizeof(ListaVencedor));

    vencedores->inicio = NULL;

    JogadorVencedor *atual;
    atual = vencedores->inicio;
    int mai = atual->jogador->quant_carta;

    while(atual->prox != NULL){

        atual->jogador->quant_carta = atual->jogador->monte->quant;

        atual = atual->prox;
    }

    atual = vencedores->inicio;

    while(atual->prox != NULL){
        if(atual->jogador->quant_carta == mai){
            
            JogadorVencedor* novo_vencedor = (JogadorVencedor*)malloc(sizeof(JogadorVencedor));// Adicione o jogador a lista de vencedores
            novo_vencedor->jogador->quant_jogador = atual->jogador->quant_jogador;
            novo_vencedor->jogador->quant_carta = atual->jogador->quant_carta;
            novo_vencedor->jogador->monte = atual->jogador->monte;
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

ListaJogadoresVencedoresLISTA *criaListaCArtasVencedora(){
    ListaJogadoresVencedoresLISTA *lv;
    lv = (ListaJogadoresVencedoresLISTA *)malloc(sizeof(ListaJogadoresVencedoresLISTA));
    if(lv != NULL){
        lv->inicio = NULL;
        return lv;
    }
    return lv;
}

void copiaCartasVencedor(ListaVencedor *lista_vencedor){

    // PASSAR TODA A PILHA DO MONTE VENCEDOR PARA A LISTA = LISTAVENCEDOR;
    // PASSANDO PRO INICIO DA LISTA O(1)

    JogadorVencedor *aux;
    aux = lista_vencedor->inicio;

    ListaJogadoresVencedoresLISTA *auxiliar;
    auxiliar->inicio = NULL;

    do{


        while(aux->jogador->monte->topo->anterior != NULL){
            ListaFinalJogadoresVencedoresELEMENTO *new;
            new = (ListaFinalJogadoresVencedoresELEMENTO *)malloc(sizeof(ListaFinalJogadoresVencedoresELEMENTO));

            new->carta = aux->jogador->monte->topo->carta;
            
            new->quant_cartas ++;
            
            new->prox = NULL;

            if(auxiliar->inicio == NULL){
                auxiliar->inicio->carta = new->carta;
                auxiliar->inicio->quant_cartas = new->quant_cartas;
            }else{
                while(auxiliar->inicio->prox != NULL){
                    auxiliar = ;
                }
                auxiliar->inicio->prox = new;
            }

            aux->jogador->monte->topo = aux->jogador->monte->topo->anterior;
        }

        if(lista_vencedor->inicio == NULL){
            lista_vencedor->inicio = aux;
        }else{
            aux->prox = lista_vencedor->inicio;
            lista_vencedor->inicio = aux;
        }
        
        aux = aux->prox;   


    }while(aux->prox != NULL);
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