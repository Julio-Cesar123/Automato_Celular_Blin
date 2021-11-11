#include "Headers/VidaArquivoView.h" 
//desenha erro
void desenharErro(interface *a){

    apagarJanela(a);
    lerFraseArquivoTxT("ASCII_Art/manutencao.txt", 1, a->larg/2 - COL_MANUTENCAO_TXT/2, a, INVERTIDO, 'J', 0.05);
    mostrarJanela(a, PADRAO);
    wattron(a->janela, COLOR_PAIR(INVERTIDO));
    mvwprintw(a->janela,a->comp-2, 2,"PRESSIONE QUALQUER TECLA PARA CONTINUAR");
    wattroff(a->janela, COLOR_PAIR(INVERTIDO));
    wrefresh(a->janela);
    wgetch(a->janela); 

}

void inicializarInterArq(arquivo *arq){
  int comp, larg;
  getmaxyx(stdscr ,comp, larg);
  int largArq;
  
  //Janela para base 
  arq->menu[1].comp = 40;
  arq->menu[1].larg = 102;
  arq->menu[1].largComeca = larg/2 - arq->menu[1].larg/2;
  arq->menu[1].compComeca = comp/2 - arq->menu[1].comp/2; 
  arq->menu[1].janela = newwin(arq->menu[1].comp, arq->menu[1].larg, arq->menu[1].compComeca, arq->menu[1].largComeca);
  
  //Janela para mostrar arquivo txt
  criarSubInter(&(arq->menu[1]), &(arq->menu[2]), 7,arq->menu[1].larg-2 , 1, 1);
  arq->menu[2].janela = newwin(arq->menu[2].comp, arq->menu[2].larg, arq->menu[2].compComeca, arq->menu[2].largComeca);
  
  
  largArq = strlen("|Arquivo|");
    
  arq->menu[0].comp =  6;
  arq->menu[0].larg =  16;
  arq->menu[0].largComeca = larg - largArq - 9;
  arq->menu[0].compComeca = 1;
  arq->menu[0].janela = newwin(arq->menu[0].comp, arq->menu[0].larg, arq->menu[0].compComeca, arq->menu[0].largComeca);
  
  arq->menu[0].nI = 4;
  carregarItem(arq->menu[0].item,
                " CARREGAR ",
                "  SALVAR  ",
                "TRANSFERIR",
                "   SAIR   ",
                     "",
                     arq->menu[0].nI);

  keypad(arq->menu[0].janela, true);
  
  //Janela para mostrar a lista de arquivos tanto salvo ou transferido
  criarSubInter(&(arq->menu[1]), &(arq->submenu[3]), 30, arq->menu[1].larg/5+1, arq->menu[2].comp+2, 1);
  arq->submenu[3].janela = newwin(arq->submenu[3].comp, arq->submenu[3].larg, arq->submenu[3].compComeca, arq->submenu[3].largComeca);
   
  //Janela para entrada de dados de arquivo Binario
  criarSubInter(&(arq->menu[1]), &(arq->submenu[0]), 15, (arq->menu[1].larg*2)/5-1, arq->menu[2].comp+2, arq->submenu[3].larg+1);
  arq->submenu[0].janela = newwin(arq->submenu[0].comp, arq->submenu[0].larg, arq->submenu[0].compComeca, arq->submenu[0].largComeca);
  
    //Janela para entrada de dados de arquivo Txt
  criarSubInter(&(arq->menu[1]), &(arq->submenu[1]), 15, (arq->menu[1].larg*2)/5, arq->menu[2].comp+2, arq->submenu[0].larg+1+arq->submenu[3].larg);
  arq->submenu[1].janela = newwin(arq->submenu[1].comp, arq->submenu[1].larg, arq->submenu[1].compComeca, arq->submenu[1].largComeca);
  
  //Janela para mostrar info de algum tipo de arquivo na janela da lista 
  criarSubInter(&(arq->menu[1]), &(arq->submenu[2]), 15, ((arq->menu[1].larg*2)/5-2)*2+3, arq->menu[2].comp+2+arq->submenu[1].comp, arq->submenu[3].larg+1);
  arq->submenu[2].janela = newwin(arq->submenu[2].comp, arq->submenu[2].larg, arq->submenu[2].compComeca, arq->submenu[2].largComeca);
   
}

