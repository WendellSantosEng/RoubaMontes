#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum{
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
};

typedef struct MonteBaralho{
    CartaMonteBaralho *topo;
}MonteBaralho;

typedef struct CartaMonteBaralho{
    Carta *carta;
    struct CartaMonteBaralho *anterior;
    int quant;
}CartaMonteBaralho;


typedef struct MontePlayer1{
    CartaMontePlayer1 *topo;
}MontePlayer1;

typedef struct CartaMontePlayer1{
    Carta *carta;
    struct CartaMontePlayer1 *anterior;
}CartaMontePlayer1;

typedef struct MontePlayer2{
    CartaMontePlayer2 *topo;
}MontePlayer2;

typedef struct CartaMontePlayer2{
    Carta *carta;
    struct CartaMontePlayer2 *anterior;
}CartaMontePlayer2;

typedef struct MontePlayer3{
    CartaMontePlayer3 *topo;
}MontePlayer3;

typedef struct CartaMontePlayer3{
    Carta *carta;
    struct CartaMontePlayer3 *anterior;
}CartaMontePlayer3;

typedef struct MontePlayer4{
    CartaMontePlayer4 *topo;
}MontePlayer4;

typedef struct CartaMontePlayer4{
    Carta *carta;
    struct CartaMontePlayer4 *anterior;
}CartaMontePlayer4;


typedef struct Descarte{
    CartaDescarte *inicio;
}Descarte;

typedef struct CartaDescarte{
    Carta *carta;
    struct CartaDescarte *prox;
    int quant;
}CartaDescarte;


typedef struct Carta{
    int valor;
    int naipe;
}Carta;


typedef struct MonteVencedor{
    CartaMonteVencedor *inicio;
}MonteVencedor;

typedef struct CartaMonteVencedor{
    Carta *carta;
    struct CartaMonteVencedor *prox;
}CartaMonteVencedor;


typedef struct ListaPlayer{
    Jogador *inicio;
}ListaPlayer;

typedef struct Jogador{
    char nome[30];
    struct Jogador *prox;
    int quant_jogador;
    int quant_carta;
}Jogador;

/*------------------------Pilha monte de compras--------------------*/

MonteBaralho *criaMonteCompra(int quant_jog); //Cria o monte de cartas
void deletaMonteBaralho(MonteBaralho *monte_compra); //Libera a memoria do *MonteBaralho, ao fim do jogo

void embaralha(MonteBaralho *monte_compra); //Algoritimo de embaralhamento de Pilha
Carta *compra(MonteBaralho *monte_compra); //Realiza a "compra" de uma carta, retorna uma *carta

/*------------------------Monte do Player 1--------------------*/

// --> ENTRADA

MontePlayer1 *criaMontePlayer1(); //Cria monte do jogador
void deletaMontePlayer1(MontePlayer1 *monte_p1);

void empilhaCartap1(MontePlayer1 *monte_p1, Carta *carta); //Topo do monte igual a carta comprada
void empilhaDescartep1(MontePlayer1 *monte_p1, Carta *carta_comprada, Carta *carta_descarte); // Carta do Descarte, igual a carta comprada
void roubaMontep2_p1(MontePlayer1 *monte_p1, MontePlayer2 *monte_p2, Carta *carta_comprada); //Rouba monte do jogador 2
void roubaMontep3_p1(MontePlayer1 *monte_p1, MontePlayer3 *monte_p3, Carta *carta_comprada); //Rouba monte do jogador 3
void roubaMontep4_p1(MontePlayer1 *monte_p1, MontePlayer4 *monte_p4, Carta *carta_comprada); //Rouba monte do jogador 4

// --> SAIDA

MontePlayer1 *verificaTopop1(MontePlayer1 *monte_p1, Carta *carta); // Caso o retorno for != NULL , o monte esta sendo roubado
void zeraCartasp1(MontePlayer1 *monte_p1); //Apos o roubo do monte, e nescessario n ter mais cartas na Pilha

/*------------------------Monte do Player 2--------------------*/

// --> ENTRADA

MontePlayer2 *criaMontePlayer2(); //Cria monte do jogador
void deletaMontePlayer2(MontePlayer2 *monte_p2);

