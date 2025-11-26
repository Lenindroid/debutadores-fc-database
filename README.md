# lobotorneodebienvenida-database

## Descripción
Programa en C para gestionar la base de datos de Debutadores FC: jugadores y partidos.  
Permite: listar, agregar, modificar y eliminar jugadores; listar, agregar, modificar, eliminar y cargar partidos desde CSV.

## Estructuras (resumen)
- Dato (jugadores)
  - matricula, nombre, apellido, goles, asistencias, partidosJugados, posiciones
- Partido
  - jornada, locales (0/1), rival (string), golesAnotados, golesConcedidos, fase (string), jugado (0/1)

## Formato de los CSV
- jugadores.csv (7 columnas):
  matricula,nombre,apellido,goles,asistencias,partidosJugados,posicion
  Ejemplo:
  123456789,Juan,Perez,5,2,10,Delantero

- partidos.csv (7 columnas, en este orden):
  jornada,locales,rival,golesAnotados,golesConcedidos,fase,jugado
  Donde locales y jugado usan 0 o 1.
  Ejemplo:
  1,0,THE WOLFS,6,7,Fase regular,1

> Nota: el programa usa la ruta relativa del working directory para abrir los CSV. Ejecuta el binario desde la carpeta del proyecto (o coloca los CSV en el directorio de trabajo del ejecutable). Si el CWD es `output/` el programa no encontrará `partidos.csv` a menos que lo copies allí.

## Uso rápido
Compilar (MinGW / GCC en Windows):
```bash
gcc -std=c11 -Wall -Wextra debutadores.c -o debutadores.exe
```

Ejecutar (desde la carpeta del repo, donde están los CSV):
```bash
./debutadores.exe
```

Menú principal: elegir 1 para jugadores, 2 para partidos. El submenú de partidos incluye opción para cargar desde CSV (asegúrate que `partidos.csv` sea accesible desde el CWD).

## Notas prácticas
- Para booleans en CSV usa 0/1. El loader convierte 1 → true, 0 → false.
- Si no quieres que Git incluya la carpeta de ejecución/salida, añade `output/` a `.gitignore`.
- El array de partidos se guarda en memoria en `partidos[]`. Cargar CSV reemplaza los partidos en memoria y actualiza `numeroDePartidos`.
- Opción 7 del menú de partidos guarda los partidos a CSV. Si ejecutas el binario desde la carpeta `output/` el programa escribe `../partidos.csv`; ejecuta desde la raíz del proyecto para leer/escribir `partidos.csv` en la carpeta del repo.

## Aclaración para Edmundo (nuestro profesor)
El código de este repositorio es original y totalmente creado por los integrantes del equipo.  
Sin embargo decidimos hacerlo público para casos de emergencia y así el código esté seguro.