void desenharTransferir(arquivo *arq, int *destaqueH, int *destaqueV){

 mostrarJanela(&(arq->menu[1]), INVERTIDO);            
 mostrarJanela(&(arq->menu[2]), PADRAO);
 
 desenharTituloJanela( &(arq->submenu[3]),"LISTA", INVERTIDO);
 lerCaracterArquivoTxT("ASCII_Art/transferir.txt",  arq->menu[2].comp/2 - LIN_TRANSFERIR_TXT/2, arq->menu[2].larg/2 - COL_TRANSFERIR_TXT/2, &(arq->menu[2]), PADRAO, 'J', 0.005);
}

void desenharCarregar(arquivo *arq, int *destaqueH, int *destaqueV){

 mostrarJanela(&(arq->menu[1]), INVERTIDO);            
 mostrarJanela(&(arq->menu[2]), PADRAO);
 
 desenharTituloJanela( &(arq->submenu[3]),"LISTA", INVERTIDO);
 lerCaracterArquivoTxT("ASCII_Art/carregar.txt",  arq->menu[2].comp/2 - LIN_CARREGAR_TXT/2, arq->menu[2].larg/2 - COL_CARREGAR_TXT/2, &(arq->menu[2]), PADRAO, 'J', 0.005);
}

void desenharSalvar(arquivo *arq, int *destaqueH, int *destaqueV){
  
  
 int opSeta= 0; 
 bool sair = false;

 mostrarJanela(&(arq->menu[1]), INVERTIDO);            
 mostrarJanela(&(arq->menu[2]), PADRAO);
 
 desenharTituloJanela( &(arq->submenu[3]),"LISTA", INVERTIDO);
 desenharTituloJanela( &(arq->submenu[0]),"BINARIO", INVERTIDO);
 desenharTituloJanela( &(arq->submenu[1]),"TEXTO", INVERTIDO);
 
 lerCaracterArquivoTxT("ASCII_Art/salvar.txt",  arq->menu[2].comp/2 - LIN_SALVAR_TXT/2, arq->menu[2].larg/2 - COL_SALVAR_TXT/2, &(arq->menu[2]), PADRAO, 'J', 0.005);
 
 mostrarJanela(&(arq->submenu[3]), PADRAO);
 mostrarJanela(&(arq->submenu[0]), PADRAO);
 mostrarJanela(&(arq->submenu[1]), PADRAO);
 mostrarJanela(&(arq->submenu[2]), PADRAO);
 
 while(sair == false){
  
  opSeta = getch();
  sair = moverSeta(destaqueV, destaqueH, 1, 0, 1, 1, &opSeta);
  
  if(*destaqueV == 0){

    for(int i = 0; i < 3; i++){
      
      if(i == *destaqueH){
       mostrarJanela(&(arq->submenu[i]), AZUL_BRANCO); 
      }else{
        mostrarJanela(&(arq->submenu[i]), PADRAO);
      }
    }
  }else if(*destaqueV == 1){
    mostrarJanela(&(arq->submenu[3]), PADRAO);
    mostrarJanela(&(arq->submenu[0]), PADRAO);
    mostrarJanela(&(arq->submenu[1]), PADRAO);
    mostrarJanela(&(arq->submenu[2]), AZUL_BRANCO);

  }else{
    mostrarJanela(&(arq->submenu[3]), PADRAO);
    mostrarJanela(&(arq->submenu[0]), PADRAO);
    mostrarJanela(&(arq->submenu[1]), PADRAO);
    mostrarJanela(&(arq->submenu[2]), PADRAO);
  
  }

 }
}

