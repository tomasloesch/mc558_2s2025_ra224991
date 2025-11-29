# MC558 - Projeto de Implementação 1

**Aluno:** Tomás Conti Loesch
**RA:** 224991

## Arquivos do Projeto

* `dijkstra.cpp`: Implementação do Dijkstra Clássico (Heap).
* `biDijkstra.cpp`: Implementação do Dijkstra Bidirecional.
* `dialDijkstra.cpp`: Implementação do Dijkstra com Otimização de Dial (Buckets).
* `biDialDijkstra.cpp`: Implementação do Dijkstra Bidirecional com Otimização de Dial.
* `plShortestPath.cpp`: Modelagem e resolução via Programação Linear (Gurobi).
* `ra224991.pdf`: Relatório técnico comparativo.

## Requisitos

* Compilador C++ com suporte ao padrão C++17 (ex: `g++`).
* Biblioteca **Gurobi Optimizer** (necessária apenas para `plShortestPath.cpp`).

## Instruções de Compilação

### 1. Gurobi:
Para compilar o código que utiliza o Gurobi, certifique-se de que os caminhos das bibliotecas, -I e -L, correspondem à instalação na sua máquina.
Exemplo de comando para Gurobi 13.0 em /opt/gurobi1300:

```bash
g++ -std=c++17 -O3 plShortestPath.cpp -o plShortestPath -I/opt/gurobi1300/linux64/include -L/opt/gurobi1300/linux64/lib -lgurobi_c++ -lgurobi130 -lm
```

### 2. Algoritmos Padrão (C++)
Para compilar os algoritmos de Dijkstra e Dial:

```bash
g++ -std=c++17 -O3 dijkstra.cpp -o dijkstra
g++ -std=c++17 -O3 biDijkstra.cpp -o biDijkstra
g++ -std=c++17 -O3 dialDijkstra.cpp -o dialDijkstra
g++ -std=c++17 -O3 biDialDijkstra.cpp -o biDialDijkstra
```
## Instrução de Execução
Todos os programas leem a entrada da entrada padrão e imprimem a distância calculada na saída padrão.
`./nome_do_executavel < arquivo_de_entrada.in`

