#include<stdio.h>
#include <stdbool.h>

struct Dato {
    char matricula[10];
    char nombre [20];
    char apellido [25];
    int goles;
    int asistencias;
    int partidosJugados;
    char posiciones [20];
};
void agregarJugador(struct Dato *datos, int index){
    printf("--Ingresa los datos del nuevo jugador:--\n");
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
int main(){
    int n = 3;
    struct Dato datos[n];
    agregarJugador(datos, 0);
    
    return 0;
}