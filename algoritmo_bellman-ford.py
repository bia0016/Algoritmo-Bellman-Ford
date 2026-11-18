# Algoritmo de Bellman-Ford em Redes de Computadores

class GrafoRede:
    def __init__(self, nos):
        self.nos = nos
        self.enlaces = []

    def adicionar_enlace(self, u, v, peso):
        self.enlaces.append((u, v, peso))
        self.enlaces.append((v, u, peso))  # Enlace bidirecional

    def bellman_ford(self, origem):
        distancias = {no: float('inf') for no in self.nos}
        predecessores = {no: None for no in self.nos}
        distancias[origem] = 0

        # Relaxamento das arestas |V| - 1 vezes
        for _ in range(len(self.nos) - 1):
            for u, v, peso in self.enlaces:
                if distancias[u] != float('inf') and distancias[u] + peso < distancias[v]:
                    distancias[v] = distancias[u] + peso
                    predecessores[v] = u

        # Exibição dos resultados
        print(f"=== Tabelas de Roteamento (Bellman-Ford) - Origem: {origem} ===")
        for no in self.nos:
            caminho = []
            atual = no
            while atual is not None:
                caminho.append(atual)
                atual = predecessores[atual]
            caminho.reverse()
            print(f"Destino: {no} | Custo Mínimo: {distancias[no]} | Rota: {' -> '.join(caminho)}")

# Topologia com 5 Roteadores
roteadores = ['A', 'B', 'C', 'D', 'E']
rede = GrafoRede(roteadores)

# Enlaces e custos iniciais (pelo menos 2 ligações por roteador)
rede.adicionar_enlace('A', 'B', 4)
rede.adicionar_enlace('A', 'C', 2)
rede.adicionar_enlace('B', 'C', 1)
rede.adicionar_enlace('B', 'D', 5)
rede.adicionar_enlace('C', 'D', 8)
rede.adicionar_enlace('C', 'E', 10)
rede.adicionar_enlace('D', 'E', 2)

rede.bellman_ford('A')
