#include "roubamonte.h"

int main(){

    int quant_jog, ver = -1;

    ListaPlayer *lista_jogador;
    lista_jogador = criaListaJogadores();

    ListaVencedor *lista_vencedor;
    lista_vencedor = criaListaVencedor();

    printf("BEM VINDO AO JOGO ROUBA-MONTES\n\n");

    do{
        printf("Insira quantos jogadores irao jogar: ");
        scanf("%d",&quant_jog);
        if(quant_jog < 2 || quant_jog > 4){
            printf("A quantidade de jogadores deve ser 2, 3 ou 4");
        }
    }while(quant_jog < 2 || quant_jog > 4);

    MonteBaralho *monte_baralho;
    monte_baralho = criaMonteCompra(quant_jog);

    embaralha(monte_baralho);

    MontePlayer *monte_p1;
    MontePlayer *monte_p2;
    MontePlayer *monte_p3;
    MontePlayer *monte_p4;

    for(int i=0;i<quant_jog;i++){
        if(i==0){
            monte_p1 = criaMontePlayer();
        }else if(i == 1){
            monte_p2 = criaMontePlayer();
        }else if(i == 2){
            monte_p3 = criaMontePlayer();
        }else if(i == 3){
            monte_p4 = criaMontePlayer();
        }
    }
    Carta *carta_comprada;
    Carta *carta_descarte;
    Descarte *descarte;
    descarte = criaDescarte();

    for(int vez = 1; vez <= quant_jog; vez++){

        if(vez == 1){
            // VEZ DO JOGADOR 1
            carta_comprada = compra(monte_baralho);
            if(carta_comprada != NULL){
                ver = 0; //verificaTopoMonte(monte_p1,monte_p2,monte_p3, monte_p4,carta_comprada,vez,quant_jog);
                if(ver == 1){
                    printf("\n\nMonte Roubado\n\n");
                }else{
                    printf("\n\nnao foi Roubado\n\n");
                    carta_descarte = RetiraCarta(descarte,carta_comprada);
                    printf("voltou de descarte");
                    if(carta_descarte != NULL){
                        ver = empilhaDescarte(monte_p1, carta_comprada, carta_descarte);
                        if(ver == 1){
                            printf("\n\nCarta do descarte no seu monte\n\n");
                        }
                    }else{
                        ver = empilhaCarta(monte_p1, carta_comprada);
                        if(ver == 1){
                            printf("\n\nCarta comprada no seu monte\n\n");
                        }else{
                            descartaCarta(descarte, carta_comprada);
                            printf("Carta descartada\n\n");
                        }
                    }
                }
            }
        }else if(vez == 2){
            // VEZ DO JOGADOR 2
            carta_comprada = compra(monte_baralho);
            if(carta_comprada != NULL){
                ver = verificaTopoMonte(monte_p1,monte_p2,monte_p3, monte_p4,carta_comprada,vez,quant_jog);
                if(ver == 1){
                    printf("\n\nMonte Roubado\n\n");
                }else{
                    carta_descarte = RetiraCarta(descarte,carta_comprada);
                    if(carta_descarte != NULL){
                        ver = empilhaDescarte(monte_p2, carta_comprada, carta_descarte);
                        if(ver == 1){
                            printf("\n\nCarta do descarte no seu monte\n\n");
                        }else{
                            ver = empilhaCarta(monte_p2, carta_comprada);
                            if(ver == 1){
                                printf("\n\nCarta comprada no seu monte\n\n");
                            }else{
                                descartaCarta(descarte, carta_comprada);
                            }
                        }
                    }
                }
            }
        }else if(vez == 3){
            // VEZ DO JOGADOR 3
            carta_comprada = compra(monte_baralho);
            if(carta_comprada != NULL){
                ver = verificaTopoMonte(monte_p1,monte_p2,monte_p3, monte_p4,carta_comprada,vez,quant_jog);
                if(ver == 1){
                    printf("\n\nMonte Roubado\n\n");
                }else{
                    carta_descarte = RetiraCarta(descarte,carta_comprada);
                    if(carta_descarte != NULL){
                        ver = empilhaDescarte(monte_p3, carta_comprada, carta_descarte);
                        if(ver == 1){
                            printf("\n\nCarta do descarte no seu monte\n\n");
                        }else{
                            ver = empilhaCarta(monte_p3, carta_comprada);
                            if(ver == 1){
                                printf("\n\nCarta comprada no seu monte\n\n");
                            }else{
                                descartaCarta(descarte, carta_comprada);
                            }
                        }
                    }
                }
            }
        }else if(vez == 4){
            // VEZ DO JOGADOR 4
            carta_comprada = compra(monte_baralho);
            if(carta_comprada != NULL){
                ver = 0; //verificaTopoMonte(monte_p1,monte_p2,monte_p3, monte_p4,carta_comprada,vez,quant_jog);
                if(ver == 1){
                    printf("\n\nMonte Roubado\n\n");
                }else{
                    carta_descarte = RetiraCarta(descarte,carta_comprada);
                    if(carta_descarte != NULL){
                        ver = empilhaDescarte(monte_p4, carta_comprada, carta_descarte);
                        if(ver == 1){
                            printf("\n\nCarta do descarte no seu monte\n\n");
                        }else{
                            ver = empilhaCarta(monte_p4, carta_comprada);
                            if(ver == 1){
                                printf("\n\nCarta comprada no seu monte\n\n");
                            }else{
                                descartaCarta(descarte, carta_comprada);
                            }
                        }
                    }
                }
            }
        }

        if(vez == quant_jog){
            vez = 0;
        }
        if(carta_comprada == NULL){
            break;
        }
    }

    deletaMonteBaralho(monte_baralho);
    deletaDescarte(descarte);
    deletaMontePlayerConteudo(monte_p1);
    deletaMontePlayerConteudo(monte_p2);
    deletaMontePlayerConteudo(monte_p3);
    deletaMontePlayerConteudo(monte_p4);
    deletaMontePlayerStruct(monte_p1);

    printf("\nFIM DE JOGO - TESTE\n\n");

    return 0;
}