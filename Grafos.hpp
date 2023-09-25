#ifndef GRAFOS_HPP
#define GRAFOS_HPP
#include <string>
#include <fstream>
#include <iostream>
class Grafo
{
private:
    std::ifstream input_file;
    int n_vertices;
    int n_arcos;
    struct Vertice
    {
        int idx;
        std::string rotulo
        Vertice(int indice, std::string name)
        {
            idx = indice;
            rotulo = name;
        }
    };

public:
    // deve carregar um grafo a partir de um arquivo
    // no formato especificado ao final do enunciado
    Grafo(std::string nome_do_arquivo)
    {
        input_file.open(nome_do_arquivo);
        if (!input_file.is_open())
        {
            std::cout << "Erro ao abrir o arquivo!\n";
        }
        std::string confirm;
        input_file >> confirm >> n_vertices;
        if (confirm != "*vertices")
        {
            std::cout << "Erro ao ler o arquivo!\n";
        }
        int indice;
        std::string rotulo;
        for (int i = 0; i < n_vertices; ++i)
        {
            input_file >> indice >> rotulo;
            Vertice v = Vertice(indice, rotulo);
        }
        input_file >> confirm;
        if (confirm != "*edges")
        {
            std::cout << "Erro ao ler o arquivo!\n";
        }
        int u, v, peso;
        n_arcos = 0;
        while (input_file >> u >> v >> peso)
        {
            n_arcos++;
        }
        input_file.close();
    }
    // retornr a quantidade de v ́ertices;
    int qtdVertices()
    {
        return n_vertices;
    }
    // retorna a quantidade de arestas;
    int qtdArestas()
    {
        return n_arcos;
    }
    // retorna o grau do vertice v
    int grau(int v) {}
    // retorna o rotulo do vertice v
    char *rotulo(int v) {}
    // retorna os vizinhos do vertice v
    int *vizinhos(int v) {}
    // se {u, v}∈ E, retorna verdadeiro; se nao existir, retorna falso
    bool haAresta(int u, int v) {}
    // se {u, v} ∈ E, retorna o peso da aresta {u, v};
    // se nao existir, retorna um valor infinito positivo;
    int peso(int u, int v) {}
};

#endif // GRAFOS_HPP
