#include<stdio.h>
typedef int bool;
#define true 1
#define false 0

struct Partido {
    int jornada;
    bool locales;
    char rival[32];
    int golesAnotados;
    int golesConcedidos;
    char fase[32];
    bool jugado;
};

void cargarPartidos(struct Partido *partidos, int n);
void mostrarPartidos(struct Partido *partidos, int n);

int main(){
    int numeroDePartidos = 7;
    struct Partido partidos[numeroDePartidos];
    cargarPartidos(partidos, numeroDePartidos);
    mostrarPartidos(partidos, numeroDePartidos);
    
    return 0;
}

void cargarPartidos(struct Partido *partidos, int n) {
    for (int i = 0; i < n; i++) {
        partidos[i].jornada = i + 1;
        partidos[i].locales = true;
        snprintf(partidos[i].rival, sizeof partidos[i].rival, "No definido");
        partidos[i].golesAnotados = 0;
        partidos[i].golesConcedidos = 0;
        snprintf(partidos[i].fase, sizeof partidos[i].fase, "Fase regular");
        partidos[i].jugado = false;
    }
    
    snprintf(partidos[0].rival, sizeof partidos[0].rival, "THE WOLFS");
    partidos[0].golesAnotados = 7;
    partidos[0].golesConcedidos = 6;
    partidos[0].jugado = true;
    
    snprintf(partidos[1].rival, sizeof partidos[1].rival, "PAPIS INGE");
    partidos[1].locales = false;
    partidos[1].golesAnotados = 7;
    partidos[1].golesConcedidos = 11;
    partidos[1].jugado = true;
    
    snprintf(partidos[2].rival, sizeof partidos[2].rival, "THE WOLFS");
    partidos[2].golesAnotados = 7;
    partidos[2].golesConcedidos = 6;
    partidos[2].jugado = true;
}

void mostrarPartidos(struct Partido *partidos, int n) {
    printf("%-8s | %-20s | %-6s | %-20s | %-6s | %-20s | %-6s |\n",
           "Jornada", "Local", "Goles", "Visitante", "Goles", "Fase", "Jugado");
    printf("----------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        const char *local_name;
        const char *visitante_name;
        int goles_local;
        int goles_visitante;

        if (partidos[i].locales) {
            local_name = "Debutadores FC";
            visitante_name = partidos[i].rival;
            goles_local = partidos[i].golesAnotados;
            goles_visitante = partidos[i].golesConcedidos;
        } else {
            local_name = partidos[i].rival;
            visitante_name = "Debutadores FC";
            goles_local = partidos[i].golesConcedidos;
            goles_visitante = partidos[i].golesAnotados;
        }

        printf("%-8d | %-20.20s | %-6d | %-20.20s | %-6d | %-20.20s | %-6s |\n",
               partidos[i].jornada,
               local_name,
               goles_local,
               visitante_name,
               goles_visitante,
               partidos[i].fase,
               partidos[i].jugado ? "Si" : "No");
    }
}