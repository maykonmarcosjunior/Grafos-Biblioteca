#include "Grafos.hpp"
#include "Algoritmos_Grafos.hpp"

void busca_em_largura(std::string arquivo_do_grafo, int start)
{
    Grafo G = Grafo(arquivo_do_grafo);
    int V = G.qtdVertices();
    // ninguém tem ancestrais
    std::vector<int> ancestrais(V, NULL);
    // a distância é sempre infinita
    std::vector<int> distancias(V, MAX);
    G.busca_em_largura(start, ancestrais, distancias);
}

void ciclo_euleriano(std::string arquivo_do_grafo)
{
}

void bellman_ford(std::string arquivo_do_grafo, int start)
{
    Grafo G = Grafo(arquivo_do_grafo);
    int V = G.qtdVertices();
    // Inicializar distâncias e precursores
    std::vector<int> distancias(V, MAX);
    std::vector<int> ancestrais(V, -1);
    G.bellman_ford(start, ancestrais, distancias);
}

void floyd_warshall(std::string arquivo_do_grafo)
{
}
