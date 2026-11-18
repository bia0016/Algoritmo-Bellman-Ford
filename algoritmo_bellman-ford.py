# ==========================================================
# Algoritmo de Bellman-Ford - Topologia Completa em Malha (A, B, C, D, E)
# ==========================================================

class Grafo:
    def __init__(self, vertices):
        self.V = vertices  
        self.arestas = []  

    def adicionar_aresta(self, u, v, w):
        self.arestas.append((u, v, w))

    def bellman_ford(self, origem):
        distancia = {i: float("inf") for i in self.V}
        distancia[origem] = 0

        for _ in range(len(self.V) - 1):
            for u, v, w in self.arestas:
                if distancia[u] != float("inf") and distancia[u] + w < distancia[v]:
                    distancia[v] = distancia[u] + w

        print(f"\n--- Tabela de Roteamento Final (A partir de {origem}) ---")
        for destino in self.V:
            print(f"Roteador {origem} -> Roteador {destino} | Custo Mínimo: {distancia[destino]}")

# Roteadores
roteadores = ['A', 'B', 'C', 'D', 'E']
rede = Grafo(roteadores)

# 1. Enlaces do Anel Externo
rede.adicionar_aresta('A', 'B', 2); rede.adicionar_aresta('B', 'A', 2)
rede.adicionar_aresta('B', 'C', 3); rede.adicionar_aresta('C', 'B', 3)
rede.adicionar_aresta('C', 'D', 1); rede.adicionar_aresta('D', 'C', 1)
rede.adicionar_aresta('D', 'E', 4); rede.adicionar_aresta('E', 'D', 4)
rede.adicionar_aresta('E', 'A', 5); rede.adicionar_aresta('A', 'E', 5)

# 2. Enlaces Internos/Atalhos (Garantem múltiplas rotas de entrada e saída)
rede.adicionar_aresta('A', 'C', 6); rede.adicionar_aresta('C', 'A', 6)
rede.adicionar_aresta('B', 'D', 3); rede.adicionar_aresta('D', 'B', 3)

# Executa a partir do Roteador A
rede.bellman_ford('A')
