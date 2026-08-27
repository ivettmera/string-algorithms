# string-algorithms
Algoritmos de alineamiento de strings para Proyecto de tesis de pregrado

## Requisitos

`g++` con C++17 y `make`

## Build y tests

```sh
make            
make test       
make bin/global # compila solo un tipo
make clean
```

`tests/run.sh` toma cada `tests/**/<caso>.in` y lo pasa por `stdin` al binario que
lleva el nombre de su carpeta padre, y compara con `<caso>.out`

Correr un caso a mano:

```sh
./bin/semiglobal 0011 < tests/alignment/semiglobal/sm97_34.in
```

## Módulos

### `src/alignment/` — (SM97 3.2)

Ejemplo:

```sh
$ printf 'GACGGATTAG\nGATCGGAATAG\n' | ./bin/global
score: 6
GA-CGGATTAG
GATCGGAATAG
```


### `src/rna/` — (trabajo futuro)
