#ifndef GRAFOS_HPP
#define GRAFOS_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
#include <queue>
// #include <stack>
// ciclo euleriano
#include <list>
#include <map>

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

    // para o algoritmo de Kruskal
    struct cd_Elemento
    {
        cd_Elemento *pai;
        int rank;
        cd_Elemento()
        {
            pai = this;
            rank = 0;
        }

        void ligar(cd_Elemento *x, cd_Elemento *y)
        {
            if (x->rank > y->rank)
            {
                y->pai = x;
            }
            else
            {
                x->pai = y;
                if (x->rank == y->rank)
                {
                    y->rank++;
                }
            }
        }

        cd_Elemento *encontrar(cd_Elemento *x)
        {
            if (x->pai != x)
            {
                x->pai = encontrar(x->pai);
            }
            return x->pai;
        }
        void uniao(cd_Elemento *x, cd_Elemento *y)
        {
            ligar(encontrar(x), encontrar(y));
        }
    };

    // vetor com todos os vértices
    std::vector<Vertice> vertices;
    // vetor com todos os arcos
    std::vector<Arco> arcos;
    // matriz de vizinhosacencia
    std::vector<std::vector<float>> matriz;

    std::list<int> buscarSubCicloEuleriano(int v,
                                           std::map<Arco,
                                                    bool> &C)
    {
        std::list<int> Ciclo = {v};
        int origem = v;
        do
        {
            if (vertices[v - 1].vizinhos.empty())
            {
                Ciclo.clear();
                return Ciclo;
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
            for (int vizinhos : vertices[x - 1].vizinhos)
            {
                if (C.find({x, vizinhos, peso(x, vizinhos)}) == C.end() || !C[{x, vizinhos, peso(x, vizinhos)}])
                {
                    std::list<int> resultado = buscarSubCicloEuleriano(vizinhos, C);
                    if (!resultado.size())
                    {
                        Ciclo.clear();
                        return Ciclo;
                    }
                    Ciclo.splice(std::find(Ciclo.begin(), Ciclo.end(), x), resultado);
                }
            }
        }
        return Ciclo;
    }

    // função auxiliar para realizar a DFS
    void DFS_Visit_OT(int v, std::vector<bool> &conhecidos,
                      std::deque<int> &ordem)
    {
        conhecidos[v - 1] = true;

        for (int u : this->vizinhos(v))
        {
            if (!conhecidos[u - 1])
            {
                DFS_Visit_OT(u, conhecidos, ordem);
            }
        }

        ordem.push_front(v);
    }

public:
    // carrega os vértices e arcos
    // a partir do nome do arquivo
    Grafo(std::string nome_do_arquivo)
    {
        // arquivo que dará origem ao grafo
        std::ifstream input_file;
        input_file.open(nome_do_arquivo);
        if (!input_file.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo!\n";
        }
        std::string confirm;
        int n_vertices;
        input_file >> confirm >> n_vertices;
        if (confirm != "*vertices")
        {
            std::cerr << "Erro ao ler os vertices\n";
        }
        // criando a matriz de vizinhosacencia
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
        if (confirm != "*edges" && confirm != "*arcs")
        {
            std::cerr << "Erro ao ler os arcos/arestas!\n";
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
            if (confirm == "*edges")
            {
                matriz[v - 1][u - 1] = peso;
            }
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
        return matriz[u - 1][v - 1] < MAX;
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
    std::vector<std::string> busca_em_largura(int start)
    {
        std::vector<int> ancestrais;
        std::vector<int> distancias;
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
        while (static_cast<int>(saida.size()) > n_niveis + 1)
        {
            saida.pop_back();
        }
        return saida;
    }

    std::list<int> cicloEuleriano()
    {
        std::map<Arco, bool> C;
        // Seleciona o primeiro vértice conectado a uma aresta
        int v = vertices[0].idx;
        std::list<int> Ciclo = buscarSubCicloEuleriano(v, C);

        if (!Ciclo.size())
        {
            Ciclo.clear();
            return Ciclo;
        }

        for (const Arco &e : arcos)
        {
            if (C.find(e) == C.end() || !C[e])
            {
                Ciclo.clear();
                return Ciclo;
            }
        }

        return Ciclo;
    }

    // retorna a distância entre s e os outros vértices
    std::string bellman_ford(int s)
    {
        // Inicializar distâncias e precursores
        std::vector<int> ancestrais;
        std::vector<int> distancias;
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

        std::string saida;
        // Verificar ciclos de peso negativo
        for (Arco e : arcos)
        {
            int u = e.u;
            int v = e.v;
            float weight = e.peso;
            if (distancias[u - 1] + weight < distancias[v - 1])
            {
                // Ciclo de peso negativo encontrado
                return saida;
            }
        }

        for (int i = 1; i <= V; ++i)
        {
            saida += std::to_string(i) + ": ";
            std::vector<int> path;
            // Se não for possível chegar ao destino
            // a partir da origem, retorne um caminho vazio
            if (!(ancestrais[i - 1] == -1 && s != i))
            {
                // Vá de trás para frente para construir o caminho
                // Vá de trás para frente para construir o caminho
                int current = i;
                while (current != -1 && current != s)
                {
                    path.insert(path.begin(), current);
                    current = ancestrais[current - 1];
                }
                // incluir o vértice de início
                path.insert(path.begin(), s);
            }
            for (size_t j = 0; j < path.size(); ++j)
            {
                saida += std::to_string(path[j]);
                if (j < path.size() - 1)
                {
                    saida += ',';
                }
            }
            saida += "; d=" + std::to_string(distancias[i - 1]) + '\n';
        }
        return saida;
    }

    std::string dijkstra(int s)
    {
        std::vector<int> dist;
        std::vector<int> pred;
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
        std::string saida;
        for (int i = 1; i <= V; ++i)
        {
            saida += std::to_string(i) + ": ";
            std::vector<int> path;

            // Se não for possível chegar ao destino
            // a partir da origem, retorne um caminho vazio
            if (!(pred[i - 1] == -1 && s != i))
            {
                // Vá de trás para frente para construir o caminho
                // Vá de trás para frente para construir o caminho
                int current = i;
                while (current != -1 && current != s)
                {
                    path.insert(path.begin(), current);
                    current = pred[current - 1];
                }
                // incluir o vértice de início
                path.insert(path.begin(), s);
            }
            for (size_t j = 0; j < path.size(); ++j)
            {
                saida += std::to_string(path[j]);
                if (j < path.size() - 1)
                {
                    saida += ',';
                }
            }
            saida += "; d=" + std::to_string(dist[i - 1]) + '\n';
        }
        return saida;
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
        return distancias;
    }

    void DFSVisitAdaptado(int s,
                          int &tempo,
                          std::vector<int> &Conhecidos,
                          std::vector<int> &Inicio,
                          std::vector<int> &Ancestrais,
                          std::vector<int> &Final,
                          std::vector<std::vector<int>> &vizinhosT)
    {
        Conhecidos.at(s - 1) = 1;
        tempo++;
        Inicio.at(s - 1) = tempo;

        for (int u : vizinhosT.at(s - 1))
        { // ajustando para 0-indexado
            if (!Conhecidos.at(u - 1))
            { // ajustando para 0-indexado
                Ancestrais.at(u - 1) = s;
                DFSVisitAdaptado(u, tempo,
                                 Conhecidos,
                                 Inicio,
                                 Ancestrais,
                                 Final,
                                 vizinhosT);
            }
        }
        tempo++;
        Final.push_back(tempo);
    }

    std::vector<int> DFSAdaptado(const std::vector<int> &ordem,
                                 std::vector<std::vector<int>> &vizinhosT)
    {
        int V = qtdVertices();
        std::vector<int> Conhecidos(V, 0);
        std::vector<int> Inicio(V, -1);
        std::vector<int> Ancestrais(V, -1);
        std::vector<int> Final;

        int tempo = 0;

        for (int idx : ordem)
        {
            if (!Conhecidos.at(idx - 1))
            {
                DFSVisitAdaptado(idx, tempo,
                                 Conhecidos,
                                 Inicio,
                                 Ancestrais,
                                 Final,
                                 vizinhosT);
            }
        }
        return Ancestrais;
    }

    void DFSVisit(int s,
                  int &tempo,
                  std::vector<int> &Conhecidos,
                  std::vector<int> &Inicio,
                  std::vector<int> &Ancestrais,
                  std::vector<int> &Final)
    {
        Conhecidos[s - 1] = 1;
        tempo++;
        Inicio[s - 1] = tempo;

        for (int u : vizinhos(s))
        { // ajustando para 0-indexado
            if (!Conhecidos.at(u - 1))
            { // ajustando para 0-indexado
                Ancestrais.at(u - 1) = s;
                DFSVisit(u, tempo, Conhecidos,
                         Inicio, Ancestrais, Final);
            }
        }
        tempo++;
        Final.push_back(tempo);
    }

    std::vector<std::vector<int>> DFS()
    {
        int V = qtdVertices();
        std::vector<int> Conhecidos(V, 0);
        std::vector<int> Inicio(V, -1);
        std::vector<int> Ancestrais(V, -1);
        std::vector<int> Final;

        int tempo = 0;

        for (int u = 1; u <= V; u++)
        {
            if (!Conhecidos[u - 1])
            {
                DFSVisit(u, tempo, Conhecidos,
                         Inicio, Ancestrais, Final);
            }
        }
        std::vector<std::vector<int>> saida;
        saida.push_back(Conhecidos);
        saida.push_back(Inicio);
        saida.push_back(Ancestrais);
        saida.push_back(Final);
        return saida;
    }

    std::vector<int> componentes_fortemente_conexas()
    {
        std::vector<std::vector<int>> dfs = DFS();
        std::vector<int> F = dfs[3];

        std::vector<std::vector<int>> vizinhosTranspostos(qtdVertices());
        // Inverte a ordem dos arcos para criar a lista de arcos transposta
        for (const Arco &arco : arcos)
        {
            vizinhosTranspostos[arco.v - 1].push_back(arco.u);
        }
        std::vector<int> ordem(F.size());
        std::iota(ordem.begin(), ordem.end(), 1);
        std::sort(ordem.begin(), ordem.end(), [&F](int i, int j)
                  { return F[i] > F[j]; });
        std::vector<int> AT = DFSAdaptado(ordem, vizinhosTranspostos);
        return AT;
    }

    // implementação do algoritmo de ordenação topológica usando DFS
    std::deque<int> ordenacao_topologica()
    {
        int V = qtdVertices();
        std::deque<int> ordem;
        std::vector<bool> conhecidos(V, false);

        for (int v = 1; v <= V; v++)
        {
            if (!conhecidos[v - 1])
            {
                DFS_Visit_OT(v, conhecidos, ordem);
            }
        }
        return ordem;
    }

    // implementação do algoritmo de Kruskal para encontrar a árvore geradora mínima do grafo
    std::vector<Arco> Kruskal()
    {
        int V = qtdVertices();
        std::vector<Arco> arvore_geradora_minima;
        std::vector<cd_Elemento *> S(V);
        for (int v = 0; v < V; v++)
        {
            cd_Elemento *x = new cd_Elemento();
            S[v] = x;
        }

        // ordena as arestas em ordem crescente de peso
        std::sort(arcos.begin(), arcos.end());

        // processa as arestas em ordem crescente de peso
        for (std::size_t i = 0; i < arcos.size(); i++)
        {
            auto x = S[arcos[i].u - 1];
            auto y = S[arcos[i].v - 1];

            // verifica se u e v estão em conjuntos disjuntos
            if (x->pai != y->pai)
            {
                // une os conjuntos disjuntos
                x->uniao(x, y);

                // adiciona a aresta na árvore geradora mínima
                arvore_geradora_minima.push_back(arcos[i]);
            }
        }

        for (int v = 0; v < V; v++)
        {
            delete S[v];
        }

        return arvore_geradora_minima;
    }

    // implementação do algoritmo de Prim para encontrar a árvore geradora mínima do grafo
    std::vector<std::vector<int>> Prim()
    {
        std::vector<std::vector<int>> saida;

        std::vector<std::pair<int, std::pair<int, int>>> arvore_geradora_minima;
        std::vector<bool> visitado(this->qtdVertices(), false);
        std::vector<int> distancia(this->qtdVertices(), MAX);
        std::vector<int> pai(this->qtdVertices(), -1);

        // escolhe o primeiro vértice como raiz da árvore geradora mínima
        int raiz = 0;
        distancia[raiz] = 0;

        // processa todos os vértices
        for (int i = 0; i < this->qtdVertices(); i++)
        {
            // encontra o vértice não visitado com menor distância
            int u = -1;
            for (int j = 0; j < this->qtdVertices(); j++)
            {
                if (!visitado[j] && (u == -1 || distancia[j] < distancia[u]))
                {
                    u = j;
                }
            }

            // marca o vértice como visitado
            visitado[u] = true;

            // adiciona a aresta na árvore geradora mínima
            if (pai[u] != -1)
            {
                arvore_geradora_minima.push_back(std::make_pair(distancia[u], std::make_pair(u, pai[u])));
            }

            // atualiza as distâncias dos vizinhos de u
            for (std::size_t j = 0; j < this->vizinhos(u).size(); j++)
            {
                int v = this->vizinhos(u)[j];
                int peso = this->peso(u, v);
                if (!visitado[v] && peso < distancia[v])
                {
                    distancia[v] = peso;
                    pai[v] = u;
                }
            }
        }

        // return arvore_geradora_minima;
        return saida;
    }
    /*
        // função auxiliar para realizar a busca em largura na rede residual
        std::vector<int> busca_em_largura_ek(Grafo &Gf, int s, int t)
        {
            std::vector<bool> conhecidos(Gf.qtdVertices(), false);
            std::vector<int> ancestrais(Gf.qtdVertices(), -1);
            std::queue<int> Q;

            conhecidos[s] = true;
            Q.push(s);

            while (!Q.empty())
            {
                int u = Q.front();
                Q.pop();

                for (int v : Gf.vizinhos(u))
                {
                    if (!conhecidos[v] && Gf.peso(u, v) > 0)
                    {
                        conhecidos[v] = true;
                        ancestrais[v] = u;

                        if (v == t)
                        {
                            // encontrou um caminho aumentante
                            std::vector<int> caminho;
                            int w = t;
                            while (w != s)
                            {
                                caminho.push_back(w);
                                w = ancestrais[w];
                            }
                            caminho.push_back(s);
                            std::reverse(caminho.begin(), caminho.end());
                            return caminho;
                        }

                        Q.push(v);
                    }
                }
            }

            // não encontrou caminho aumentante
            return std::vector<int>();
        }

        int Edmonds_Karp(int s, int v)
        {
            // cria a rede residual
            Grafo Gf = this->rede_residual();

            // inicializa o fluxo máximo
            int F = 0;

            // busca caminhos aumentantes na rede residual
            std::vector<int> p = busca_em_largura_ek(Gf, s, t);
            while (!p.empty())
            {
                // encontra o fluxo do caminho aumentante
                int fp = MAX;
                for (int i = 0; i < p.size() - 1; i++)
                {
                    int u = p[i];
                    int v = p[i + 1];
                    fp = std::min(fp, Gf.peso(u, v));
                }

                // atualiza o fluxo máximo
                F += fp;

                // atualiza a rede residual
                for (int i = 0; i < p.size() - 1; i++)
                {
                    int u = p[i];
                    int v = p[i + 1];
                    Gf.atualiza_peso(u, v, -fp);
                    Gf.atualiza_peso(v, u, fp);
                }

                // busca o próximo caminho aumentante
                p = busca_em_largura_ek(Gf, s, t);
            }

            return F;
        }
    */
}; // Grafos

#endif // GRAFOS_HPP
