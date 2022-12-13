#ifndef PARTIDASFG_H
#define PARTIDASFG_H


#include "grupos.h"
#include "times.h"


typedef struct partidasCopaFG{
    char idGrupo;
    int times[2];
    int placar[2];
    int rodada;
} PartidaFG;

void inserePartidasFG();

void printaPartidasFG();

void escrevePartidaFG();

void seekPartidasFG(char grupo, int rodada, FILE *partidas);

PartidaFG *lePartida();





#endif