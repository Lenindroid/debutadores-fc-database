#include<stdio.h>
#include <stdbool.h>
#include <string.h>

struct Dato {
    char matricula[10];
    char nombre [20];
    char apellido [25];
    int goles;
    int asistencias;
    int partidosJugados;
    char posiciones [20];
};

struct Partido {
    int jornada;
    bool locales;
    char rival[32];
    int golesAnotados;
    int golesConcedidos;
    char fase[32];
    bool jugado;
};

int main_jugadores();
int main_partidos();

void mostrarDatos(struct Dato *datos, int n, int in);
void cargarDatos(struct Dato *datos);
void form(struct Dato *datos, int index);
void agregarJugador(struct Dato *datos, int index);
void modificarJugador(struct Dato *datos, int index);
void eliminarJugador(struct Dato *datos, int *index, int el);
int consultarJugador(struct Dato *datos, int index);
void ciclo(struct Dato *datos, int *index);

void cargarPartidos(struct Partido *partidos, int n);
void mostrarPartidos(struct Partido *partidos, int n);
void agregarPartido(struct Partido *partidos, int index);
void modificarPartido(struct Partido *partidos, int index);
void eliminarPartido(struct Partido *partidos, int index);

int main(){
    int opcion=0;
    while(opcion!=3){
        printf("--Debutadores FC--\n");
        printf("Que desea hacer?\n1. Gestionar jugadores\n2. Gestionar partidos\n3. Salir\n");
        scanf("%d", &opcion);
        if (opcion == 1) {
            main_jugadores();
        } else if (opcion == 2) {
            main_partidos();
        } else if(opcion == 3){
            break;
        } else {
            printf("Opcion no valida.\n");
        }
    }   
    return 0;
}

int main_jugadores() {
    int index = 2;
    struct Dato datos[100];
    printf("--Base de datos de jugadores de Debutadores FC--\n");
    cargarDatos(datos);
    ciclo(datos, &index);
    return 0;
}

void ciclo(struct Dato *datos, int *index){
    int desicion=0,desicion2=0,el=0;
     while(desicion!=3){
        mostrarDatos(datos, *index+1,0);
        printf("Que desea hacer?\n1. Agregar jugador\n2. Consultar jugador\n3. Salir\n");
        scanf("%d",&desicion);
        switch (desicion)
        {
        case 1:
            (*index)++;
            agregarJugador(datos, *index);
            break;
        case 2:
            el=consultarJugador(datos, *index);
            if(el==-1){
                break;
            }
            printf("Que desea hacer?\n1. Modificar jugador\n2. Eliminar jugador\n 3.Regresar\n");
            scanf("%d",&desicion2);
            switch (desicion2)
            {
                case 1:
                    modificarJugador(datos, el);
                    break;
                case 2:
                    eliminarJugador(datos, index, el);
                    break;
                case 3:
                    break;
                default:
                    printf("Opcion no valida.\n");
                    break;
            }
            break;
            case 3:
                break;
        default:
            printf("Opcion no valida.\n");
            break;
        }
    }
}

void form(struct Dato *datos, int index){
        printf("Matricula:");
        scanf(" %s", datos[index].matricula);
        printf("Nombre:");
        scanf(" %s", datos[index].nombre);
        printf("Apellido:");
        scanf(" %s", datos[index].apellido);
        printf("Goles:");
        scanf("%d", &datos[index].goles);
        printf("Asistencias:");
        scanf("%d", &datos[index].asistencias);
        printf("Partidos Jugados:");
        scanf("%d", &datos[index].partidosJugados);
        printf("Posicion:");
        scanf(" %s", datos[index].posiciones);
}

void agregarJugador(struct Dato *datos, int index){
    int correcto=0;
    while(correcto==0){
        printf("--Ingresa los datos del nuevo jugador:--\n");
        form(datos, index);
        printf("Los datos son correctos? (1-Si, 0-No):");
        scanf("%d",&correcto);
        if(correcto==0){
            printf("Ingrese los datos nuevamente.\n");
        }else{
            printf("Jugador agregado correctamente.\n");
            correcto=1;
        }
    }
}

int consultarJugador(struct Dato *datos, int index){
    char b[10];
    printf("Ingrese la matricula del jugador a consultar:");
    scanf(" %s", b);
    for(int i=0; i<=index; i++){
        if(strcmp(datos[i].matricula, b) == 0){
            printf("--Jugador encontrado--\n");
            mostrarDatos(datos, i+1, i);
            return i;
        }
    }
    printf("Jugador no encontrado.\n");
    return -1;
}

void eliminarJugador(struct Dato *datos, int *index, int el){
    for(int i=el; i<(*index); i++){
        datos[i] = datos[i+1];
    }
    printf("Jugador eliminado correctamente.\n");
    (*index)--;
}
void modificarJugador(struct Dato *datos, int in){
     int correcto=0;
    while(correcto==0){
        printf("--Modificando datos del jugador--\n");
        form(datos, in);
        printf("Los datos son correctos? (1-Si, 0-No):");
        scanf("%d",&correcto);
        if(correcto==0){
            printf("Ingrese los datos nuevamente.\n");
        }else{
            printf("Datos del jugador modificados correctamente.\n");
            correcto=1;
        }
    }
}

void mostrarDatos(struct Dato *datos, int n, int in){
    printf("%-10s | %-15s | %-15s | %-6s | %-11s | %-15s | %-10s\n",
       "Matricula", "Nombre", "Apellido", "Goles", "Asistencias", "Partidos Jugados", "Posicion");
    printf("-----------------------------------------------------------------------------------------------\n");

    for (int i= in; i < n; i++) {
        
        printf("%-10s | %-15s | %-15s | %-6d | %-11d | %-15d | %-10s\n",
           datos[i].matricula,
           datos[i].nombre,
           datos[i].apellido,
           datos[i].goles,
           datos[i].asistencias,
           datos[i].partidosJugados,
           datos[i].posiciones);
    }
}
void cargarDatos(struct Dato *datos) {

    snprintf(datos[0].matricula, sizeof datos[0].matricula, "202530977");
    snprintf(datos[0].nombre, sizeof datos[0].nombre, "Lenin");
    snprintf(datos[0].apellido, sizeof datos[0].apellido, "Rojas Sanchez");
    datos[0].goles = 4;
    datos[0].asistencias = 6;
    datos[0].partidosJugados = 3;
    snprintf(datos[0].posiciones, sizeof datos[0].posiciones, "Portero");
    
    snprintf(datos[1].matricula, sizeof datos[1].matricula, "202523496");
    snprintf(datos[1].nombre, sizeof datos[1].nombre, "Daniel Elihud");
    snprintf(datos[1].apellido, sizeof datos[1].apellido, "Mancera Lopez");
    datos[1].goles = 6;
    datos[1].asistencias = 9;
    datos[1].partidosJugados = 6;
    snprintf(datos[1].posiciones, sizeof datos[1].posiciones, "Delantero");

    snprintf(datos[2].matricula, sizeof datos[2].matricula, "202523252");
    snprintf(datos[2].nombre, sizeof datos[2].nombre, "Jose Francisco");
    snprintf(datos[2].apellido, sizeof datos[2].apellido, "Lozada Luna");
    datos[2].goles = 5;
    datos[2].asistencias = 6;
    datos[2].partidosJugados = 8;
    snprintf(datos[2].posiciones, sizeof datos[2].posiciones, "Lateral derecho");
}

int main_partidos(){
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