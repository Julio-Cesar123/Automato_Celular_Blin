#include "Headers/VidaArquivoModel.h"

//modo serve para nao sobreescrever o caracter de uma matriz como parametro por exemplo 
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

void inicializarArqInfo(arquivoInfo lista[]){

  for(int i = 0; i < 10; i++){

    lista[i].status = -1;
    strcpy(lista[i].nomeArq, "Save/");
  
  }


}
