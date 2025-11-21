#include<stdio.h>
typedef int bool;
#define true 1
#define false 0

struct Partido {
    int jornada;
    bool locales;
    int golesAnotados;
    int golesConcedidos;
    char fase[32];
    bool jugado;
};

int main(){
    int numeroDePartidos = 7;
    struct Partido partidos[numeroDePartidos];

    //Eliminar basura 
    for (int i = 0; i < numeroDePartidos; i++) {
        partidos[i].jornada = i + 1;
        partidos[i].locales = true;
        partidos[i].golesAnotados = 0;
        partidos[i].golesConcedidos = 0;
        snprintf(partidos[i].fase, sizeof partidos[i].fase, "Fase regular");
        partidos[i].jugado = false;
    }
    return 0;
}