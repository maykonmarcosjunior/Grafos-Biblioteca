#ifndef GRAFOS_HPP
#define GRAFOS_HPP
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <iostream>
#define MAX 2147483647
class Grafo
{
private:
    // contém o índice, o rótulo
    // e os índices dos vizinhos
    struct Vertice
    {
        int idx;
        std::string label;
        std::vector<int> vizinhos;
    };

    // os índices dos 2 vértices
    // e o peso da ligação
    struct Arco
    {
        int u, v, peso;
    };

    // arquivo que dará origem ao grafo
    std::ifstream input_file;
    // vetor com todos os vértices
    std::vector<Vertice> vertices;
    // vetor com todos os arcos
    std::vector<Arco> arcos;

public:
    // carrega s vértices e arcos
    // a partir do nome do arquivo
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
        // para ler vértice a vértice
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
        // lendo arco a arco
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
    // retorna a quantidade de vértices;
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
    // retorna o rótulo do vertice v
    std::string rotulo(int v)
    {
        return vertices[v - 1].label;
    }
    // retorna os vizinhos do vertice v
    std::vector<int> vizinhos(int v)
    {
        return vertices.at(v - 1).vizinhos;
    }
    // se {u, v}∈ E, retorna verdadeiro; se nao existir, retorna falso
    bool haAresta(int u, int v)
    {
        std::vector<int> *vizinhos = &(vertices[u - 1].vizinhos);
        for (int i = 0; i < static_cast<int>(vizinhos->size()); ++i)
        {
            if (vizinhos->at(i) == v)
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
            Arco *e = &(arcos[i]);
            if (e->u == u && e->v == v)
            {
                return e->peso;
            }
        }
        return MAX;
    }

    // printa a arvore de busca em largura
    // onde cada posição corresponde a um
    // nível da arvore
    void busca_em_largura(int start, std::vector<int> &ancestrais,
                          std::vector<int> &distancias)
    {
        int V = qtdVertices();
        // ninguém tem ancestrais
        std::vector<int> ancestrais(V, -1);
        // não visitamos ninguém
        std::vector<bool> conhecidos(V, 0);
        // a distância é sempre infinita
        std::vector<int> distancias(V, MAX);

        conhecidos[start - 1] = 1;
        distancias[start - 1] = 0;
        std::queue<int> fila;
        fila.push(start);
        std::vector<std::string> saida;
        for (int i = 0; i < V; ++i)
        {
            std::string nivel = "nivel " + std::to_string(i) + ":";
            saida.push_back(nivel);
        }
        saida[0] += " " + std::to_string(start);
        int n_niveis = 0;
        while (fila.size())
        {
            int u = fila.front();
            fila.pop();
            for (int v : vertices[u - 1].vizinhos)
            {
                if (!(conhecidos[v - 1]))
                {
                    ancestrais[v - 1] = u;
                    conhecidos[v - 1] = 1;
                    int nivel = distancias[u - 1] + 1;
                    saida[nivel] += " " + std::to_string(v);
                    if (nivel > n_niveis)
                    {
                        n_niveis = nivel;
                    }
                    distancias[v - 1] = nivel;
                    fila.push(v);
                }
            }
        }
        for (int i = 0; i < n_niveis; ++i)
        {
            std::cout << saida[i] << '\n';
        }
    }
    bool bellman_ford(int s, std::vector<int> &ancestrais,
                      std::vector<int> &distancias)
    {
        int V = qtdVertices();
        int E = qtdArestas();

        distancias[s - 1] = 0; // distância do vértice inicial é 0

        // Relaxar as arestas V-1 vezes
        for (int i = 1; i < V; i++)
        {
            for (Arco e : arcos)
            {
                int u = e.u;
                int v = e.v;
                int weight = e.peso;
                if (distancias[v - 1] >= distancias[u - 1] + weight)
                {
                    distancias[v - 1] = distancias[u - 1] + weight;
                    ancestrais[v - 1] = u;
                }
            }
        }

        // Verificar ciclos de peso negativo
        for (Arco e : arcos)
        {
            int u = e.u;
            int v = e.v;
            int weight = e.peso;
            if (distancias[u - 1] + weight < distancias[v - 1])
            {
                // Ciclo de peso negativo encontrado
                return false;
            }
        }

        return true;
    }

    void Dijkstra(int s, std::vector<int> &dist, std::vector<int> &pred)
    {
        int V = qtdVertices();

        dist.assign(V, MAX);
        pred.assign(V, -1);
        std::vector<bool> visited(V, false);

        using pii = std::pair<int, int>; // Peso, Vértice
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;

        dist[s - 1] = 0;
        pq.push({0, s});

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            if (visited[u - 1])
                continue;
            visited[u - 1] = true;

            for (int v : vizinhos(u))
            {
                int weight = peso(u, v);
                if (!visited[v - 1] && dist[u - 1] + weight < dist[v - 1])
                {
                    dist[v - 1] = dist[u - 1] + weight;
                    pred[v - 1] = u;
                    pq.push({dist[v - 1], v});
                }
            }
        }
    }

    std::vector<int> Hierholzer()
    {
        int start_vertex = 0;
        int odd_count = 0;

        for (int i = 0; i < qtdVertices(); ++i)
        {
            if (grau(i + 1) % 2 != 0)
            {
                odd_count++;
                start_vertex = i;
            }
        }

        if (odd_count != 0 && odd_count != 2)
        {
            // Não é possível encontrar um caminho ou ciclo euleriano.
            return {};
        }

        std::stack<int> current_path;
        std::vector<int> circuit;

        current_path.push(start_vertex + 1);

        int current_vertex = start_vertex + 1;

        while (!current_path.empty())
        {
            if (!vertices[current_vertex - 1].vizinhos.empty())
            {
                current_path.push(current_vertex);
                int next_vertex = vertices[current_vertex - 1].vizinhos.back();
                // Removendo a aresta do grafo
                vertices[current_vertex - 1].vizinhos.pop_back();
                current_vertex = next_vertex;
            }
            else
            {
                circuit.push_back(current_vertex);
                current_vertex = current_path.top();
                current_path.pop();
            }
        }

        return circuit;
    }
}; // Grafos

#endif // GRAFOS_HPP