void desenharPadrao(arquivo *arq){
  
  bool sair = false;
  int l = 0, c = 0;
  int opSeta = 0;
  int  colComeca = 4, linComeca = 12* TERMINAL_COL; 
  individuo celula[100][100];
  limparMatriz(celula, 8);

  desenharTituloJanela(&(arq->submenu[2]),"PADRAO", INVERTIDO);
  desenharEnum(&(arq->submenu[2]), 8, 4, 12*TERMINAL_COL, 0.1, 1);

  mvwaddch(arq->submenu[2].janela, 3,1, ACS_DIAMOND);
  mvwprintw(arq->submenu[2].janela, 3, 3, "Uma vez apertado o botao,");
  mvwprintw(arq->submenu[2].janela, 4, 3, "não há como retorna");
  wrefresh(arq->submenu[2].janela);
   
  while(sair == false){
   
    sair = animarCursor(&l, &c, 8, 4, 12*TERMINAL_COL, 1,&(arq->submenu[2]) , &opSeta);
    definirCelViva(celula, l, c);
    
    wmove(arq->submenu[2].janela, linComeca+l+1, colComeca+c*3+2); 
    wattron(arq->submenu[2].janela, COLOR_PAIR(VERDE_ESCURO));
    wprintw(arq->submenu[2].janela, "%c", celula[l][c].desenho);
    wattroff(arq->submenu[2].janela, COLOR_PAIR(VERDE_ESCURO));
    wrefresh(arq->submenu[2].janela);
    
  }

  arq->lista[arq->qS-1].arq = fopen(arq->lista[arq->qS-1].nomeArq, "w+");

  for(int l = 0; l< 9; l++){
    
    for(int c = 0; c < 9; c++){
      if(l < 8 && c < 8){
        adicionarCaracterTxt(arq->lista[arq->qS-1].arq,  arq->lista[arq->qS-1].nomeArq, celula[l][c].desenho, 0);
      }else if(c == 8){
        adicionarCaracterTxt(arq->lista[arq->qS-1].arq,  arq->lista[arq->qS-1].nomeArq, '\n', 0);
      }
    }

  }
  fclose(arq->lista[arq->qS-1].arq);

  getch(); 
  apagarJanela(&(arq->submenu[2]));

}
// i = 0 Binario e i = 1 Txt
void obterNomeArq(arquivo *arq, int i){

  char nome[100];

  mostrarJanela(&(arq->submenu[i]), PADRAO);
  
  if(i == 0){
    mvwaddch(arq->submenu[i].janela, 3,1, ACS_DIAMOND);
    mvwprintw(arq->submenu[i].janela, 3, 3, "Digite o nome do arquivo");
    mvwaddch(arq->submenu[i].janela, 5,1, ACS_DIAMOND);
    mvwprintw(arq->submenu[i].janela, 5, 3, "Recomendamos que voce coloque um");
    mvwprintw(arq->submenu[i].janela, 6, 3, " nome reconhecivel");
    wattron(arq->submenu[i].janela, COLOR_PAIR(AZUL_BRANCO));
    mvwprintw(arq->submenu[i].janela, 8, 1, "> ");
    wattroff(arq->submenu[i].janela, AZUL_BRANCO);
    wrefresh(arq->submenu[i].janela);
    mvwgetstr(arq->submenu[i].janela, 11, 3, nome);
    
    arq->lista[arq->qS].status = 0;
  
  }else{
    mvwaddch(arq->submenu[i].janela, 3,1, ACS_DIAMOND);
    mvwprintw(arq->submenu[i].janela, 3, 3, "Arquivo para guardar um padrao de");
    mvwprintw(arq->submenu[i].janela, 4, 3, "conjunto de individuos");
    
    mvwaddch(arq->submenu[i].janela, 6,1, ACS_DIAMOND);
    mvwprintw(arq->submenu[i].janela, 6, 3, "Digite o nome do arquivo");
    
    mvwaddch(arq->submenu[i].janela, 8,1, ACS_DIAMOND);
    mvwprintw(arq->submenu[i].janela, 8, 3, "Recomendamos que voce coloque um");
    mvwprintw(arq->submenu[i].janela, 9, 3, " nome reconhecivel");
    
    wattron(arq->submenu[i].janela, COLOR_PAIR(AZUL_BRANCO));
    mvwprintw(arq->submenu[i].janela, 11, 1, "> ");
    wattroff(arq->submenu[i].janela, AZUL_BRANCO);
    wrefresh(arq->submenu[i].janela);
    mvwgetstr(arq->submenu[i].janela, 11, 3, nome);
    
    arq->lista[arq->qS].status = 1;

  }
  if(i == 1){
    strcat(nome, ".txt");
    strcat(arq->lista[arq->qS].nomeArq, nome);
  }else{
    strcat(nome, ".dat");
    strcat(arq->lista[arq->qS].nomeArq, nome);

  }

   arq->qS++;

 


}
//faz  leitura do txt
void lerCaracterArquivoTxT(char *nomeArq, int x, int y, interface *a, int cor, char modo, float vel){


  FILE *arq;
  char c;
  
  if(modo == 'J')
    wattron(a->janela, COLOR_PAIR(cor));
  else
    attron(COLOR_PAIR(cor));
  
  // Abre um arquivo TEXTO para LEITURA

  arq = fopen(nomeArq, "rt");
  if (arq == NULL)  // Se houve erro na abertura
  {
     printw("Problemas na abertura do arquivo\n");
     exit(1);
  }
  
  int i = 0;
  int j = 0;
  while (!feof(arq))
  {
    // Lê cada caracter
  	 c = fgetc(arq);
    if(modo == 'J'){
      mvwprintw(a->janela, x+i, y+j, "%c", c);
      atrasarTela(vel);
      wrefresh(a->janela);
    }else{
      mvprintw(x+i, y+j,"%c", c);
      atrasarTela(vel);
      refresh();
    }
    if(c == '\n'){
      i++;
      j = 0;
    }
    
    j++;
  }
  
  if(modo == 'J'){
    wattroff(a->janela, COLOR_PAIR(cor));
    mostrarJanela(a, cor);
  }
  else
    attroff(COLOR_PAIR(cor));
  
  fclose(arq);

}

