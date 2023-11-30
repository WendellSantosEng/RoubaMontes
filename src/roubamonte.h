#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

/*enum{
    AS = 1,
    DOIS = 2,
    TRES = 3,
    QUATRO = 4,
    CINCO = 5,
    SEIS = 6,
    SETE = 7,
    OITO = 8,
    NOVE = 9,
    DEZ = 10,
    DAMA = 11,
    VALETE = 12,
    REI = 13,
};*/

typedef struct Carta{ //  ESTRUTURA DA CARTA
    int valor;
    int naipe;
}Carta;
typedef struct CartaMontePlayer{ // ELEMENTO DA PILHA DO MONTE DO JOGADOR
    Carta *carta;
    struct CartaMontePlayer *anterior;
    struct CartaMontePlayer *prox;
}CartaMontePlayer;

typedef struct MontePlayer{ // PILHA DO MONTE DO JOGADOR
    CartaMontePlayer *topo;
    int quant;
}MontePlayer;

typedef struct ListaBaralhoVencedor{ // LISTA DO MONTE DO JOGADOR -> UTILIZADA CASO O JOG SEJA UM VENCEDOR
    CartaMontePlayer *inicio;
}ListaBaralhoVencedor;


typedef struct Jogador{ // ELEMENTO JOGADOR DA LISTA DE JOGADORES
    char nome[30];
    struct Jogador *prox;
    int num_jogador;
    int quant_carta;
    int venceu;
    MontePlayer *monte;
    ListaBaralhoVencedor *lista;
}Jogador;

typedef struct ListaPlayer{ // LISTA DA LISTA DE JOGADORES
    Jogador *inicio;
}ListaPlayer;


typedef struct CartaMonteBaralho{ // STRUCT ELEMENTO DO MONTE DE COMPRA
    Carta *carta;
    struct CartaMonteBaralho *anterior;
}CartaMonteBaralho;

typedef struct MonteBaralho{
    int quantidade_baralho;
    CartaMonteBaralho *topo; // PILHA DO MONTE DE COMPRA
}MonteBaralho;

typedef struct CartaDescarte{ // ELEMENTO DA CARTA DO DESCARTE
    Carta *carta;
    struct CartaDescarte *prox;
}CartaDescarte;
typedef struct Descarte{ // LISTA DO DESCARTE
    CartaDescarte *inicio;
}Descarte;



/*------------------------Pilha monte de compras--------------------*/

MonteBaralho *criaMonteCompra(int quant_jog); //Cria o monte de cartas
void deletaMonteBaralho(MonteBaralho *monte_compra); //Libera a memoria do *MonteBaralho, ao fim do jogo
void deletaMonte(MontePlayer *monte); // deleta um so monte

void embaralha(MonteBaralho *monte_compra); //Algoritimo de embaralhamento de Pilha
Carta *compra(MonteBaralho *monte_compra); //Realiza a "compra" de uma carta, retorna uma *carta
void imprimircarta(Carta *carta);

/*------------------------Manipulação dos montes--------------------*/

MontePlayer *criaMontePlayer(); //Cria monte do jogador
void deletaMontePlayer(ListaPlayer *lp);

int empilhaCarta(ListaPlayer *lista_jogador, int vez,Carta *carta_comprada); //Topo do monte igual a carta comprada
int empilhaDescarte(ListaPlayer *lista_jogador, int vez, Carta *carta_comprada, Carta *carta_descarte); // Empilhar no meu monte a carta do descarte e a comprada
int verificaTopoMonte(ListaPlayer *lista_jogador,Carta *carta_comprada,int vez); //Rouba monte do jogador
int verificaCartaTopo(Jogador *atual,Carta *carta_comprada); // verifica igualdade entre carta comprada e o topo do monte do jogador que e repassado como parametro
MontePlayer *roubaMonte(MontePlayer *monte_destino, MontePlayer *monte_saida, Carta *carta_comprada, int *quant_roubo);

/*------------------------Area do Descarte--------------------*/

// --> ENTRADA

Descarte *criaDescarte();
void deletaDescarte(Descarte *descarte);

void descartaCarta(Descarte *descarte, Carta *carta); // Descarte recebe uma carta

void imprimeDescarte(Descarte *descarte);

// --> SAIDA

int RetiraCarta(ListaPlayer *lista_jogador, int vez, Descarte *descarte, Carta *carta_comprada); // Verifica o descarte e retorna a carta caso a carta_comprada == carta_descarte

/*---------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------*/

/*------------------------VITORIA--------------------*/

ListaPlayer *criaListaJogadores();

void listaJogadores(ListaPlayer *lista_jogador, int quant_jog);

Jogador *preencheJogador(Jogador *novo,int i);

Jogador *verificaVencedor(ListaPlayer *lista_jogador); // Verifica qual monte tem mais cartas

ListaBaralhoVencedor *criaBaralhoVencedor();

void copiaCartasVencedor(Jogador *vencedor);

void selectionSortCartas(ListaPlayer *lista_jogadores);

void imprimeCartasVencedor(ListaPlayer *lista_jogador);

void ordenarJogadoresPorQuantidadeDeCartas(ListaPlayer *lista_jogadores);

void imprimirRanking(ListaPlayer *lista);

/*------------------------FIM DE JOGO--------------------*/
