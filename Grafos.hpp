#ifndef GRAFOS_HPP
#define GRAFOS_HPP
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>
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
        int u, v;
        float peso;
        bool operator<(const Arco &outro) const
        {
            return peso < outro.peso;
        }
    };

    // arquivo que dará origem ao grafo
    std::ifstream input_file;
    // vetor com todos os vértices
    std::vector<Vertice> vertices;
    // vetor com todos os arcos
    std::vector<Arco> arcos;
    // matriz de adjacencia
    std::vector<std::vector<float>> matriz;

    // obtém o caminho feito pelo bellman-for
    std::vector<int> get_path(int start, int end, std::vector<int> &ancestrais)
    {
        std::vector<int> path;

        // Se não for possível chegar ao destino
        // a partir da origem, retorne um caminho vazio
        if (ancestrais[end - 1] == -1 && start != end)
            return path;

        // Vá de trás para frente para construir o caminho
        // Vá de trás para frente para construir o caminho
        int current = end;
        while (current != -1 && current != start)
        {
            path.insert(path.begin(), current);
            current = ancestrais[current - 1];
        }
        path.insert(path.begin(), start); // incluir o vértice de início
        return path;
    }

    std::pair<bool, std::list<int>> buscarSubCicloEuleriano(int v, std::map<Arco, bool> &C)
    {
        std::list<int> Ciclo = {v};
        int origem = v;
        do
        {
            if (vertices[v - 1].vizinhos.empty())
            {
                return {false, {}};
            }

            int u = -1;
            for (int viz : vertices[v - 1].vizinhos)
            {
                Arco e = {v, viz, peso(v, viz)};
                if (C.find(e) == C.end() || !C[e])
                {
                    u = viz;
                    break;
                }
            }

            if (u == -1)
            {
                return {false, {}};
            }

            C[{v, u, peso(v, u)}] = true;
            Ciclo.push_back(u);
            v = u;
        } while (v != origem);

        for (int x : Ciclo)
        {
            for (int adj : vertices[x - 1].vizinhos)
            {
                if (C.find({x, adj, peso(x, adj)}) == C.end() || !C[{x, adj, peso(x, adj)}])
                {
                    std::pair<bool, std::list<int>> resultado = buscarSubCicloEuleriano(adj, C);
                    if (!resultado.first)
                    {
                        return {false, {}};
                    }
                    Ciclo.splice(std::find(Ciclo.begin(), Ciclo.end(), x), resultado.second);
                }
            }
        }
        return {true, Ciclo};
    }

