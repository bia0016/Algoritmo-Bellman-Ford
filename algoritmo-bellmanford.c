#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Estrutura para representar uma aresta na rede
struct Aresta {
    int origem, destino, peso;
};

// Estrutura para representar o Grafo
struct Grafo {
    int V, E; // V = número de vértices, E = número de arestas
    struct Aresta* arestas;
};

// Função para criar o grafo
struct Grafo* criarGrafo(int V, int E) {
    struct Grafo* grafo = (struct Grafo*)malloc(sizeof(struct Grafo));
    grafo->V = V;
    grafo->E = E;
    grafo->arestas = (struct Aresta*)malloc(E * sizeof(struct Aresta));
    return grafo;
}

// Função principal do Bellman-Ford
void bellmanFord(struct Grafo* grafo, int origem) {
    int V = grafo->V;
    int E = grafo->E;
    int dist[V];

    // Passo 1: Inicializa as distâncias como infinito e origem como 0
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[origem] = 0;

    // Passo 2: Relaxa todas as arestas |V| - 1 vezes
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = grafo->arestas[j].origem;
            int v = grafo->arestas[j].destino;
            int peso = grafo->arestas[j].peso;
            if (dist[u] != INT_MAX && dist[u] + peso < dist[v])
                dist[v] = dist[u] + peso;
        }
    }

    // Exibe os resultados finais
    char nomes[] = {'A', 'B', 'C', 'D', 'E'};
    printf("\n--- Bellman-Ford: Tabela de Roteamento a partir de %c ---\n", nomes[origem]);
    for (int i = 0; i < V; i++)
        printf("Até %c -> Custo Mínimo: %d\n", nomes[i], dist[i]);
}

int main() {
    int V = 5; // 5 Roteadores (A=0, B=1, C=2, D=3, E=4)
    int E = 10; // 5 conexões bidirecionais = 10 arestas direcionadas
    struct Grafo* grafo = criarGrafo(V, E);

    // Definindo as arestas e custos da topologia em anel:
    // A <-> B (Custo 2)
    grafo->arestas[0] = (struct Aresta){0, 1, 2};
    grafo->arestas[1] = (struct Aresta){1, 0, 2};
    // B <-> C (Custo 3)
    grafo->arestas[2] = (struct Aresta){1, 2, 3};
    grafo->arestas[3] = (struct Aresta){2, 1, 3};
    // C <-> D (Custo 1)
    grafo->arestas[4] = (struct Aresta){2, 3, 1};
    grafo->arestas[5] = (struct Aresta){3, 2, 1};
    // D <-> E (Custo 4)
    grafo->arestas[6] = (struct Aresta){3, 4, 4};
    grafo->arestas[7] = (struct Aresta){4, 3, 4};
    // E <-> A (Custo 5)
    grafo->arestas[8] = (struct Aresta){4, 0, 5};
    grafo->arestas[9] = (struct Aresta){0, 4, 5};

    bellmanFord(grafo, 0); // Executa a partir do roteador A (0)

    // Libera a memória alocada
    free(grafo->arestas);
    free(grafo);

    return 0;
}
