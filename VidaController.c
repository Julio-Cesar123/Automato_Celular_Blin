#include "Headers/VidaController.h"

void animarJanela(interface *a, int cor, int x, int y, int k, int *opcao){

    bool sair = false;
    a->destaqueH = 0;
    a->destaqueV = 0;

    while(sair == false){

        destacarItem(a , cor, x, y, k);
        destacarBorda(a->destaqueH, a->destaqueV);        
        *opcao = wgetch(a->janela);
        sair = moverSeta(&(a->destaqueH), &(a->destaqueV), 0, 0, a->nI-1, 1, opcao);
   }
}


void controller(){
    
    initscr();
    start_color();
    keypad(stdscr, true);

    inicializarCor();
    
    interface menuP;
    interface submenuP[3];
    mundo mundo;

    inicializarInter(&menuP);
    inicializarSubInter(submenuP, &menuP);
    keypad(submenuP[0].janela, true);

    int comp, larg;
    getmaxyx(stdscr,comp, larg);

        
    lerCaracterArquivoTxT("ASCII_Art/automato_celular.txt", comp/2 - LIN_AUTOMATO_CEL_TXT, larg/2 - COL_AUTOMATO_CEL_TXT/2, NULL, PADRAO, 'N', 0.003);
    getch();
    clear();
    

    desenharBorda();                                                      
    mostrarJanela(&menuP, BRANCO);

    mostrarJanela(&submenuP[0], PADRAO);
    mostrarJanela(&submenuP[1], PADRAO);  
    
    gerenciarMenu(&menuP,  DESTAQUE, 4,  submenuP[0].larg/2-submenuP[0].item[0].nS/2, 8, &mundo, submenuP);

    endwin();
}

void gerenciarMenu(interface *menuP, int cor, int x, int y, int k, mundo *mundo, interface submenuP[]){

  bool sair = false;
  int opcao;
  int larg;
  int comp;
  getmaxyx(stdscr, comp, larg);

  while(sair == false){
  
    wclear(submenuP[1].janela); 
    mostrarJanela(&submenuP[1], PADRAO);   
    lerFraseArquivoTxT("ASCII_Art/blin.txt", submenuP[1].comp/2 - LIN_BLIN_TXT/2 , submenuP[1].larg/2 - COL_BLIN_TXT/2, &submenuP[1], PADRAO, 'J', 0.03);
    
    desenharTituloJanela(&submenuP[0], "MENU", INVERTIDO);
    mostrarJanela(&submenuP[0], PADRAO);
    animarJanela(&submenuP[0], cor, x, y, k, &opcao);
    

    if((submenuP[0].destaqueH == -1 || submenuP[0].destaqueH == submenuP[0].nI) && opcao == '\n'){
     desenharErro(&submenuP[1]); 
    }
    
    switch(submenuP[0].destaqueH){
     
      case 0:
        mundo->tam = obterTam(&submenuP[2]);
        limparMatriz(mundo);
        clear();
        desenharMundoEnum(mundo, 0.05);
        desenharMundo(mundo, VERDE_ESCURO, PADRAO, 0.02);

        clear();
        mostrarJanela(menuP, BRANCO);
      break;

      case 1:
        desenharErro(&submenuP[1]); 
      break;

      case 2:
        sair = true;
      break;
    }

  }

}