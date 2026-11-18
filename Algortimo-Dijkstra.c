#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 5 
// Número de vértices (A, B, C, D, E)

// Função para encontrar o vértice com a menor distância não visitada
int minIndice(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Executa o algoritmo de Dijkstra a partir de um nó de origem
void dijkstra(int grafo[V][V], int origem) {
    int dist[V];
    bool sptSet[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[origem] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minIndice(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && grafo[u][v] && dist[u] != INT_MAX && dist[u] + grafo[u][v] < dist[v])
                dist[v] = dist[u] + grafo[u][v];
    }

    // Exibe os custos mínimos finais a partir da origem
    char nomes[] = {'A', 'B', 'C', 'D', 'E'};
    printf("\n--- Dijkstra (Topologia da Questão 5) a partir de %c ---\n", nomes[origem]);
    for (int i = 0; i < V; i++) {
        printf("Até o Roteador %c -> Custo Mínimo: %d\n", nomes[i], dist[i]);
    }
}

int main() {
    // Matriz de Adjacência para os nós A(0), B(1), C(2), D(3), E(4)
    // Baseado nas conexões visíveis na topologia:
    int grafo[V][V] = {
        {0, 2, 5, 0, 0}, // A conectado a B(2) e C(5)
        {2, 0, 4, 3, 0}, // B conectado a A(2), C(4) e D(3)
        {5, 4, 0, 1, 0}, // C conectado a A(5), B(4) e D(1)
        {0, 3, 1, 0, 2}, // D conectado a B(3), C(1) e E(2)
        {0, 0, 0, 2, 0}  // E conectado a D(2)
    };

    dijkstra(grafo, 0); // Executa calculando os caminhos a partir do Roteador A (0)
    return 0;
}
