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
void agregarPartido(struct Partido *partidos, int index);
void modificarPartido(struct Partido *partidos, int index);
void eliminarPartido(struct Partido *partidos, int index);

int main(){
    int numeroDePartidos = 7;
    struct Partido partidos[numeroDePartidos];
    cargarPartidos(partidos, numeroDePartidos);
    modificarPartido(partidos, 0);
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

void modificarPartido(struct Partido *partidos, int index) {
    printf("Est%cs modificando el siguiente partido:\n", 160);
    printf("%-8s | %-20s | %-6s | %-20s | %-6s | %-20s | %-6s |\n",
           "Jornada", "Local", "Goles", "Visitante", "Goles", "Fase", "Jugado");
    printf("----------------------------------------------------------------------------------------------------\n");

    printf("%cEl partido ya se jug%c? (1-S%c, 0-No): ", 168, 162, 161);
    if (scanf("%d", &partidos[index].jugado) != 1) {
        /* entrada inválida: mantener valor anterior */
    }

    if (!partidos[index].jugado) {
        partidos[index].jugado = false;
        partidos[index].jornada = index + 1;
        partidos[index].locales = true;
        snprintf(partidos[index].rival, sizeof partidos[index].rival, "No definido");
        partidos[index].golesAnotados = 0;
        partidos[index].golesConcedidos = 0;
        snprintf(partidos[index].fase, sizeof partidos[index].fase, "Fase regular");
        printf("El partido se marc%c como no jugado y se inicializaron los campos por defecto.\n", 162);
        return;
    }
    const char *local_name;
    const char *visitante_name;
    int goles_local;
    int goles_visitante;

    if (partidos[index].locales) {
        local_name = "Debutadores FC";
        visitante_name = partidos[index].rival;
        goles_local = partidos[index].golesAnotados;
        goles_visitante = partidos[index].golesConcedidos;
    } else {
        local_name = partidos[index].rival;
        visitante_name = "Debutadores FC";
        goles_local = partidos[index].golesConcedidos;
        goles_visitante = partidos[index].golesAnotados;
    }

    printf("%-8d | %-20.20s | %-6d | %-20.20s | %-6d | %-20.20s | %-6s |\n",
        partidos[index].jornada,
        local_name,
        goles_local,
        visitante_name,
        goles_visitante,
        partidos[index].fase,
        partidos[index].jugado ? "Si" : "No");

    printf("%cJugamos como local? (1-Si, 0-No):", 168);
    scanf("%d", (int*)&partidos[index].locales);
    printf("\n%cContra qui%cn jug%c nuestro equipo?:\n", 168, 130, 160);
    scanf(" %31[^\n]", partidos[index].rival);
    printf("%cCu%cntos goles anot%c nuestro equipo?:", 168, 130, 162);
    scanf("%d", &partidos[index].golesAnotados);
    printf("%cCu%cntos goles concedimos?:", 168, 130);
    scanf("%d", &partidos[index].golesConcedidos);
    int fase_opcion;
    printf("Seleccione la fase del partido:\n1. Fase regular\n2. Fase de grupos\n3. Eliminatorias\n");
    scanf("%d", &fase_opcion);
    switch (fase_opcion) {
        case 1:
            snprintf(partidos[index].fase, sizeof partidos[index].fase, "Fase regular");
            break;
        case 2:
            snprintf(partidos[index].fase, sizeof partidos[index].fase, "Fase de grupos");
            break;
        case 3:
            snprintf(partidos[index].fase, sizeof partidos[index].fase, "Eliminatorias");
            break;
        default:
            printf("Opci%cn no valida. Se mantiene la fase actual.\n", 162);
            break;
    }
}