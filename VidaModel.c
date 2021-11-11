#include "Headers/VidaModel.h"

//faz um delay em certas ações
void  delay(float delay1) {

   if (delay1<0.001) return; // pode ser ajustado e/ou evita-se valores negativos.

   float inst1=0, inst2=0;

   inst1 = (float)clock()/(float)CLOCKS_PER_SEC;

   while (inst2-inst1<delay1) inst2 = (float)clock()/(float)CLOCKS_PER_SEC;

   return;

}

//faz uma animação de atraso na tela
void atrasarTela(float tempo){
    
    if(tempo > 0){
      fflush (stdout);
      delay(tempo);
    }
}



//transformas as letras em maiúsculo
void transformarMaius(char *str){

    int i = 0;
  
    while(str[i] != '\0'){
        str[i] = toupper(str[i]);
        i++;
    }
}

//transformas as letras em minusculo
void transformarMinus(char *str){

    int i = 0;
  
    while(str[i] != '\0'){
        str[i] = tolower(str[i]);
        i++;
    }
}
//faz a criaçao das opções do menu principal
void carregarItem(Item a[], char *str1, char *str2, char *str3, char *str4, char *str5, int nA){

    strcpy(a[Q_ITEM-5].str, str1);
    strcpy(a[Q_ITEM-4].str, str2);
    strcpy(a[Q_ITEM-3].str, str3);
    strcpy(a[Q_ITEM-2].str, str4);
    strcpy(a[Q_ITEM-1].str, str5);

    for(int i = 0; i< nA; i++){
      a[i].nS = strlen(a[i].str);
    }
}


//defini o status da célula como morta
void limparMatriz(individuo celula[100][100], int tam){
  
  for(int lin = 0; lin < tam; lin++){
    for(int col = 0; col < tam; col++) {
      celula[lin][col].status = 0;
      celula[lin][col].desenho = ' ';

      
    }
  }
}

//defini o status da celula como morta
void definirCelMorta(individuo celula[100][100], int lin, int col){
  
  celula[lin][col].status = 0; 
  celula[lin][col].desenho = ' ';
}

//define status da celula como viva
void definirCelViva(individuo celula[100][100], int lin, int col){
  celula[lin][col].status = 1;
  celula[lin][col].desenho = 'O';
}


void criarCelula(individuo celula[100][100], int tam, tipoLista *vivo, tipoLista *possivelVivo, tipoLista *mortoFuturo, tipoLista *vivoFuturo){

  int lin, col;
  int contVizinhos = 0;
  

  inicializarLista(vivo);
  inicializarLista(possivelVivo);
  inicializarLista(vivoFuturo);
  inicializarLista(mortoFuturo);
   
  

  definirListaVivo(vivo, celula, tam);

  estimarCelFuturas(vivo, possivelVivo, tam, celula);

  definirGeracao(vivo, vivoFuturo, mortoFuturo,  celula, tam);

  definirGeracao(possivelVivo, vivoFuturo, mortoFuturo,  celula, tam);


   for(int i = 0; i < mortoFuturo->qtdItens; i++){
    
    lin = mortoFuturo->lista[i].linha;
    col = mortoFuturo->lista[i].coluna;

    definirCelMorta(celula, lin, col);
    
  }

  for(int i = 0; i < vivoFuturo->qtdItens; i ++){
    
    lin = vivoFuturo->lista[i].linha;
    col = vivoFuturo->lista[i].coluna;

    definirCelViva(celula, lin, col);
  }

  

}

void definirListaVivo(tipoLista *a, individuo celula[100][100], int tam){
  tipoItem itemAux;

  for (int lin = 0; lin <= tam ; lin++){ 
    
    for (int col = 0; col <= tam ; col++){

      if(celula[lin][col].status == 2 || celula[lin][col].status == 1){
        itemAux.linha = lin;
        itemAux.coluna = col;
        a->lista[a->qtdItens].estado = 1;

        inserirItemLista(a, itemAux);
        
      }
    }
  }
}

