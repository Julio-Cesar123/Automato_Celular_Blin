#ifndef VIDAARQUIVOMODEL_H_
#define VIDAARQUIVOMODEL_H_

#include "VidaView.h"

typedef struct arquivoInfo{
  
  FILE *arq;
  char status;
  char nomeArq[100];

}arquivoInfo;


void salvarArquivo(arquivoInfo *lista, mundo *mundoSalvar, int i);
void carregarArquivo(arquivoInfo *lista, mundo *mundoCarregar, int i);
void adicionarCaracterTxt(FILE *arq, char *arqNome, char caracter, int modo);
void inicializarArqInfo(arquivoInfo lista[]);
#endif