void empilhaCartap2(MontePlayer2 *monte_p2, Carta *carta); //A jogada foi efetuada com sucesso
void empilhaDescartep2(MontePlayer2 *monte_p2, Carta *carta_comprada, Carta *carta_descarte); // Carta do Descarte, igual a carta comprada
void roubaMontep1_p2(MontePlayer2 *monte_p2, MontePlayer1 *monte_p1, Carta *carta_comprada); //Rouba monte do jogador 1
void roubaMontep3_p2(MontePlayer2 *monte_p2, MontePlayer3 *monte_p3, Carta *carta_comprada); //Rouba monte do jogador 3
void roubaMontep4_p2(MontePlayer2 *monte_p2, MontePlayer4 *monte_p4, Carta *carta_comprada); //Rouba monte do jogador 4

// --> SAIDA

MontePlayer2 *verificaTopop2(MontePlayer2 *monte_p2, Carta *carta); // Caso o retorno for != NULL , o monte esta sendo roubado
void zeraCartasp2(MontePlayer2 *monte_p2); //Apos o roubo do monte, e nescessario n ter mais cartas na Pilha

/*------------------------Monte do Player 3--------------------*/

// --> ENTRADA

MontePlayer3 *criaMontePlayer3(); //Cria monte do jogador
void deletaMontePlayer3(MontePlayer3 *monte_p3);

void empilhaCartap3(MontePlayer3 *monte_p3, Carta *carta); //A jogada foi efetuada com sucesso
void empilhaDescartep3(MontePlayer3 *monte_p3, Carta *carta_comprada, Carta *carta_descarte); // Carta do Descarte, igual a carta comprada
void roubaMontep1_p3(MontePlayer3 *monte_p3, MontePlayer1 *monte_p1, Carta *carta_comprada); //Rouba monte do jogador 1
void roubaMontep2_p3(MontePlayer3 *monte_p3, MontePlayer2 *monte_p2, Carta *carta_comprada); //Rouba monte do jogador 2
void roubaMontep4_p3(MontePlayer3 *monte_p3, MontePlayer4 *monte_p4, Carta *carta_comprada); //Rouba monte do jogador 4

// --> SAIDA

MontePlayer3 *verificaTopop3(MontePlayer3 *monte_p3, Carta *carta); // Caso o retorno for != NULL , o monte esta sendo roubado
void zeraCartasp3(MontePlayer3 *monte_p3); //Apos o roubo do monte, e nescessario n ter mais cartas na Pilha

/*------------------------Monte do Player 4--------------------*/

// --> ENTRADA

MontePlayer4 *criaMontePlayer4(); //Cria monte do jogador
void deletaMontePlayer4(MontePlayer4 *monte_p4);

void empilhaCartap4(MontePlayer4 *monte_p4, Carta *carta); //A jogada foi efetuada com sucesso
void empilhaDescartep4(MontePlayer4 *monte_p4, Carta *carta_comprada, Carta *carta_descarte); // Carta do Descarte, igual a carta comprada
void roubaMontep1_p4(MontePlayer4 *monte_p4, MontePlayer1 *monte_p1, Carta *carta_comprada); //Rouba monte do jogador 1
void roubaMontep2_p4(MontePlayer4 *monte_p4, MontePlayer2 *monte_p2, Carta *carta_comprada); //Rouba monte do jogador 2
void roubaMontep3_p4(MontePlayer4 *monte_p4, MontePlayer3 *monte_p3, Carta *carta_comprada); //Rouba monte do jogador 3

// --> SAIDA

MontePlayer4 *verificaTopop4(MontePlayer4 *monte_p4, Carta *carta); // Caso o retorno for != NULL , o monte esta sendo roubado
void zeraCartasp4(MontePlayer4 *monte_p4); //Apos o roubo do monte, e nescessario n ter mais cartas na Pilha

/*------------------------Area do Descarte--------------------*/

// --> ENTRADA

Descarte *criaDescarte();
void deletaDescarte(Descarte *descarte);

void descartaCarta(Descarte *descarte, Carta *carta);


// --> SAIDA

Carta *RetiraCarta(Descarte *descarte, Carta *carta_comprada); // Verifica o descarte e retorna a carta caso a carta_comprada == carta_descarte


/*---------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------*/


/*------------------------VITORIA--------------------*/ 
MonteVencedor *verificaVencedor(ListaPlayer *player, MontePlayer1 *monte_p1, MontePlayer2 *monte_p2, MontePlayer3 *monte_p3, MontePlayer4 *monte_p4); // Verifica qual monte tem mais cartas

void ordenaCartas(MonteVencedor *monte_vencedor);
void imprimeCartas(MonteVencedor *monte_vencedor);

void ordenaJogadores(ListaPlayer *player);
void imprimeRanking(ListaPlayer *player);

/*------------------------FIM DE JOGO--------------------*/


