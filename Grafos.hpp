#ifndef GRAFOS_HPP
#define GRAFOS_HPP

class Grafo
{
private:
public:
    // deve carregar um grafo a partir de um arquivo
    // no formato especificado ao final do enunciado
    Grafo(char *nome_do_arquivo) {}
    // retornr a quantidade de v ́ertices;
    int qtdVertices() {}
    // retorna a quantidade de arestas;
    int qtdArestas() {}
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
