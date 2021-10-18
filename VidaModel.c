#include "Headers/VidaModel.h"

void inicializarSubInter(interface submenuP[], interface *menuP){

  criarSubInter(menuP, &submenuP[0], menuP->comp-2, menuP->larg/4, 1, 1);
  criarSubInter(menuP, &submenuP[1], menuP->comp-2, menuP->larg - menuP->larg/4-3, 1, menuP->larg/4+2);
  criarSubInter(menuP, &submenuP[2], submenuP[1].comp/6+2, submenuP[1].larg - 4, 2, menuP->larg/4+4);

  submenuP[0].nI = 3;
  
  carregarItem(&submenuP[0],
              "<   comecar   >",
              "<    opcoes   >",
              "<     sair    >",
              " ",
              " "); 
}


void criarSubInter(interface *a, interface *aSub, int  linha, int coluna, int compComeca, int largComeca){

  aSub->comp = linha;
  aSub->larg = coluna;
  aSub->compComeca = compComeca + a->compComeca;
  aSub->largComeca = largComeca + a->largComeca;
  aSub->janela = newwin(aSub->comp, aSub->larg, aSub->compComeca, aSub->largComeca);
}

void  delay(float delay1) {

   if (delay1<0.001) return; // pode ser ajustado e/ou evita-se valores negativos.

   float inst1=0, inst2=0;

   inst1 = (float)clock()/(float)CLOCKS_PER_SEC;

   while (inst2-inst1<delay1) inst2 = (float)clock()/(float)CLOCKS_PER_SEC;

   return;

}

void atrasarTela(float tempo){
    fflush (stdout);
    delay(tempo);
}

void inicializarInter(interface *menuP){
      
    int comp, larg;
    getmaxyx(stdscr ,comp, larg);
    
    menuP->comp = comp/2 + comp/8;
    menuP->larg = larg/2 + larg/8;
    menuP->compComeca = comp/2 - menuP->comp/2;
    menuP->largComeca = larg/2 - menuP->larg/2;
    // fizemos de uma maneira generalizada para ter um padrao em qualquer pc
    menuP->janela = newwin(menuP->comp, menuP->larg, menuP->compComeca, menuP->largComeca); 
    keypad(menuP->janela, true); 


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

void carregarItem(interface *a, char *str1, char *str2, char *str3, char *str4, char *str5){

    strcpy(a->item[Q_ITEM-5].str, str1);
    strcpy(a->item[Q_ITEM-4].str, str2);
    strcpy(a->item[Q_ITEM-3].str, str3);
    strcpy(a->item[Q_ITEM-2].str, str4);
    strcpy(a->item[Q_ITEM-1].str, str5);

    for(int i = 0; i< a->nI; i++){
      a->item[i].nS = strlen(a->item[i].str);
    }
}

void inicializarCor(){
  init_pair(ALERTA, COLOR_RED, COLOR_BLACK);
  init_pair(PADRAO, COLOR_WHITE, COLOR_BLACK);
  init_pair(DESTAQUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(INVERTIDO, COLOR_BLACK, COLOR_WHITE);
  init_pair(BRANCO, COLOR_WHITE, COLOR_WHITE);
  init_pair(VERDE_ESCURO, COLOR_GREEN, COLOR_BLACK);
  init_pair(CIANO, COLOR_CYAN, COLOR_BLACK);

}

//defini o status da célula como morta
void limparMatriz(mundo *mundo){
  
  for(int lin = 0; lin < mundo->tam; lin++){
    for(int col = 0; col < mundo->tam; col++) {
      mundo->celula[lin][col].status = 0;
      mundo->celula[lin][col].desenho = ' ';

      
    }
  }
}

//defini o status da celula como morta
void definirCelMorta(mundo *mundo, int lin, int col){
  
  mundo->celula[lin][col].status = 0;
  mundo->celula[lin][col].desenho = ' ';
}

void definirCelViva(mundo *mundo, int lin, int col){
  mundo->celula[lin][col].status = 1;
  mundo->celula[lin][col].desenho = 'O';
}
bool moverSeta(int *escolhaH, int *escolhaV, int minH, int minV, int maxH, int maxV, int *opcao){
  bool  sair = false;
  int escolhaAux = *escolhaH;
  int escolhaAux2 = *escolhaV;
  

  switch(*opcao){
    case KEY_UP:
      escolhaAux--;
      if(escolhaAux  < minH){
        escolhaAux  = minH-1;
      }
    break;

    case KEY_DOWN:
      escolhaAux++;
        if(escolhaAux  > maxH){
          escolhaAux  = maxH+1 ;
        }
    break;

    case KEY_LEFT:
      escolhaAux2--;
      if(escolhaAux2 < minV){
          escolhaAux2 = minV - 1;
        }
    break;

    case KEY_RIGHT:
      escolhaAux2++;
      if(escolhaAux2  > maxV){
          escolhaAux2  = maxV + 1;
        }
    break;

    case '\n':
      sair = true;
    break;
  }
  
  *escolhaH = escolhaAux;
  *escolhaV = escolhaAux2;
  return sair;
}
