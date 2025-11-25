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
void mostrarDatos(struct Dato *datos, int n, int in);
void cargarDatos(struct Dato *datos);
void form(struct Dato *datos, int index);
void agregarJugador(struct Dato *datos, int index);
void modificarJugador(struct Dato *datos, int index);
void eliminarJugador(struct Dato *datos, int *index, int el);
int consultarJugador(struct Dato *datos, int index);
void ciclo(struct Dato *datos, int *index);

int main(){
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