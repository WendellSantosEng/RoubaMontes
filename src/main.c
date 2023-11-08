#include "roubamonte.h"

int main(){

    int quant_jog, ver_tm, ver_ed, ver_ec, cont_rodadas = 0;

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
    carta_comprada = (Carta *)malloc(sizeof(Carta));
    Carta *carta_descarte;
    carta_descarte = (Carta *)malloc(sizeof(Carta));
    Descarte *descarte;
    descarte = criaDescarte();

    for(int vez = 0; vez < quant_jog; vez++){

        cont_rodadas++;
        printf("Rodada %d", cont_rodadas);

        printf("Vez do jogador %d",vez+1);

        carta_comprada = compra(monte_baralho); 

        if(carta_comprada != NULL){
            ver_tm = verificaTopoMonte(lista_jogador,carta_comprada,vez);
            printf("entrou\n");
            printf("saiu\n");

            if(ver_tm == 1){
                printf("\n\nMonte Roubado\n\n");
            }else{
                printf("\n\nnao foi Roubado\n\n");
                carta_descarte = RetiraCarta(descarte,carta_comprada);
                printf("voltou de descarte");
                if(carta_descarte != NULL){
                    ver_ed = empilhaDescarte(lista_jogador, vez, carta_comprada, carta_descarte);
                    if(ver_ed == 1){
                        printf("\n\nCarta do descarte no seu monte\n\n");
                    }
                }else{
                    ver_ec = empilhaCarta(lista_jogador, vez, carta_comprada);
                    if(ver_ec == 1){
                        printf("\n\nCarta comprada no seu monte\n\n");
                    }else{
                        descartaCarta(descarte, carta_comprada);
                        printf("Carta descartada\n\n");
                    }
                }
            }
        }

        if(vez == quant_jog-1){
            vez = -1;
        }
    }

    lista_vencedor = verificaVencedor(lista_jogador);

    ListaCartasVencedora *cartas_vencer;
    cartas_vencer = criaListaCArtasVencedora();

    copiaCartasVencedor(lista_vencedor);

    ordenaCartas(lista_vencedor);



    deletaMonteBaralho(monte_baralho);
    deletaDescarte(descarte);
    deletaMontePlayer(lista_jogador);

    printf("\nFIM DE JOGO - TESTE\n\n");

    return 0;
}