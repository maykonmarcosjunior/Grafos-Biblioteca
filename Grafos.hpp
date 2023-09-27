#ifndef GRAFOS_HPP
#define GRAFOS_HPP
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#define MAX 2147483647
class Grafo
{
private:
    struct Vertice
    {
        int idx;
        std::string label;
        std::vector<int> vizinhos;
    };

    struct Arco
    {
        int u, v, peso;
    };

    std::ifstream input_file;
    std::vector<Vertice> vertices;
    std::vector<Arco> arcos;

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
        int n_vertices;
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
            Vertice v;
            v.idx = indice;
            v.label = rotulo;
            vertices.push_back(v);
        }
        input_file >> confirm;
        if (confirm != "*edges")
        {
            std::cout << "Erro ao ler o arquivo!\n";
        }
        int u, v, peso;
        while (input_file >> u >> v >> peso)
        {
            Arco e;
            e.u = u;
            e.v = v;
            e.peso = peso;
            arcos.push_back(e);
            vertices[u - 1].vizinhos.push_back(v);
            vertices[v - 1].vizinhos.push_back(u);
        }
        input_file.close();
    }
    // retornr a quantidade de vwrtices;
    int qtdVertices()
    {
        return static_cast<int>(vertices.size());
    }
    // retorna a quantidade de arestas;
    int qtdArestas()
    {
        return static_cast<int>(arcos.size());
    }
    // retorna o grau do vertice v
    int grau(int v)
    {
        return static_cast<int>(vertices[v - 1].vizinhos.size());
    }
    // retorna o rotulo do vertice v
    std::string rotulo(int v)
    {
        return vertices[v - 1].rotulo;
    }
    // retorna os vizinhos do vertice v
    std::vector<int> vizinhos(int v)
    {
        return static_cast<int>(vertices[v - 1].vizinhos);
    }
    // se {u, v}∈ E, retorna verdadeiro; se nao existir, retorna falso
    bool haAresta(int u, int v)
    {
        auto vizinhos = &(vertices[u - 1].vizinhos);
        for (int i = 0; i < static_cast<int>(vizinhos->size()); ++i)
        {
            if (vizinhos[i] == v)
            {
                return true;
            }
        }
        return false;
    }
    // se {u, v} ∈ E, retorna o peso da aresta {u, v};
    // se nao existir, retorna um valor infinito positivo;
    int peso(int u, int v)
    {
        for (int i = 0; i < static_cast<int>(arcos.size()); ++i)
        {
            auto e = arcos[i];
            if (e.u == u && e.v == v)
            {
                return e.peso;
            }
        }
        return MAX;
    }
};

#endif // GRAFOS_HPP