//MODO = 'J' (JANELA)
void lerFraseArquivoTxT(char *nomeArq, int x, int y, interface *a, int cor, char modo, float vel){


  FILE *arq;
  char Linha[200];
  
  if(modo == 'J')
    wattron(a->janela, COLOR_PAIR(cor));
  else
    attron(COLOR_PAIR(cor));
  
  // Abre um arquivo TEXTO para LEITURA

  arq = fopen(nomeArq, "rt");
  if (arq == NULL)  // Se houve erro na abertura
  {
     printw("Problemas na abertura do arquivo\n");
     exit(1);
  }
  
  int i = 0;
  while (!feof(arq))
  {
  	// Lê uma linha (inclusive com o '\n')
    fgets(Linha, 100, arq); // o 'fgets' lê até 99 caracteres ou até o '\n'
    if(modo == 'J'){
      mvwprintw(a->janela, x+i, y, "%s", Linha);
      atrasarTela(vel);
      wrefresh(a->janela);
    }else{
      mvprintw(x+i, y, "%s", Linha);
      atrasarTela(vel);
      refresh();
    }
    i++;
  }
  
  if(modo == 'J'){
    wattroff(a->janela, COLOR_PAIR(cor));
    mostrarJanela(a, cor);
  }  
  else
    attroff(COLOR_PAIR(cor));
  
  fclose(arq);

}



