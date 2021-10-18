#include "Headers/VidaView.h"

//forma a matriz 
void desenharMundoEnum(mundo *mundo,  float vel){

    int c, l, col, linha; 
    
    getmaxyx(stdscr, linha ,col);
    linha = linha/2 - mundo->tam/2;
    col = col/2 - mundo->tam/2 * CONST_TERM;

    mvhline( linha, col-1, ACS_HLINE, mundo->tam*3+1);
    mvvline(linha, col, ACS_VLINE, mundo->tam+1);
    
    move(linha-1, col);    
    for(c = 1; c <= mundo->tam; c++) { 
      if(c<10){ 
        printw("  %d", c);
        atrasarTela(vel);
        refresh();  
      }else{      
        printw(" %d", c);
        atrasarTela(vel);
        refresh();
      }
    }
    printw("\n ");

    
    for(l = 1 ; l<= mundo->tam; l++) {
        
      if(l < 10){
        move(l+linha, col-2);
        printw(" %d", l);
        atrasarTela(vel);
        refresh();

      }
        else{
        move(l+linha, col-2);
        printw("%d", l);
        atrasarTela(vel);
        refresh();
          
        }
    }

}

void mostrarJanela(interface *a, int cor){ 

    wbkgd(a->janela, COLOR_PAIR(cor));
    box(a->janela, 0, 0);
    refresh();
    wrefresh(a->janela);
}

//pergunta o tamanho da matriz
int obterTam(interface *submenuP){

    int tam;
    int colMax, linMax;
    getmaxyx(stdscr, linMax, colMax);
    
    mostrarJanela(submenuP, PADRAO); 
    desenharTituloJanela(submenuP, "TAMANHO ", INVERTIDO);
    wattron(submenuP->janela, COLOR_PAIR(INVERTIDO));
    mvwprintw(submenuP->janela, 3, 4 , "Digite o tamanho do seu mundo (min -> 2; max -> %d): ", colMax/4);
    wattroff(submenuP->janela, COLOR_PAIR(INVERTIDO));
    wrefresh(submenuP->janela);
    wscanw(submenuP->janela, "%d", &tam);

    while(tam >100 || tam < 2){
      beep();

      wclear(submenuP->janela);
      mostrarJanela(submenuP, PADRAO);
      desenharTituloJanela(submenuP, "ERRO", ALERTA);
      atrasarTela(0.2); 
      wattron(submenuP->janela, COLOR_PAIR(ALERTA));
      mvwprintw(submenuP->janela, 3, 1 , "Opps!! Voce deve ter digitado algo errado");
      atrasarTela(0.2);
      wrefresh(submenuP->janela);
      mvwprintw(submenuP->janela, 4, 1 , "Digite o tamanho do seu mundo (min -> 2; max -> %d): ", colMax/4);
      atrasarTela(0.2);
      wrefresh(submenuP->janela);
      wattroff(submenuP->janela, COLOR_PAIR(ALERTA));
      wrefresh(submenuP->janela);
      wscanw(submenuP->janela, "%d", &tam);
      
    }
    
    wclear(submenuP->janela);
    wrefresh(submenuP->janela);

  
    return tam;
}

void desenharTituloJanela(interface *a, char *titulo, int cor){

  int tituloLargura = strlen(titulo);
 

  mvwaddch(a->janela, 2, 0, ACS_LTEE); 
  mvwhline(a->janela, 2, 1, ACS_HLINE, a->larg - 2);
  mvwaddch(a->janela, 2, a->larg - 1, ACS_RTEE); 
  

  wattron(a->janela, COLOR_PAIR(cor));
  mvwprintw(a->janela, 1, a->larg/2 - tituloLargura/2, "%s", titulo);
  wattroff(a->janela, COLOR_PAIR(cor));
  
  wrefresh(a->janela);
}

void desenharBorda(){
  
    int comp, larg;
    getmaxyx(stdscr ,comp, larg);
    int largArq;

    largArq = strlen("|Arquivo|");
    //desenhar bordas
    mvhline( 0, 0, ACS_HLINE, larg);
    mvprintw(0, larg-largArq-2, "|Arquivo|");
    mvprintw(0, larg-largArq*2, "|Info|");
    attron(COLOR_PAIR(CIANO));
    mvaddch(comp-3, 11, ACS_UARROW);
    mvprintw(comp-2, 2, "Utilize  |  |  para locomover");
    mvaddch(comp-1, 14, ACS_DARROW);
    attroff(COLOR_PAIR(CIANO));
    refresh();
}

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

void destacarBorda(int destaqueH, int destaqueV){
  int larg, largArq, comp;
  
  getmaxyx(stdscr, comp, larg);
  largArq = strlen("|Arquivo|");

  if(destaqueH == -1 && destaqueV == 0){
    attron(COLOR_PAIR(INVERTIDO));    
    mvprintw(0, larg-largArq-2, "|Arquivo|");
    attroff(COLOR_PAIR(INVERTIDO));     
    mvprintw(0, larg-largArq*2, "|Info|");
    refresh();
  }else if(destaqueH == -1 && destaqueV == -1){
    
    attron(COLOR_PAIR(INVERTIDO));    
    mvprintw(0, larg-largArq*2, "|Info|");
    attroff(COLOR_PAIR(INVERTIDO));
    mvprintw(0, larg-largArq-2, "|Arquivo|");
    refresh();
  }else{
    desenharBorda();
  }
}
//destaca a opção selecionada
void destacarItem(interface *a, int cor, int x, int y, int k){
    
    for(int i = 0; i < a->nI; i++){
      
      if(i == a->destaqueH ){
        transformarMaius(a->item[i].str);
        wattron(a->janela, COLOR_PAIR(cor));
        
        mvwprintw(a->janela, i*x+k, y, "-> %s", a->item[i].str);
        wattroff(a->janela, COLOR_PAIR(cor));
        transformarMinus(a->item[i].str);
        
      }else{
        mvwprintw(a->janela, i*x+k, y, "%s    ", a->item[i].str);
      }
    }
}

