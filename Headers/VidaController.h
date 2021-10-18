#ifndef VIDACONTROLLER_H_
#define VIDACONTROLLER_H_

#include "VidaModel.h"
#include "VidaView.h"

void animarJanela(interface *a, int cor, int x, int y, int k, int *opcao);

void controller();

void gerenciarMenu(interface *menuP, int cor, int x, int y, int k, mundo *mundo, interface submenuP[]);

#endif