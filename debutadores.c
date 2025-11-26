#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include <direct.h>   // _getcwd
#define MAX_PARTIDOS 128

bool partidosCargados = false;
int numeroDePartidos = 7;

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
struct Partido partidos[MAX_PARTIDOS];

int main_jugadores();
int main_partidos();

void mostrarDatos(struct Dato *datos, int n, int in);
int cargarDatos(struct Dato *datos, int *in);
int subirDatos(struct Dato *datos, int in);
void form(struct Dato *datos, int index);
void agregarJugador(struct Dato *datos, int index);
void modificarJugador(struct Dato *datos, int index);
void eliminarJugador(struct Dato *datos, int *index, int el);
int consultarJugador(struct Dato *datos, int index);
void ciclo(struct Dato *datos);

void cargarPartidos(struct Partido *partidos, int n);
void mostrarPartidos(struct Partido *partidos, int inicio, int n);
void agregarPartido(struct Partido *partidos, int index);
void modificarPartido(struct Partido *partidos, int index);
void eliminarPartido(struct Partido *partidos, int *index, int el);
int cargarCSVPartidos(struct Partido *partidos);

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

int main_partidos(){
    if (!partidosCargados) {
        cargarPartidos(partidos, numeroDePartidos);
        partidosCargados = true;
    }
    
    printf("--Gestion de partidos de Debutadores FC--\n");
    printf("%cQu%c desea hacer?\n", 168, 130);
    printf("1. Mostrar partidos\n2. Modificar partido\n3. Reiniciar base de datos de partidos\n4. A%cadir partido\n5. Eliminar partido\n6. Cargar desde CSV\n7. Guardar a CSV\n8. Salir", 164);
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
        case 6: {
            int n = cargarCSVPartidos(partidos);
            if (n < 0) {
                printf("No se pudo abrir partidos.csv\n");
            } else {
                numeroDePartidos = n;
                partidosCargados = true;
                printf("Se cargaron %d partidos desde partidos.csv\n", n);
                mostrarPartidos(partidos, 0, numeroDePartidos);
            }
            break;
        }
        case 7:
            printf("Funcionalidad no implementada aun.\n");
            break;
        case 8:
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
}

int cargarCSVPartidos(struct Partido *partidos) {
    FILE *file = fopen("../partidos.csv", "r");
    if (!file) {
        char cwd[512];
        if (_getcwd(cwd, sizeof cwd)) {
            fprintf(stderr, "No se pudo abrir partidos.csv. CWD=%s\n", cwd);
        } else {
            fprintf(stderr, "No se pudo abrir partidos.csv. No se pudo obtener CWD.\n");
        }
        perror("fopen partidos.csv");
        return -1;
    }

    char line[512];
    int records = 0;

    while (fgets(line, sizeof line, file)) {
        if (line[0] == '\n' || line[0] == '\r') continue;

        int jornada, locales_i, golesA, golesB, jugado_i;
        char rival[32];
        char fase[64];

        int matched = sscanf(line,
            " %d,%d,%31[^,],%d,%d,%63[^,\r\n],%d",
            &jornada,
            &locales_i,
            rival,
            &golesA,
            &golesB,
            fase,
            &jugado_i
        );

        if (matched != 7) {
            fprintf(stderr, "Formato incorrecto en partidos.csv (linea %d)\n", records + 1);
            continue;
        }

        partidos[records].jornada = jornada;
        partidos[records].locales = locales_i ? true : false;
        strncpy(partidos[records].rival, rival, sizeof partidos[records].rival - 1);
        partidos[records].rival[sizeof partidos[records].rival - 1] = '\0';
        partidos[records].golesAnotados = golesA;
        partidos[records].golesConcedidos = golesB;
        strncpy(partidos[records].fase, fase, sizeof partidos[records].fase - 1);
        partidos[records].fase[sizeof partidos[records].fase - 1] = '\0';
        partidos[records].jugado = jugado_i ? true : false;

        records++;
        if (records >= MAX_PARTIDOS) break;
    }
    numeroDePartidos = records;

    fclose(file);
    return records;
}