#ifndef VIDAVIEW_H_
#define VIDAVIEW_H_

#include "VidaModel.h"

void desenharMundoEnum(mundo *mundo,  float vel); 
void mostrarJanela(interface *a, int cor);
int obterTam(interface *submenuP);
void desenharTituloJanela(interface *a, char *titulo, int cor);
void desenharBorda();
void lerCaracterArquivoTxT(char *nomeArq, int x, int y, interface *a, int cor, char modo, float vel);
void lerFraseArquivoTxT(char *nomeArq, int x, int y, interface *a,int cor, char modo, float vel);
void destacarItem(interface *a, int cor, int x, int y, int k);
void desenharErro(interface *a);
int adicionarCelula(int cor, mundo *mundo);
void desenharMundo(mundo *mundo, int cor, int corJan, float vel);
void desenharCel(mundo *mundo, float vel, int cor);
void destacarBorda(int destaqueH, int destaqueV);

#endif