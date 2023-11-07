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
    int quant;
}MonteBaralho;

typedef struct CartaMonteBaralho{
    Carta *carta;
    struct CartaMonteBaralho *anterior;
}CartaMonteBaralho;


typedef struct MontePlayer{
    CartaMontePlayer *topo;
    int quant;
}MontePlayer;

typedef struct CartaMontePlayer{
    Carta *carta;
    struct CartaMontePlayer *anterior;
}CartaMontePlayer;

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


typedef struct ListaVencedor{
    CartaListaVencedor *inicio;
}ListaVencedor;

typedef struct CartaListaVencedor{
    Carta *carta;
    struct CartaListaVencedor *prox;
}CartaListaVencedor;


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

/*------------------------Manipulação dos montes--------------------*/

MontePlayer *criaMontePlayer(); //Cria monte do jogador
void deletaMontePlayerConteudo(MontePlayer *monte);
void deletaMontePlayerStruct(MontePlayer *monte);

int empilhaCarta(MontePlayer *monte, Carta *carta); //Topo do monte igual a carta comprada
int empilhaDescarte(MontePlayer *monte, Carta *carta_comprada, Carta *carta_descarte); // Empilhar no meu monte a carta do descarte e a comprada
int verificaTopoMonte(MontePlayer *monte_p1, MontePlayer *monte_p2, MontePlayer *monte_p3, MontePlayer *monte_p4, Carta *carta_comprada, int vez); //Rouba monte do jogador
void roubaMonte(MontePlayer *monte_destino, MontePlayer *monte_saida, Carta *carta_comprada);

/*------------------------Area do Descarte--------------------*/

// --> ENTRADA

Descarte *criaDescarte();
void deletaDescarte(Descarte *descarte);

void descartaCarta(Descarte *descarte, Carta *carta); // Descarte recebe uma carta

// --> SAIDA

Carta *RetiraCarta(Descarte *descarte, Carta *carta_comprada); // Verifica o descarte e retorna a carta caso a carta_comprada == carta_descarte


/*---------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------*/


/*------------------------VITORIA--------------------*/ 
ListaPlayer *verificaVencedor(ListaPlayer *player, MontePlayer *monte_p1, MontePlayer *monte_p2, MontePlayer *monte_p3, MontePlayer *monte_p4); // Verifica qual monte tem mais cartas

ListaVencedor *criaListaVencedor();
void copiaCartasVencedor(ListaVencedor *lista_vencedor, MontePlayer *monte_vencedor);
void ordenaCartas(ListaVencedor *lista_vencedor);
void trocarCarta(Carta *a, Carta *b);
void imprimirLista(ListaVencedor *lista);

void trocarJogador(Jogador *a, Jogador *b);
void ordenarListaJogadores(ListaPlayer *lista);
void imprimirRanking(ListaPlayer *lista);

/*------------------------FIM DE JOGO--------------------*/


