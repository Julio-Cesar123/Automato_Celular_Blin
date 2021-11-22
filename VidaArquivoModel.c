#include "Headers/VidaArquivoModel.h"
#include "Headers/Lista.h"

//Se passar um caracter basta ativar 
void adicionarCaracterTxt(FILE *arq, char *arqNome, char caracter, int modo){
  
  if(modo == 1){   
    arq = fopen(arqNome, "w+");
  }

  if(arq == NULL){
    exit(1);
  }
  
  fputc(caracter, arq);
  
  if(modo == 1){   
    fclose(arq);
  }
}

void salvarArquivo(arquivoInfo *lista, mundo *mundoSalvo, int i){
  
  lista->arq = fopen(lista->nomeArq, "wb");
  
  if(lista->arq == NULL){
     exit(1);
  }
  
  fwrite(mundoSalvo, sizeof(mundo), 1, lista->arq);
  fclose(lista->arq);
}
void carregarArquivo(arquivoInfo *lista, mundo *mundoCarregar, int i){
  
  lista->arq = fopen(lista->nomeArq, "rb");

  if(lista->arq == NULL){
     exit(1);
  }

  fread(mundoCarregar, sizeof(mundo), 1, lista->arq);
  
  fclose(lista->arq);
}



void inicializarArqInfo(arquivoInfo lista[]){

  for(int i = 0; i < 10; i++){

    lista[i].status = -1;
    strcpy(lista[i].nomeArq, "Save/");
  
  }

}
