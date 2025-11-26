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
int cargarDatos(struct Dato *datos, int *in);
int subirDatos(struct Dato *datos, int in);
void form(struct Dato *datos, int index);
void agregarJugador(struct Dato *datos, int index);
void modificarJugador(struct Dato *datos, int index);
void eliminarJugador(struct Dato *datos, int *index, int el);
int consultarJugador(struct Dato *datos, int index);
void ciclo(struct Dato *datos);


int main() {
    struct Dato datos[100];
    printf("--Base de datos de jugadores de Debutadores FC--\n");
    ciclo(datos);
    return 0;
}

void ciclo(struct Dato *datos){
    int index=0;
    int desicion=0,desicion2=0,el=0;
    cargarDatos(datos, &index);
     while(desicion!=3){
        mostrarDatos(datos, index+1,0);
        printf("Que desea hacer?\n1. Agregar jugador\n2. Consultar jugador\n3. Salir\n");
        scanf("%d",&desicion);
        switch (desicion)
        {
        case 1:
            index++;
            agregarJugador(datos, index);
            subirDatos(datos,index);
            break;
        case 2:
            el=consultarJugador(datos, index);
            if(el==-1){
                break;
            }
            printf("Que desea hacer?\n1. Modificar jugador\n2. Eliminar jugador\n3.Regresar\n");
            scanf("%d",&desicion2);
            switch (desicion2)
            {
                case 1:
                    modificarJugador(datos, el);
                    subirDatos(datos, index);
                    break;
                case 2:
                    eliminarJugador(datos, &index, el);
                    subirDatos(datos, index);
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

void form(struct Dato *datos, int index) {
    printf("Matricula: ");
    scanf(" %9s", datos[index].matricula);
    getchar();
    printf("Nombre: ");
    scanf(" %19[^\n]", datos[index].nombre);
    getchar();
    printf("Apellido: ");
    scanf(" %24[^\n]", datos[index].apellido);
    getchar();
    printf("Goles: ");
    scanf("%d", &datos[index].goles);
    getchar();
    printf("Asistencias: ");
    scanf("%d", &datos[index].asistencias);
    getchar();
    printf("Partidos Jugados: ");
    scanf("%d", &datos[index].partidosJugados);
    getchar();
    printf("Posicion: ");
    scanf(" %19[^\n]", datos[index].posiciones);
    getchar();
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
int cargarDatos(struct Dato *datos, int *in) {
    FILE *file;
    int read=0;
    file = fopen("jugadores.csv", "r");

    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }
    while(true){
        read = fscanf(file,
            " %9[^,],%19[^,],%24[^,],%d,%d,%d,%19[^\n]\n",
            datos[*in].matricula,
            datos[*in].nombre,
            datos[*in].apellido,
            &datos[*in].goles,
            &datos[*in].asistencias,
            &datos[*in].partidosJugados,
            datos[*in].posiciones
        );

        if (read == EOF || feof(file)) break;

        if (read != 7) {
            printf("Formato de archivo incorrecto.\n");
            fclose(file);
            return 1;
        }
        (*in)++;
    }
    fclose(file);     
    return 0;
}

int subirDatos(struct Dato *datos, int in){
    FILE *file;
    file = fopen("jugadores.csv", "w");

    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }
    for(int i=0; i<=in;i++){
        fprintf(file,
                "%s,%s,%s,%d,%d,%d,%s\n",
                datos[i].matricula,
                datos[i].nombre,
                datos[i].apellido,
                datos[i].goles,
                datos[i].asistencias,
                datos[i].partidosJugados,
                datos[i].posiciones);
    }  
    fclose(file);   
    return 0;
}
