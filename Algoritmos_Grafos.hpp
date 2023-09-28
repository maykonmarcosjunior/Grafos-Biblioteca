#include <string>

// receba um arquivo de grafo e o índice do vértice s como argumentos.
// O programa deve fazer uma busca em largura a partir de s e devera
// imprimir a saida na tela, onde cada linha devera conter o nıvel
// seguido de “:” e a listagem de vertices encontrados naquele nıvel.
void busca_em_largura(std::string arquivo_do_grafo, int start);

// recebe um grafo como argumento. Ao final, a função devera
// determinar se há ou não um ciclo euleriano e exibi-lo
// na tela de acordo com as intruções: A primeira linha
// devera conter o numero 0 caso o grafo não contenha o ciclo euleriano.
// Caso contenha, devera ser impresso 1 na primeira linha e, em seguida,
// a sequencia de vertices que corresponde ao ciclo devera ser impressa.
void ciclo_euleriano(std::string arquivo_do_grafo);

// recebe um arquivo de grafo como argumento e um vertice s.
// O programa devera executar o algoritmo de Bellman-Ford
// ou de Dijkstra e informar o caminho percorrido de s ate
// todos os outros vertices do grafo e a distancia necessaria.
// A saıda devera ser impressa na tela de acordo com o exemplo abaixo.
// Cada linha representa o caminho realizado de s para o vertice da respectiva
// linha.Em cada linha, antes dos s ́ımbolo “:” dever ́a estar o vertice destino.
// A direita de “:”, encontra-se o caminho percorrido de s ate o vertice destino.
// Mais a direita encontram-se os sımbolos “d =” seguidos da distancia
// necessaria para percorrer o caminho.
void bellman_ford(std::string arquivo_do_grafo, int start);
void dijkstra(std::string arquivo_do_grafo, int start);

// recebe um arquivo de grafo como argumento. O
// programa dever ́a exercutar o algoritmo de
// Floyd-Warshall e mostrar as distancias para
// cada par de vertices na tela utilizando o formato do exemplo abaixo.
// Na saıda, cada linha tera as distancias para
// vertice na ordem crescente dos ́ındices
// informados no arquivo de entrada.
void floyd_warshall(std::string arquivo_do_grafo);
