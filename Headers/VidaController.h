#ifndef VIDACONTROLLER_H_
#define VIDACONTROLLER_H_

#include "VidaModel.h"
#include "VidaView.h"
#include "VidaArquivoView.h"

void animarJanela(interface *a, int cor, int x, int y, int k, int *opcao, int modoSeta);

void controller();

void gerenciarMenu(interface *menuP, int cor, int x, int y, int k, mundo *mundo, interface submenuP[], arquivo *arq);

void gerenciarMundo(mundo *mundo, int cor, int corJan, float vel);

char adicionarCelula(int cor, mundo *mundo);

void gerenciarMenuArquivo(arquivo *arq);

void gerenciarMenuOpcao(interface *submenu, mundo *mundo);

#endif
