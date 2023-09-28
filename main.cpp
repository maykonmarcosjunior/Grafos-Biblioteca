#include <Algoritmos_Grafos.hpp>
#include <iostream>

int main(int argc, char *argv)
{
    if (argc != 2)
    {
        std::cout << "Erro, voce deve digitar ./main <nome-do-arquivo>\n";
        return 1;
    }
    int start = 1;
    std::string nome_do_arquivo = std::to_string(argv[1]);
    std::cout << "Busca em Largura\n";
    busca_em_largura(nome_do_arquivo, start);
    std::cout << "\nCiclo Euleriano\n";
    ciclo_euleriano(nome_do_arquivo);
    std::cout << "\nBellman Ford\n";
    bellman_ford(nome_do_arquivo, start);
    std::cout << "\nFloyd Warshall\n";
    floyd_warshall(nome_do_arquivo);
    return 0;
}
