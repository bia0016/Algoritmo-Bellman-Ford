# Algoritmo de Bellman-Ford aplicado à Redes de Computadores
class Grafo:
    def __init__(self, vertices):
        self.V = vertices  # Lista dos roteadores (nós)
        self.arestas = []  # Lista para armazenar as conexões (Origem, Destino, Custo)

    def adicionar_aresta(self, u, v, w):
        self.arestas.append((u, v, w))

    def bellman_ford(self, origem):
        # Passo 1: Inicializa as distâncias da origem para todos como infinito
        distancia = {i: float("inf") for i in self.V}
        # A distância do nó de origem para ele mesmo é 0
        distancia[origem] = 0

        # Passo 2: Relaxa todas as arestas |V| - 1 vezes
        for _ in range(len(self.V) - 1):
            for u, v, w in self.arestas:
                if distancia[u] != float("inf") and distancia[u] + w < distancia[v]:
                    distancia[v] = distancia[u] + w

        # Passo 3: Exibe a tabela de roteamento final (custos mínimos)
        print(f"\n==================================================")
        print(f" TABELA DE ROTEAMENTO FINAL (A partir do Roteador {origem})")
        print(f"==================================================")
        for destino in self.V:
            print(f" Roteador {origem} -> Roteador {destino} | Custo Mínimo: {distancia[destino]}")
        print(f"==================================================\n")

# --- Configuração da Topologia da Atividade ---
# Roteadores presentes na topologia: A, B, C, D, E
roteadores = ['A', 'B', 'C', 'D', 'E']
rede = Grafo(roteadores)

# Adicionando os enlaces bidirecionais com os custos da imagem:
# A <-> B (Custo 2)
rede.adicionar_aresta('A', 'B', 2)
rede.adicionar_aresta('B', 'A', 2)

# B <-> C (Custo 3)
rede.adicionar_aresta('B', 'C', 3)
rede.adicionar_aresta('C', 'B', 3)

# C <-> D (Custo 1)
rede.adicionar_aresta('C', 'D', 1)
rede.adicionar_aresta('D', 'C', 1)

# D <-> E (Custo 4)
rede.adicionar_aresta('D', 'E', 4)
rede.adicionar_aresta('E', 'D', 4)

# E <-> A (Custo 5)
rede.adicionar_aresta('E', 'A', 5)
rede.adicionar_aresta('A', 'E', 5)

# Executando o algoritmo a partir do Roteador A para gerar as rotas finais
rede.bellman_ford('A')
