#include "roubamonte.h"

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
        if(quant_jog == 2){
            break;
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



