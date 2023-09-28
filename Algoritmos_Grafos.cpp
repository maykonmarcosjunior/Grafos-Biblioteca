#include "Algoritmos_Grafos.hpp"
#include "Grafos.hpp"

void busca_em_largura(std::string arquivo_do_grafo, int start)
{
    Grafo G = Grafo(arquivo_do_grafo);
    std::vector<int> ancestrais;
    std::vector<int> distancias;
    G.busca_em_largura(start, ancestrais, distancias);
}

void ciclo_euleriano(std::string arquivo_do_grafo)
{
    Grafo G = Grafo(arquivo_do_grafo);
    G.cicloEuleriano();
}

void bellman_ford(std::string arquivo_do_grafo, int start)
{
    Grafo G = Grafo(arquivo_do_grafo);
    // Inicializar distâncias e precursores
    std::vector<int> distancias;
    std::vector<int> ancestrais;
    G.bellman_ford(start, ancestrais, distancias);
}

void dijkstra(std::string arquivo_do_grafo, int start)
{
    Grafo G = Grafo(arquivo_do_grafo);
    std::vector<int> distancias;
    std::vector<int> ancestrais;
    G.dijkstra(start, ancestrais, distancias);
}

void floyd_warshall(std::string arquivo_do_grafo)
{
    Grafo G = Grafo(arquivo_do_grafo);
    G.floyd_warshall();
}
