#include "Grafos.hpp"

/*
Padrao de Arquivo de Entrada
O arquivo de entrada deve estar no formato abaixo. Na primeira linha, n  ́e o n ́umero de v ́ertices. Nas linhas seguintes
e antes da palavra “*edges”, h ́a uma listagem de r ́otulos dos v ́ertices. Note que cada v ́ertice possui um  ́ındice de 1 `a n.
Esse  ́ındice  ́e importante, pois ele  ́e utilizado nas defini ̧c ̃oes das arestas. Depois da palavra “*edges” cada linha conter ́a uma aresta. Por exemplo, na linha onde h ́a “a b valor do peso”, a e b s ̃ao os v ́ertices que a aresta conecta, valor do peso
 ́e o peso da aresta.
 */

// receba um arquivo de grafo e o  ́ındice do v ́ertice s como argumentos3.
// O programa deve fazer uma busca em largura4 a partir de s e devera
// imprimir a sa ́ıda na tela, onde cada linha dever ́a conter o nıvel
// seguido de “:” e a listagem de v ́ertices encontrados naquele nıvel.
void busca_em_largura();

// recebe um grafo como argumento. Ao final, o programa dever ́a
// determinar se ha ou n ̃ao um ciclo euleriano e exibi-lo
// na tela de acordo com o exemplo abaixo. A primeira linha
// devera conter o n ́umero 0 caso o grafo nao contenha o ciclo euleriano.
// Caso contenha, devera ser impresso 1 na primeira linha e, em seguida,
// a sequencia de v ́ertices que corresponde ao ciclo dever ́a ser impressa.
void ciclo_euleriano();

// ecebe um arquivo de grafo como argumento e um v ́ertice s.
// O programa dever ́a executar o algoritmo de Bellman-Ford
// ou de Dijkstra e informar o caminho percorrido de s ate
// todos os outros v ́ertices do grafo e a distancia necessaria.
// A saıda devera ser impressa na tela de acordo com o exemplo abaixo.
// Cada linha representa o caminho realizado de s para o vertice da respectiva
// linha.Em cada linha, antes dos s ́ımbolo “:” dever ́a estar o vertice destino.
// A direita de “:”, encontra-se o caminho percorrido de s ate o vertice destino.
// Mais a direita encontram-se os sımbolos “d =” seguidos da distancia
// necessaria para percorrer o caminho.
void bellman_ford();

// recebe um arquivo de grafo como argumento. O
// programa dever ́a exercutar o algoritmo de
// Floyd-Warshall e mostrar as distancias para
// cada par de vertices na tela utilizando o formato do exemplo abaixo.
// Na saıda, cada linha tera as distancias para
// vertice na ordem crescente dos ́ındices
// informados no arquivo de entrada.
void floyd_warshal();
