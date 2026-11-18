#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#V 5 
// Número de vértices (A, B, C, D, E)

// Função para encontrar o vértice com a menor distância que ainda não foi visitado
int minIndice(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Função principal do Dijkstra
void dijkstra(int grafo[V][V], int origem) {
    int dist[V];      // Armazena a menor distância de origem até i
    bool sptSet[V];   // True se o vértice i já foi incluído na árvore de caminho mais curto

    // Inicializa todas as distâncias como infinito e sptSet como falso
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[origem] = 0; // Distância do nó de origem para ele mesmo é 0

    // Encontra o caminho mais curto para todos os vértices
    for (int count = 0; count < V - 1; count++) {
        int u = minIndice(dist, sptSet);
        sptSet[u] = true;

        // Atualiza a distância dos vértices adjacentes ao vértice escolhido
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && grafo[u][v] && dist[u] != INT_MAX && dist[u] + grafo[u][v] < dist[v])
                dist[v] = dist[u] + grafo[u][v];
    }

    // Exibe os resultados finais
    char nomes[] = {'A', 'B', 'C', 'D', 'E'};
    printf("\n--- Dijkstra: Tabela de Roteamento a partir de %c ---\n", nomes[origem]);
    for (int i = 0; i < V; i++)
        printf("Até %c -> Custo Mínimo: %d\n", nomes[i], dist[i]);
}

int main() {
    // Matriz de adjacência representando a topologia (Custos do Anel)
    // A=0, B=1, C=2, D=3, E=4
    // Custos: A-B=2, B-C=3, C-D=1, D-E=4, E-A=5
    int grafo[V][V] = {
        {0, 2, 0, 0, 5}, // A
        {2, 0, 3, 0, 0}, // B
        {0, 3, 0, 1, 0}, // C
        {0, 0, 1, 0, 4}, // D
        {5, 0, 0, 4, 0}  // E
    };

    dijkstra(grafo, 0); // Executa a partir do nó A (0)
    return 0;
}
