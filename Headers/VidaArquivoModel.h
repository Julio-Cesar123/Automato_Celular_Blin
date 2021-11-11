#ifndef VIDAARQUIVOMODEL_H_
#define VIDAARQUIVOMODEL_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>

typedef struct arquivoInfo{
  
  FILE *arq;
  char status;
  char nomeArq[100];

}arquivoInfo;


void adicionarCaracterTxt(FILE *arq, char *arqNome, char caracter, int modo);
void inicializarArqInfo(arquivoInfo lista[]);
#endif


