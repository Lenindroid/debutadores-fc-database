 #include<stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_PARTIDOS 128

bool partidosCargados = false;
int numeroDePartidos = 7;

struct Partido {
    int jornada;
    bool locales;
    char rival[32];
    int golesAnotados;
    int golesConcedidos;
    char fase[32];
    bool jugado;
};
struct Partido partidos[MAX_PARTIDOS];

void cargarPartidos(struct Partido *partidos, int n);
void mostrarPartidos(struct Partido *partidos, int inicio, int n);
void agregarPartido(struct Partido *partidos, int index);
void modificarPartido(struct Partido *partidos, int index);
void eliminarPartido(struct Partido *partidos, int *index, int el);

int main(){
    if (!partidosCargados) {
        cargarPartidos(partidos, numeroDePartidos);
        partidosCargados = true;
    }
    
    printf("--Gestion de partidos de Debutadores FC--\n");
    printf("%cQu%c desea hacer?\n", 168, 130);
    printf("1. Mostrar partidos\n2. Modificar partido\n3. Reiniciar base de datos de partidos\n4. A%cadir partido\n5. Eliminar partido\n6. Salir\n", 164);
    int opcion;
    scanf("%d", &opcion);
    switch (opcion) {
        case 1:
            mostrarPartidos(partidos, 0, numeroDePartidos);
            break;
        case 2:
            printf("Estos son los partidos actuales:\n");
            mostrarPartidos(partidos, 0, numeroDePartidos);
            int indexModificado;
            printf("Ingrese el ID del partido a modificar:");
            scanf("%d", &indexModificado);
            if (indexModificado < 1 || indexModificado > numeroDePartidos) {
                printf("N%cmero de partido no v%clido.\n", 163, 160);
                return 1;
            }
            modificarPartido(partidos, indexModificado - 1);
            printf("Partido modificado correctamente.\n");
            break;
        case 3:
            cargarPartidos(partidos, numeroDePartidos);
            printf("Base de datos de partidos reiniciada correctamente.\n");
            break;
        case 4:
            agregarPartido(partidos, numeroDePartidos);
            numeroDePartidos++;
            printf("Partido a%cadido correctamente.\n", 164);
            break;
            
        case 5:
            printf("Estos son los partidos actuales:\n");
            mostrarPartidos(partidos, 0, numeroDePartidos);
            int indexEliminado;
            printf("Ingrese el ID del partido a eliminar:");
            scanf("%d", &indexEliminado);
            if (indexEliminado < 1 || indexEliminado > numeroDePartidos) {
                printf("N%cmero de partido no v%clido.\n", 163, 160);
                return 1;
            }
            eliminarPartido(partidos, &numeroDePartidos, indexEliminado - 1);
            break;
        case 6:
            break;
        default:
            printf("Opci%cn no v%clida.\n", 162, 160);
            return 1;
    }
    
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

void mostrarPartidos(struct Partido *partidos,int inicio, int n) {
    printf("%-8s | %-8s | %-20s | %-6s | %-20s | %-6s | %-20s | %-6s |\n",
           "ID","Jornada", "Local", "Goles", "Visitante", "Goles", "Fase", "Jugado");
    printf("----------------------------------------------------------------------------------------------------\n");
    for (int i = inicio; i < n; i++) {
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

        printf("%-8d | %-8d | %-20.20s | %-6d | %-20.20s | %-6d | %-20.20s | %-6s |\n",
               i + 1,
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
    mostrarPartidos(partidos, index, index + 1);
    printf("----------------------------------------------------------------------------------------------------\n");
    int jugado_flag;
    printf("%cEl partido ya se jug%c? (1-S%c, 0-No): ", 168, 162, 161);
    scanf("%d", &jugado_flag);
    if (jugado_flag == 0) 
        partidos[index].jugado = false;
    else
        partidos[index].jugado = true;

    if (!partidos[index].jugado) {
        partidos[index].jugado = false;
        partidos[index].jornada = index + 1;
        partidos[index].locales = true;
        snprintf(partidos[index].rival, sizeof partidos[index].rival, "No definido");
        partidos[index].golesAnotados = 0;
        partidos[index].golesConcedidos = 0;
        snprintf(partidos[index].fase, sizeof partidos[index].fase, "Fase regular");
        printf("El partido se marc%c como no jugado y se inicializaron los campos por defecto.\n", 162);
        mostrarPartidos(partidos, index, index + 1);
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

    int locales_opcion;
    printf("%cJugamos como local? (1-Si, 0-No): ", 168);
    scanf("%d", &locales_opcion);
    if (locales_opcion == 0) 
        partidos[index].locales = false;
    else
        partidos[index].locales = true;

    
    printf("Introduzca la jornada (n%cmero) del partido: ", 163);
    scanf("%d", &partidos[index].jornada);
    printf("\n%cContra qui%cn jug%c nuestro equipo?:\n", 168, 130, 160);
    scanf(" %31[^\n]", partidos[index].rival);
    printf("%cCu%cntos goles anot%c nuestro equipo?:", 168, 130, 162);
    scanf("%d", &partidos[index].golesAnotados);
    printf("%cCu%cntos goles concedimos?:", 168, 130);
    scanf("%d", &partidos[index].golesConcedidos);
    printf("Escriba que fase se jug%c:\n", 162);
    scanf(" %31[^\n]", partidos[index].fase);

    mostrarPartidos(partidos, index, index + 1);
}

void eliminarPartido(struct Partido *partidos, int *index, int el){
    for(int i=el; i<(*index); i++){
        partidos[i] = partidos[i+1];
    }
    printf("Partido eliminado correctamente.\n");
    (*index)--;
}

void agregarPartido(struct Partido *partidos, int index){
    printf("%cEl partido ya se jug%c? (1-S%c, 0-No): ", 168, 162, 161);
    int jugado_flag;
    scanf("%d", &jugado_flag);
    if (jugado_flag == 0) 
        partidos[index].jugado = false;
    else
        partidos[index].jugado = true;

    if (!partidos[index].jugado) {
        partidos[index].jugado = false;
        partidos[index].jornada = index + 1;
        partidos[index].locales = true;
        snprintf(partidos[index].rival, sizeof partidos[index].rival, "No definido");
        partidos[index].golesAnotados = 0;
        partidos[index].golesConcedidos = 0;
        snprintf(partidos[index].fase, sizeof partidos[index].fase, "Fase regular");
        printf("El partido se marc%c como no jugado y se inicializaron los campos por defecto.\n", 162);
        mostrarPartidos(partidos, index, index + 1);
        return;
    }
    printf("Introduzca la jornada (n%cmero) del partido: ", 163);
    scanf("%d", &partidos[index].jornada);
    printf("\n%cContra qui%cn jug%c nuestro equipo?:\n", 168, 130, 160);
    scanf(" %31[^\n]", partidos[index].rival);
    printf("%cCu%cntos goles anot%c nuestro equipo?:", 168, 130, 162);
    scanf("%d", &partidos[index].golesAnotados);
    printf("%cCu%cntos goles concedimos?:", 168, 130);
    scanf("%d", &partidos[index].golesConcedidos);
    printf("Escriba que fase se jug%c:\n", 162);
    scanf(" %31[^\n]", partidos[index].fase);
}