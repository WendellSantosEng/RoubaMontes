#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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


typedef struct Carta{
    int valor;
    int naipe;
}Carta;
typedef struct CartaMontePlayer{
    Carta *carta;
    struct CartaMontePlayer *anterior;
}CartaMontePlayer;

typedef struct MontePlayer{
    CartaMontePlayer *topo;
    int quant;
}MontePlayer;

typedef struct Jogador{
    char nome[30];
    struct Jogador *prox;
    int quant_jogador;
    int quant_carta;
    MontePlayer *monte;
}Jogador;

typedef struct ListaPlayer{
    Jogador *inicio;
}ListaPlayer;


typedef struct CartaMonteBaralho{
    Carta *carta;
    struct CartaMonteBaralho *anterior;
}CartaMonteBaralho;

typedef struct MonteBaralho{
    CartaMonteBaralho *topo;
}MonteBaralho;


typedef struct CartaDescarte{
    Carta *carta;
    struct CartaDescarte *prox;
}CartaDescarte;
typedef struct Descarte{
    CartaDescarte *inicio;
}Descarte;


typedef struct JogadorVencedor{
    Jogador *jogador;
    int vencedor;
    struct JogadorVencedor *prox;
}JogadorVencedor;

typedef struct ListaVencedor{
    JogadorVencedor *inicio;
}ListaVencedor;









// LISTA DE CARTAS
typedef struct ListaCartasdoVencedorELEMENTO{
    Carta *carta;
    struct ListaCartasdoVencedorELEMENTO *prox;
}ListaCartasdoVencedorELEMENTO;
typedef struct ListaCartasdoVencedorLISTA{
    ListaCartasdoVencedorELEMENTO *inicio;
}ListaCartasdoVencedorLISTA;

// JOGADOR(ES) QUE VENCEU(RAM) = ESTRUTURA
typedef struct JogadorVencedorFinal{

    ListaCartasdoVencedorLISTA *cartas_vencedor;
    char nome[30];
    int qual_jog;
    int quant_cartas;

}JogadorVencedorFinal;

// LISTA QUE CONTEM OS JOGADORES QUE VENCERAM
typedef struct ListaFinalJogadoresVencedoresELEMENTO{
    JogadorVencedorFinal *jogador;
    struct ListaFinalJogadoresVencedoresELEMENTO *prox;
}ListaFinalJogadoresVencedoresELEMENTO;

typedef struct ListaJogadoresVencedoresLISTA{
    ListaFinalJogadoresVencedoresELEMENTO *inicio;
}ListaJogadoresVencedoresLISTA;



//DESSA FORMA, TENHO UMA LISTA COM JOGADORES QUE VENCERAM, AS QUAIS TEM UM PONTEIRO QUE APONTA PARA O JOGADOR, E SEU ESTRUTURA
// ESSES JOGADORES , ALEM DE SEUS DADOS TEM UM PONTEIRO PRA CARTAS, A QUAL NESCESSITA SERA SER UMA LISTA DE CARTAS
// PARA FACILITAR A ORDENAÇÃO
// ENTAO O VALOR DA CARTA ESTA EM :
// LISTAVENCEDORELEMENTO = JOGADOR->CARTAS_VENCEDOR->CARTAS->VALOR;
// LISTA = LISTA->ESTRUTURA->LISTA->ESTRUTURA->INT


/*------------------------Pilha monte de compras--------------------*/

MonteBaralho *criaMonteCompra(int quant_jog); //Cria o monte de cartas
void deletaMonteBaralho(MonteBaralho *monte_compra); //Libera a memoria do *MonteBaralho, ao fim do jogo

void embaralha(MonteBaralho *monte_compra); //Algoritimo de embaralhamento de Pilha
Carta *compra(MonteBaralho *monte_compra); //Realiza a "compra" de uma carta, retorna uma *carta

/*------------------------Manipulação dos montes--------------------*/

MontePlayer *criaMontePlayer(); //Cria monte do jogador
void deletaMontePlayer(ListaPlayer *lp);

int empilhaCarta(ListaPlayer *lista_jogador, int vez,Carta *carta_comprada); //Topo do monte igual a carta comprada
int empilhaDescarte(ListaPlayer *lista_jogador, int vez, Carta *carta_comprada, Carta *carta_descarte); // Empilhar no meu monte a carta do descarte e a comprada
int verificaTopoMonte(ListaPlayer *lista_jogador,Carta *carta_comprada,int vez); //Rouba monte do jogador
int roubaMonte(MontePlayer *monte_destino, MontePlayer *monte_saida, Carta *carta_comprada);

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

ListaPlayer *criaListaJogadores();

ListaJogadoresVencedoresLISTA *criaListaCArtasVencedora();

void listaJogadores(ListaPlayer *lista_jogador, int quant_jog);

Jogador *preencheJogador(ListaPlayer *lista_jogador, Jogador *novo,int i);

ListaVencedor *verificaVencedor(ListaPlayer *lista_jogador); // Verifica qual monte tem mais cartas

ListaVencedor *criaListaVencedor();
void copiaCartasVencedor(ListaVencedor *lista_vencedor);
void ordenaCartas(ListaVencedor *lista_vencedor);
void trocarCarta(Carta *a, Carta *b);
void imprimirLista(ListaVencedor *lista);

void trocarJogador(Jogador *a, Jogador *b);
void ordenarListaJogadores(ListaPlayer *lista);
void imprimirRanking(ListaPlayer *lista);

/*------------------------FIM DE JOGO--------------------*/
