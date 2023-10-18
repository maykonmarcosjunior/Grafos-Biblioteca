#include <iostream>
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

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Erro, voce deve digitar" << argv[0] << "<nome-do-arquivo>\n";
        return 1;
    }
    int start = 1;
    std::string nome_do_arquivo = argv[1];
    std::cout << "Busca em Largura\n";
    busca_em_largura(nome_do_arquivo, start);
    // std::cout << "\nCiclo Euleriano\n";
    // ciclo_euleriano(nome_do_arquivo);
    std::cout << "\nBellman Ford\n";
    bellman_ford(nome_do_arquivo, start);
    std::cout << "\nFloyd Warshall\n";
    floyd_warshall(nome_do_arquivo);
    return 0;
}
