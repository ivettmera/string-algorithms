# string-algorithms

Algoritmos sobre strings para el proyecto de tesis de pregrado. 

## Requisitos

`g++` con C++17 y `make`.

## Build

```sh
make              # compila bin/global, bin/local, bin/semiglobal
make bin/local    # compila uno solo
make clean
```

## Uso

Cada binario lee dos secuencias por `stdin` e imprime el score y un alineamiento óptimo. Ejemplo:

```sh
$ printf 'GACGGATTAG\nGATCGGAATAG\n' | ./bin/global
score: 6
GA-CGGATTAG
GATCGGAATAG
```

  `FREE_S_START` / `FREE_S_END`: espacios al inicio / fin de la primera secuencia.
  `FREE_T_START` / `FREE_T_END`:espacios al inicio / fin de la segunda secuencia. 
(Los 4 en `false` equivale a `global`)

Parámetros de score fijos: match `+1`, mismatch `-1`, hueco `-2`.

## Tests

```sh
make test          # compila y corre tests/
make run-<algo>    # corre un algoritmo con tests/global.in e imprime la output
```

Editar el `.in` para probar una entrada, regenerar el `.out` con
`make run-<algo>` tras verificar que la salida es correcta.

## Estructura

- `src/alignment/` — algoritmos de alineamiento
- `src/edit-distance/` — distancia de edición

## To-Do list

- [x] Alineamiento global, local y semiglobal (Setubal & Meidanis 1997, §3.2)
- [ ] Espacio lineal, gaps afines y generales (Setubal & Meidanis 1997, §3.3)