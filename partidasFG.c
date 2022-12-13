#include "partidasFG.h"

void inserePartidasFG(){
    FILE *partidas = fopen("partidasFG.txt", "ab+");
    PartidaFG *partida = (PartidaFG *) malloc (sizeof(PartidaFG));
    
    int j = 0;
    while(j <= 7){
        scanf(" %c", &partida ->idGrupo);
        int i = 0;
        while(i <= 5){
            scanf("%d %d %d", &partida ->times[0], &partida ->times[1], &partida ->rodada);
            partida ->placar[0] = 0;
            partida ->placar[1] = 0;
            i++;
            fwrite(&partida ->idGrupo, sizeof(char), 1, partidas);
            fwrite(partida ->times, sizeof(int), 2, partidas);
            fwrite(&partida ->rodada, sizeof(int), 1, partidas);
            fwrite(partida ->placar, sizeof(int), 2, partidas);
        }
        j++;
    }
    fclose(partidas);
    free(partida);
}

PartidaFG *lePartida(FILE *partidas){
    PartidaFG *partidaAtual = (PartidaFG*) malloc(sizeof(PartidaFG));

    fread(&partidaAtual ->idGrupo, sizeof(char), 1, partidas);
    fread(&partidaAtual ->times, sizeof(int), 2, partidas);
    fread(&partidaAtual ->rodada, sizeof(int), 1, partidas);
    fread(&partidaAtual ->placar, sizeof(int), 2, partidas);

    return partidaAtual;
}

void escrevePartidaFG(){
    char grupo;
    int rodada;
    int placar[2][2];
    FILE *partidasFG = fopen("partidasFG.txt", "rb+");
    FILE *timestxt = fopen("times.txt", "ab+");
    PartidaFG *partidas[2];
    Time *times[2];

    scanf("%c", &grupo);
    scanf("%d", &rodada);
    seekPartidasFG(grupo, rodada, partidasFG);

    int i = 0;
    while(i <= 1){
        partidas[i] = lePartida(partidasFG);
        times[0] = buscaTime(timestxt, partidas[i] ->times[0]);
        times[1] = buscaTime(timestxt, partidas[i] ->times[1]);
        printf("\nGrupo %c\nRodada %d\n%s x %s\n", partidas[i] ->idGrupo, partidas[i] ->rodada,
        times[0] ->nome, times [1] ->nome);
        scanf("%d %d", &placar[i][0], &placar[i][1]);
        partidas[i] ->placar[0] = placar[i][0];
        partidas[i] ->placar[1] = placar[i][1];
        i++;
    }

    seekPartidasFG(grupo, rodada, partidasFG);
    i = 0;
    while(i <= 1){
        fwrite(&partidas[i] ->idGrupo, sizeof(char), 1, partidasFG);
        fwrite(partidas[i] ->times, sizeof(int), 2, partidasFG);
        fwrite(&partidas[i] ->rodada, sizeof(int), 1, partidasFG);
        fwrite(partidas[i] ->placar, sizeof(int), 2, partidasFG);
        i++;
    }
    fclose(partidasFG);
    fclose(timestxt);

}
    


void seekPartidasFG(char idG, int rodada, FILE *partidas){
    int posicaoGrupo = (idG - 65) * 21 * 6;
    int posicaoRodada = (rodada - 1) * 21 * 2;
    fseek(partidas, posicaoGrupo, SEEK_SET);
    fseek(partidas, posicaoRodada, SEEK_CUR);   
}



void printaPartidasFG(){
    FILE *partidas = fopen("partidasFG.txt", "ab+");
    FILE *times = fopen("times.txt", "ab+");
    PartidaFG *partidaAtual = (PartidaFG*) malloc (sizeof(PartidaFG));
    Time *time1 = (Time *) malloc(sizeof(Time));
    Time *time2 = (Time *) malloc(sizeof(Time));
    int i = 0;
    while(i <= 47){
        fread(&partidaAtual ->idGrupo, sizeof(char), 1, partidas);
        fread(&partidaAtual ->times, sizeof(int), 2, partidas);
        fread(&partidaAtual ->rodada, sizeof(int), 1, partidas);
        fread(&partidaAtual ->placar, sizeof(int), 2, partidas);
        time1 = buscaTime(times, partidaAtual->times[0]);
        time2 = buscaTime(times, partidaAtual->times[1]);
        printf("Grupo %c Rodada %d\t%s %d x %d %s\n", partidaAtual ->idGrupo, partidaAtual ->rodada, 
        time1 ->nome, partidaAtual->placar[0], partidaAtual ->placar[1], time2 ->nome);
        i++;
    }
    fclose(partidas);
    fclose(times);
}