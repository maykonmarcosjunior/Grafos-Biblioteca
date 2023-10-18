#include <iostream>
#include "Grafos.hpp"

void busca_em_largura(std::string arquivo_do_grafo, int start)
{
    Grafo G = Grafo(arquivo_do_grafo);
    std::vector<std::string> resultado = G.busca_em_largura(start);
    for (std::string i : resultado)
    {
        std::cout << i << '\n';
    }
}

void ciclo_euleriano(std::string arquivo_do_grafo)
{
    Grafo G = Grafo(arquivo_do_grafo);
    std::list<int> resultado = G.cicloEuleriano();
    if (resultado.size())
    {
        std::cout << "1\n";
        for (auto it = resultado.begin(); it != resultado.end(); it++)
        {
            std::cout << *it << " ";
        }
        std::cout << "\n";
    }
    else
    {
        std::cout << "0\n";
    }
}

void bellman_ford(std::string arquivo_do_grafo, int start)
{
    Grafo G = Grafo(arquivo_do_grafo);
    std::string resultado = G.bellman_ford(start);
    if (resultado.size() > 0)
    {
        std::cout << resultado << '\n';
    }
    else
    {
        std::cout << "0\n";
    }
}

void dijkstra(std::string arquivo_do_grafo, int start)
{
    Grafo G = Grafo(arquivo_do_grafo);
    std::string resultado = G.dijkstra(start);
    if (resultado.size() > 0)
    {
        std::cout << resultado << '\n';
    }
    else
    {
        std::cout << "0\n";
    }
}

void floyd_warshall(std::string arquivo_do_grafo)
{
    Grafo G = Grafo(arquivo_do_grafo);
    auto distancias = G.floyd_warshall();
    for (std::size_t i = 0; i < distancias.size(); ++i)
    {
        std::cout << i + 1 << ':';
        for (std::size_t j = 0; j < distancias.size() - 1; ++j)
        {
            std::cout << distancias[i][j] << ',';
        }
        std::cout << distancias[i][distancias.size() - 1] << '\n';
    }
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
    std::cout << "\nCiclo Euleriano\n";
    ciclo_euleriano(nome_do_arquivo);
    std::cout << "\nBellman Ford\n";
    bellman_ford(nome_do_arquivo, start);
    std::cout << "\nDijkstra\n";
    dijkstra(nome_do_arquivo, start);
    std::cout << "\nFloyd Warshall\n";
    floyd_warshall(nome_do_arquivo);
    return 0;
}
