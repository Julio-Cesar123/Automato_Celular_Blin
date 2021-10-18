#ifndef VIDAMODEL_H_
#define VIDAMODEL_H_

#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

#define Q_ITEM 5
#define Q_CARAC 60

#define CONST_TERM 3.5


#define COL_AUTOMATO_CEL_TXT 60
#define LIN_AUTOMATO_CEL_TXT 20
#define COL_BLIN_TXT 66
#define LIN_BLIN_TXT 18
#define COL_MANUTENCAO_TXT 47
#define LIN_MANUTENCAO_TXT 18 
//Definindo paletas de cor
enum Cores {

  TESTE,
  ALERTA, 
  PADRAO, 
  DESTAQUE,  
  INVERTIDO, 
  BRANCO, 
  VERDE_ESCURO,
  CIANO

  };
//struct da celula


typedef struct Item{

  char str[Q_CARAC];
  int nS;

}Item;

typedef struct Interface{
    
  int compComeca, largComeca; //posição na qual eles vao comecar a ser printados
  int comp, larg; //coluna linha
  int destaqueH;//Palvra destacada: highlight
  int destaqueV;
  WINDOW *janela;
  Item item[Q_ITEM];
  int nI;

}interface;

typedef struct animal{
  
  char desenho;
  int status;

}animal;

typedef struct info{

  int quantTotal;
  int quantVivo;
  int quantMorto;
  
  int geracao;

  int tempo;

}info;

typedef struct mundo{

  animal celula[100][100];
  info infoCel;
  int tam;

}mundo;

Item borda; 

void inicializarSubInter(interface submenuP[], interface *menuP);
void criarSubInter(interface *a, interface *aSub, int linha, int coluna, int compComeca, int largComeca);
void inicializarCor();
void transformarMaius(char *str); //model
void transformarMinus(char *str); //model
void atrasarTela(float tempo);//model
void delay(float delay1);//model
void inicializarInter(interface *menuP);//model
void carregarItem(interface *a, char *str1, char *str2, char *str3, char *str4, char *str5); //model
void definirCelMorta(mundo *mundo, int lin, int col);
void definirCelViva(mundo *mundo, int lin, int col);
void limparMatriz(mundo *mundo);
bool  moverSeta(int *escolhaH, int *escolhaV, int minH, int minV, int maxH, int maxV, int *opcao);





#endif