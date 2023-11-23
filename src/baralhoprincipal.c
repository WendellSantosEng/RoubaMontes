#include "roubamonte.h"

/*--------------------------------FUNÇÕES DO MONTE DE COMPRAS--------------------------------*/

MonteBaralho *criaMonteCompra(int quant_jog){

    MonteBaralho *monte_baralho;
    monte_baralho = (MonteBaralho *)malloc(sizeof(MonteBaralho));
    monte_baralho->topo = NULL;
    monte_baralho->quantidade_baralho = 0;

    int repeat = 0;

    for(int i=0;i<quant_jog;i++){
        if(i%2 == 1){
            repeat ++;
        }
    }

    while(repeat != 0){
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
        monte_baralho->quantidade_baralho ++;
        repeat--;
    }
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
    if(monte_compra->topo != NULL){

        Carta *carta;
        carta = (Carta *)malloc(sizeof(Carta));
        CartaMonteBaralho *aux;
    
        aux = monte_compra->topo;
        carta = monte_compra->topo->carta;
        if(carta != NULL){
            monte_compra ->topo = monte_compra->topo->anterior;
            free(aux);


            /*int layer[3][3];

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {

                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 7 | (15 << 4));  // Cor de fundo branca // 7 é o código para branco

                    printf("%3d ", layer[i][j]);
                }
                printf("\n");
            }*/
            

            return carta;
        }else{
            return NULL;
        }
    }else{
        return NULL;
    }
}

void deletaMonteBaralho(MonteBaralho *monte_compra){
    free(monte_compra);
}