//desenha erro
void desenharErro(interface *a){

    wclear(a->janela); 
    lerFraseArquivoTxT("ASCII_Art/manutencao.txt", 1, a->larg/2 - COL_MANUTENCAO_TXT/2, a, INVERTIDO, 'J', 0.05);
    mostrarJanela(a, PADRAO);
    wattron(a->janela, COLOR_PAIR(INVERTIDO));
    mvwprintw(a->janela,a->comp-2, 2,"PRESSIONE QUALQUER TECLA PARA CONTINUAR");
    wattroff(a->janela, COLOR_PAIR(INVERTIDO));
    wrefresh(a->janela);
    wgetch(a->janela); 

}

//função para escolher
int escolherModo(){
  int op;
  
  interface modo;
  modo.comp = 8;
  modo.larg = 40;
  modo.compComeca = 0;
  modo.largComeca = 0;
  modo.janela = newwin(modo.comp, modo.larg, modo.compComeca, modo.largComeca);
  mostrarJanela(&modo, PADRAO);

  mvwprintw(modo.janela, 1, 2, "1 - Colocar as celulas automaticamente");
  mvwprintw(modo.janela, 2, 2 ,"(maneira aleatoria)");
  mvwprintw(modo.janela, 3, 2, "2 - Colocar as celulas manualmente");
  mvwprintw(modo.janela, 4, 2, "0 - Para sair");
  mvwprintw(modo.janela, 6, 2, "Opcao:   ");
  wrefresh(modo.janela);
  mvwscanw(modo.janela, 6, 9,"%d", &op);

  return op;
}

//adiciona celulas de um modo manual ou aleatório
int adicionarCelula(int cor, mundo *mundo){
  
  int op;
  int larg, comp;
  op = escolherModo();
  int lin, col;
  int quant;
  interface modo;
  
  getmaxyx(stdscr, comp, larg);

  modo.larg = 80;
  modo.comp = 8;
  modo.largComeca = larg/2 - 40;
  modo.compComeca = comp/2 - 4;
  modo.janela = newwin(modo.comp, modo.larg, modo.compComeca, modo.largComeca);
  
  mostrarJanela(&modo, PADRAO); //SDDS SUPERMAN
  desenharTituloJanela(&modo, "Celula", cor);
  
  if(op == 1){ //modo Aleatório
    wattron(modo.janela, COLOR_PAIR(cor));  
    mvwprintw(modo.janela, 3, 1,"Quantas celulas voce deseja colocar? (da para colocar %d celulas)", mundo->tam * mundo->tam);
    wrefresh(modo.janela);
    mvwscanw(modo.janela, 3, 69,"%d", &quant);
    wattron(modo.janela, COLOR_PAIR(cor));  
    
    srand(time(NULL));
    
    for(int i = 0; i < quant; i++){
      lin = rand() % mundo->tam;
      col = rand() % mundo->tam;
      definirCelViva(mundo, lin, col); 
      
    }

  }else if(op == 2){ //modo Manual
  
    wattron(modo.janela, COLOR_PAIR(cor));
    mvwprintw(modo.janela, 3, 2,"No modo manual, cada celula sera adicionada individualmente"); 
    mvwprintw(modo.janela, 4, 2,"Em qual linha voce gostaria de colocar suas celulas:     ");
    mvwprintw(modo.janela, 5, 2,"Em qual coluna voce gostaria de colocar suas celulas:    ");
    wrefresh(modo.janela);
    mvwscanw(modo.janela, 4, 55, "%d", &lin);
    mvwscanw(modo.janela, 5, 56, "%d", &col);
    wattroff(modo.janela,COLOR_PAIR(cor));
    
    lin--;
    col--;
    definirCelViva(mundo, lin, col); 
  }

  clear();
  wclear(modo.janela);
  refresh();
  wrefresh(modo.janela);
  
  return op;
}

void desenharMundo(mundo *mundo, int cor, int corJan, float vel){ //
  
  int opcao;
  
  opcao = adicionarCelula(corJan , mundo);
  
  while(opcao != 0){ 
    desenharMundoEnum(mundo, 0.001);
    refresh();
    desenharCel(mundo, vel, cor);
    opcao = adicionarCelula(corJan , mundo);
  } 

}


void desenharCel(mundo *mundo, float vel, int cor){
  
  int  coluna, linha; 
  
  getmaxyx(stdscr, linha ,coluna);
  linha = linha/2 - mundo->tam/2;
  coluna = coluna/2 - mundo->tam/2 * CONST_TERM;


  // i = linha; j = coluna;
  for(int i = 0; i < mundo->tam; i++){
    
    for(int j = 0; j < mundo->tam; j++){  
      move(linha+i+1, coluna+j*3+2); 
      
      if(mundo->celula[i][j].status == 1){
        attron(COLOR_PAIR(cor));
        printw("%c", mundo->celula[i][j].desenho);
        atrasarTela(vel);
        attroff(COLOR_PAIR(cor));
        refresh();
      
      }
    } 
  }
}
