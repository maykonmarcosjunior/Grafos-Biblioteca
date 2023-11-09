#include <iostream>
#include "Grafos.hpp"

void busca_em_largura(Grafo &G, int start = 1)
{
    std::vector<std::string> resultado = G.busca_em_largura(start);
    for (std::string i : resultado)
    {
        std::cout << i << '\n';
    }
}

void ciclo_euleriano(Grafo &G)
{
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

void bellman_ford(Grafo &G, int start)
{
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

void dijkstra(Grafo &G, int start)
{
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

void floyd_warshall(Grafo &G)
{
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

void componentes_fortemente_conexas(Grafo &G)
{
    std::vector<int> resultado = G.componentes_fortemente_conexas();
    for (std::size_t i = 0; i < resultado.size(); ++i)
    {
        std::cout << resultado[i] << ',';
    }
    std::cout << '\n';
}

void ordenacao_topologica(Grafo &G)
{
    std::deque<int> resultado = G.ordenacao_topologica();
    for (std::size_t i = 0; i < resultado.size() - 1; ++i)
    {
        std::cout << G.rotulo(resultado[i]) << " → ";
    }
    std::cout << G.rotulo(resultado.back()) << ".\n";
}

void Kruskal(Grafo &G)
{
    auto resultado = G.Kruskal();
    int soma = 0;
    std::string arestas = "";
    for (std::size_t i = 0; i < resultado.size(); ++i)
    {
        arestas += std::to_string(resultado[i].u) + "-" + std::to_string(resultado[i].v) + ", ";
        soma += resultado[i].peso;
    }
    std::cout << soma << '\n';
    std::cout << arestas << '\n';
}

void Prim(Grafo &G)
{
    std::vector<std::vector<int>> resultado = G.Prim();
    int soma = 0;
    std::string arestas;
    for (std::size_t i = 0; i < resultado.size(); ++i)
    {
        arestas += resultado[i][0] + '-' + resultado[i][1] + ", ";
        soma += resultado[i][2];
    }
    std::cout << soma << '\n';
    std::cout << arestas << '\n';
}

// Ao final, imprima na tela o valor do fluxo
// máximo resultante da execução do algoritmo
// de Edmonds-Karp.
void EdmondsKarp(Grafo &G)
{
    // int resultado = G.EdmondsKarp();
    // std::cout << resultado << '\n';
}

// Crie um programa que receba um arquivo de grafo bipartido,
// não-dirigido, não-ponderado e informe qual o valor do
// emparelhamento máximo e quais arestas pertencem a ele.
// Utilize o algoritmo de HopcroftKarp.

void HopcroftKarp(Grafo &G)
{
    // int resultado = G.HopcroftKarp();
    // std::cout << resultado << '\n';
}

//[Coloração de Vértices] (2,5pts) Crie um programa que
// recebe um grafo não-dirigido e não-ponderado como argumento.
// Ao final, informe a coloração m´ınima e qual número cromático
// foi utilizado em cada vértice

void ColoracaoVertices(Grafo &G)
{
    // int resultado = G.ColoracaoVertices();
    // std::cout << resultado << '\n';
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Erro, voce deve digitar" << argv[0] << "<nome-do-arquivo>\n";
        return 1;
    }
    std::string nome_do_arquivo = argv[1];
    Grafo G = Grafo(nome_do_arquivo);
    /*
    std::cout << "Busca em Largura\n";
    busca_em_largura(G);
    std::cout << "\nCiclo Euleriano\n";
    ciclo_euleriano(G);
    std::cout << "\nBellman Ford\n";
    bellman_ford(G);
    std::cout << "\nDijkstra\n";
    dijkstra(G);
    std::cout << "\nFloyd Warshall\n";
    floyd_warshall(G);
    */
    std::cout << "\nComponentes Fortemente Conexas\n";
    componentes_fortemente_conexas(G);
    std::cout << "\nOrdenacao Topologica\n";
    ordenacao_topologica(G);
    std::cout << "\nKruskal\n";
    Kruskal(G);
    // std::cout << "\nPrim\n";
    // Prim(G);
    return 0;
}
