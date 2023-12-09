#include "roubamonte.h"

int main(){

    int quant_jog, ver_tm, ver_ec, cont_rodadas = 0, ver_dc, info = 0;

    printf("-----------------------------------------------------------------------------------\n");
    printf("|                                                                                  |\n");
    printf("|                 BEM VINDO AO JOGO ROUBA-MONTES                                   |\n");
    printf("|                                                                                  |\n");
    printf("-----------------------------------------------------------------------------------\n");

    printf("\n---> DESEJA IMPRIMIR AS INFORMACOES: 1- SIM ; 2- NAO\n");
    scanf("%d", &info);

    if(info == 1){
        const char *nomeArquivo = "src/info.txt";
        FILE *arquivo = fopen(nomeArquivo, "r");

        if(arquivo == NULL){
            printf(" => Erro ao abrir o arquivo %s\n", nomeArquivo);
        }else{
            char linha[100];
            while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                printf("%s", linha);
            }
            fclose(arquivo);
        }
    }else if(info == 2){
        printf(" => Voce escolheu NAO. As regras nao serao impressas.\n\n");
    }else{
        printf(" => Opcao invalida. Por favor, escolha 1 (SIM) ou 2 (NAO).\n");
    }

    printf("=> QUANTOS JOGADORES SERAO : ");
    scanf("%d",&quant_jog);
    
    ListaPlayer *lista_jogador;
    lista_jogador = criaListaJogadores();

    listaJogadores(lista_jogador, quant_jog);

    MonteBaralho *monte_baralho;
    monte_baralho = criaMonteCompra(quant_jog);

    printf("\n\n---------------O JOGO SERA COM %d BARALHO(S)--------------\n\n", monte_baralho->quantidade_baralho);

    embaralha(monte_baralho);

    Carta *carta_comprada;
    carta_comprada = (Carta *)malloc(sizeof(Carta));

    Descarte *descarte;
    descarte = criaDescarte();

    for(int vez = 0; vez < quant_jog; vez++){

        carta_comprada = NULL;
        cont_rodadas++;
        
        sleep(1);

        printf("\n----------------------------------------------------------------------------------------------------\n");
        printf("\n---------------RODADA %d - ", cont_rodadas);

        printf(" ==>> VEZ DO JOGADOR %d---------------\n\n",vez+1);

        carta_comprada = compra(monte_baralho); // compra uma carta

        if(carta_comprada != NULL){ // se a carta comprada for valida

            ver_tm = verificaTopoMonte(lista_jogador,carta_comprada,vez); // verifica o topo dos outros montes
            sleep(1);

            if(ver_tm == 1){ // se tem igual , rouba

                printf("\n\n ---->>> MONTE ROUBADO\n\n");
                vez--; // repete a vez
                sleep(1);

            }else{
                printf("\n\n ---->>> NAO EXISTE CARTA DE MESMO VALOR NO TOPO DOS OUTROS MONTES\n");

                ver_dc = RetiraCarta(lista_jogador, vez, descarte, carta_comprada); // retira uma carta do descarte, caso for igual
                sleep(1);

                if(ver_dc == 1){ // tinha no descarte igual
                    vez--;
                    sleep(1);

                }else{ // nao tinha no descarte uma carta igual a comprada

                    printf("\n\n ---->>> NAO EXISTE CARTA NO DESCARTE COM MESMO VALOR\n\n");
                    ver_ec = empilhaCarta(lista_jogador, vez, carta_comprada); // empilha a carta no meu monte se o topo for igual
                    sleep(1);

                    if(ver_ec == 1){ // a carta e igual a do topo do meu monte
                        printf("\n\n ---->>> CARTA COMPRADA, EMPILHADA EM MEU MONTE\n\n");
                        vez--;
                        sleep(1);

                    }else{
                        descartaCarta(descarte, carta_comprada); // descarta a carta 
                        sleep(1);
                        printf("\n\n ---->>> CARTA DESCARTADA\n\n");

                    }
                }
            }
        }else{

            Jogador *venceu;
            venceu = verificaVencedor(lista_jogador);

            printf("\n\nGanhador: %d\nQuantidade de cartas %d\n",venceu->num_jogador+1, venceu->quant_carta);

            copiaCartasVencedor(venceu);

            sleep(1);

            imprimeCartasVencedor(lista_jogador);

            ordenarJogadoresPorQuantidadeDeCartas(lista_jogador,quant_jog);
            
            sleep(1);

            printf("\n\n\nFIM DE JOGO\n\n");
            break;
        }
        if(vez == quant_jog-1){
            vez = -1;
        }
    }

    deletaMonteBaralho(monte_baralho);
    deletaDescarte(descarte);
    deletaMontePlayer(lista_jogador);

    getchar();

    return 0;
}