void estimarCelFuturas(tipoLista *vivo, tipoLista *possivelVivo,  int tam, individuo celula[100][100]){
  
  int lin, col;
  tipoItem itemAux;
  
  for (int i = 0; i < vivo->qtdItens ; i++){ 
    
      lin = vivo->lista[i].linha;
      col = vivo->lista[i].coluna;
      
      //embaixo
      if((celula[lin+1][col].status == 0 ) && lin != tam - 1){
        
        itemAux.linha = lin+1;
        itemAux.coluna = col;

        inserirItemLista(possivelVivo, itemAux);
        possivelVivo->lista[possivelVivo->qtdItens-1].estado = 1;

      }

      //em cima
      if((celula[lin-1][col].status == 0 ) && lin != 0){

        itemAux.linha = lin-1;
        itemAux.coluna = col;
      
        inserirItemLista(possivelVivo, itemAux);
        possivelVivo->lista[possivelVivo->qtdItens-1].estado = 1;
      }

      //direita
      if((celula[lin][col+1].status == 0) && col != tam - 1){

        itemAux.linha = lin;
        itemAux.coluna = col+1;
        inserirItemLista(possivelVivo, itemAux);
        possivelVivo->lista[possivelVivo->qtdItens-1].estado = 1;
      }

      //esquerda
      if((celula[lin][col-1].status == 0) && col != 0){
        
        itemAux.linha = lin;
        itemAux.coluna = col-1;
        inserirItemLista(possivelVivo, itemAux);
        possivelVivo->lista[possivelVivo->qtdItens-1].estado = 1;
      }

      //embaixo + direita
      if((celula[lin+1][col+1].status == 0) && (lin != tam - 1 && col != tam -1)){

        itemAux.linha = lin+1;
        itemAux.coluna = col+1;
        inserirItemLista(possivelVivo, itemAux);
        possivelVivo->lista[possivelVivo->qtdItens-1].estado = 1;
      }

      //em cima + esquerda
      if((celula[lin-1][col-1].status == 0) && (lin != 0 && col != 0)){
        
        
        itemAux.linha = lin-1;
        itemAux.coluna = col-1;
        inserirItemLista(possivelVivo, itemAux);
        possivelVivo->lista[possivelVivo->qtdItens-1].estado = 1;
      }
      
      //embaixo + esquerda
      if((celula[lin+1][col-1].status == 0) && (lin != tam -1 && col != 0)){
        
        itemAux.linha = lin+1;
        itemAux.coluna = col-1;
        inserirItemLista(possivelVivo, itemAux);
        possivelVivo->lista[possivelVivo->qtdItens-1].estado = 1;
      }

      if((celula[lin-1][col+1].status == 0) && (lin != 0 && col != tam - 1)){

        itemAux.linha = lin-1;
        itemAux.coluna = col+1;
        inserirItemLista(possivelVivo, itemAux);
        possivelVivo->lista[possivelVivo->qtdItens-1].estado = 1;
      }
  }    
}
//compLista == lista para ser objeto de comparação 
void definirGeracao(tipoLista *compLista, tipoLista *vivoFuturo, tipoLista *mortoFuturo,  individuo celula[100][100], int tam){

  int contVizinhos;
  int lin, col;
  
  for (int i = 0; i < compLista->qtdItens ; i++){ 
    
      contVizinhos = 0;

      lin = compLista->lista[i].linha;
      col = compLista->lista[i].coluna;
      
      //embaixo
      if((celula[lin+1][col].status == 2 ) && lin != tam - 1){
        contVizinhos++;
      }

      //em cima
      if((celula[lin-1][col].status == 2 ) && lin != 0){
        contVizinhos++;
      }

      //direita
      if((celula[lin][col+1].status == 2) && col != tam - 1){
        contVizinhos++;
      }

      //esquerda
      if((celula[lin][col-1].status == 2) && col != 0){
        contVizinhos++;
      }

      //embaixo + direita
      if((celula[lin+1][col+1].status == 2) && (lin != tam - 1 && col != tam -1)){
        contVizinhos++;
      }

      //em cima + esquerda
      if((celula[lin-1][col-1].status == 2) && (lin != 0 && col != 0)){
        contVizinhos++;
      }
      
      //embaixo + esquerda
      if((celula[lin+1][col-1].status == 2) && (lin != tam -1 && col != 0)){
        contVizinhos++;
      }

      //em cima + direita
      if((celula[lin-1][col+1].status == 2) && (lin != 0 && col != tam - 1)){
        contVizinhos++;
      }

      definirCelPresentes(vivoFuturo, mortoFuturo, lin, col, contVizinhos);
  }    
}

void definirCelPresentes(tipoLista *vivoFuturo, tipoLista *mortoFuturo, int lin, int col, int contVizinhos){

  tipoItem itemAux;

  if(contVizinhos == 3){
    
    
    itemAux.linha = lin;
    itemAux.coluna = col;
    vivoFuturo->lista[vivoFuturo->qtdItens].estado = 1;
    inserirItemLista(vivoFuturo, itemAux);

  }else if(contVizinhos < 2 || contVizinhos > 3){
    
    itemAux.linha = lin;
    itemAux.coluna = col;
    mortoFuturo->lista[mortoFuturo->qtdItens].estado = 0;
    inserirItemLista(mortoFuturo, itemAux);
    
    
  }
}

