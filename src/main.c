#include "roubamonte.h"

int main(){

    int quant_jog, ver = -1;

    ListaVencedor *lista_vencedor;
    lista_vencedor = criaListaVencedor();

    printf("BEM VINDO AO JOGO ROUBA-MONTES\n\n");

    printf("Insira quantos jogadores irao jogar: ");
    scanf("%d",&quant_jog);
    if(quant_jog < 2 || quant_jog > 4){
        printf("A quantidade de jogadores deve ser 2, 3 ou 4");
    }
    
    ListaPlayer *lista_jogador;
    lista_jogador = criaListaJogadores();

    listaJogadores(lista_jogador, quant_jog);

    MonteBaralho *monte_baralho;
    monte_baralho = criaMonteCompra(quant_jog);

    embaralha(monte_baralho);

    Carta *carta_comprada;
    Carta *carta_descarte;
    Descarte *descarte;
    descarte = criaDescarte();

    for(int vez = 0; vez < quant_jog; vez++){

        carta_comprada = compra(monte_baralho);
        if(carta_comprada != NULL){
            verificaTopoMonte(lista_jogador,carta_comprada,vez);
            if(ver == 1){
                printf("\n\nMonte Roubado\n\n");
            }else{
                printf("\n\nnao foi Roubado\n\n");
                carta_descarte = RetiraCarta(descarte,carta_comprada);
                printf("voltou de descarte");
                if(carta_descarte != NULL){
                    ver = empilhaDescarte(lista_jogador, vez, carta_comprada, carta_descarte);
                    if(ver == 1){
                        printf("\n\nCarta do descarte no seu monte\n\n");
                    }
                }else{
                    ver = empilhaCarta(lista_jogador, vez, carta_comprada);
                    if(ver == 1){
                        printf("\n\nCarta comprada no seu monte\n\n");
                    }else{
                        descartaCarta(descarte, carta_comprada);
                        printf("Carta descartada\n\n");
                    }
                }
            }
        }

        if(vez == quant_jog){
            vez = -1;
        }
    }

    deletaMonteBaralho(monte_baralho);
    deletaDescarte(descarte);
    deletaMontePlayer(lista_jogador);

    printf("\nFIM DE JOGO - TESTE\n\n");

    return 0;
}