public:
    // carrega os vértices e arcos
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
            std::cout << "Erro ao ler o arquivo\n";
        }
        // criando a matriz de adjacencia
        matriz.resize(n_vertices, std::vector<float>(n_vertices, MAX));
        // para ler vértice a vértice
        for (int i = 0; i < n_vertices; ++i)
        {
            int indice;
            std::string rotulo;
            // lendo o indice
            input_file >> indice;
            // aramzenando o resto da linha em label
            std::getline(input_file, rotulo);
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
        int u, v;
        float peso;
        while (input_file >> u >> v >> peso)
        {
            Arco e;
            e.u = u;
            e.v = v;
            e.peso = peso;
            arcos.push_back(e);
            vertices[u - 1].vizinhos.push_back(v);
            vertices[v - 1].vizinhos.push_back(u);
            matriz[u - 1][v - 1] = peso;
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
    // se {u, v} ∈ E, retorna verdadeiro;
    // se nao existir, retorna falso
    bool haAresta(int u, int v)
    {
        return matriz[u - 1][v - 1] != MAX;
    }
    // se {u, v} ∈ E, retorna o peso da aresta {u, v};
    // se nao existir, retorna um valor infinito positivo;
    float peso(int u, int v)
    {
        return matriz[u - 1][v - 1];
    }

    // printa a arvore de busca em largura
    // onde cada posição corresponde a um
    // nível da arvore
    void busca_em_largura(int start, std::vector<int> &ancestrais,
                          std::vector<int> &distancias)
    {
        int V = qtdVertices();
        // ninguém tem ancestrais
        ancestrais.assign(V, -1);
        // a distância é sempre infinita
        distancias.assign(V, MAX);
        // não visitamos ninguém
        std::vector<bool> conhecidos(V, 0);

        conhecidos[start - 1] = 1;
        distancias[start - 1] = 0;
        std::queue<int> fila;
        fila.push(start);
        std::vector<std::string> saida;
        for (int i = 0; i < V; ++i)
        {
            std::string nivel = std::to_string(i) + ": ";
            saida.push_back(nivel);
        }
        saida[0] += std::to_string(start);
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
                    if (saida[nivel].back() == ' ')
                    {
                        saida[nivel] += std::to_string(v);
                    }
                    else
                    {
                        saida[nivel] += "," + std::to_string(v);
                    }
                    if (nivel > n_niveis)
                    {
                        n_niveis = nivel;
                    }
                    distancias[v - 1] = nivel;
                    fila.push(v);
                }
            }
        }
        for (int i = 0; i <= n_niveis; ++i)
        {
            std::cout << saida[i] << '\n';
        }
    }

    std::pair<bool, std::list<int>> cicloEuleriano()
    {
        std::map<Arco, bool> C;
        // Seleciona o primeiro vértice conectado a uma aresta
        int v = vertices[0].idx;
        std::pair<bool, std::list<int>> resultado = buscarSubCicloEuleriano(v, C);
        bool achou = resultado.first;
        std::list<int> Ciclo = resultado.second;

        if (!achou)
        {
            return {false, {}};
        }

        for (const Arco &e : arcos)
        {
            if (C.find(e) == C.end() || !C[e])
            {
                return {false, {}};
            }
        }

        return {true, Ciclo};
    }

    // printa a distância entre s e os outros vértices
    bool bellman_ford(int s, std::vector<int> &ancestrais,
                      std::vector<int> &distancias)
    {
        int V = qtdVertices();
        // ninguém tem ancestrais
        ancestrais.assign(V, -1);
        // a distância é sempre infinita
        distancias.assign(V, MAX);
        // distância do vértice inicial é 0
        distancias.at(s - 1) = 0;

        // Relaxar as arestas V-1 vezes
        for (int _ = 1; _ < V; _++)
        {
            for (Arco e : arcos)
            {
                int u = e.u;
                int v = e.v;
                float weight = e.peso;
                if (distancias[u - 1] < MAX && distancias[v - 1] > distancias[u - 1] + weight)
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
            float weight = e.peso;
            if (distancias[u - 1] + weight < distancias[v - 1])
            {
                // Ciclo de peso negativo encontrado
                return false;
            }
        }

        for (int i = 1; i <= V; ++i)
        {
            std::cout << i << ": ";
            std::vector<int> path = get_path(s, i, ancestrais);
            for (size_t j = 0; j < path.size(); ++j)
            {
                std::cout << path[j];
                if (j < path.size() - 1)
                {
                    std::cout << ',';
                }
            }
            std::cout << "; d=" << distancias[i - 1] << std::endl;
        }
        return true;
    }

    void dijkstra(int s, std::vector<int> &dist, std::vector<int> &pred)
    {
        int V = qtdVertices();

        dist.assign(V, MAX);
        pred.assign(V, -1);
        std::vector<bool> visited(V, false);

        using pii = std::pair<float, int>; // Peso, Vértice
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
                float weight = peso(u, v);
                if (!visited[v - 1] && dist[u - 1] + weight < dist[v - 1])
                {
                    dist[v - 1] = dist[u - 1] + weight;
                    pred[v - 1] = u;
                    pq.push({dist[v - 1], v});
                }
            }
        }
    }

    // printa a distancia entre quaisquer par de vértices
    std::vector<std::vector<float>> floyd_warshall()
    {
        int V = qtdVertices();
        std::vector<std::vector<float>> distancias(V, std::vector<float>(V, MAX));

        // Inicializa as distâncias com os pesos das arestas existentes
        for (Arco arco : arcos)
        {
            distancias[arco.u - 1][arco.v - 1] = arco.peso;
            // Se o grafo for não direcionado
            distancias[arco.v - 1][arco.u - 1] = arco.peso;
        }

        // Define a distância de um vértice para ele mesmo como 0
        for (int i = 0; i < V; i++)
        {
            distancias[i][i] = 0;
        }

        // Atualizando as distâncias
        for (int k = 0; k < V; k++)
        {
            for (int i = 0; i < V; i++)
            {
                for (int j = 0; j < V; j++)
                {
                    if (distancias[i][k] < MAX && distancias[k][j] < MAX && distancias[i][k] + distancias[k][j] < distancias[i][j])
                    {
                        distancias[i][j] = distancias[i][k] + distancias[k][j];
                    }
                }
            }
        }
        for (int i = 0; i < V; ++i)
        {
            std::cout << i + 1 << ':';
            for (int j = 0; j < V - 1; ++j)
            {
                std::cout << distancias[i][j] << ',';
            }
            std::cout << distancias[i][V - 1] << '\n';
        }
        return distancias;
    }

}; // Grafos

#endif // GRAFOS_HPP
