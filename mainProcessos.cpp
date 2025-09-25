#include <iostream>
#include <string>
#include "lerMatriz.h"

int main(int argc, char* argv[]) {
    if(argc != 4) {
        std::cout << "Uso: ./nome_do_executavel <arquivo1.txt> <arquivo2.txt> <valor de P>" << std::endl;
        return 1;
    }

    std::string nomeArquivo1 = argv[1];
    std::string nomeArquivo2 = argv[2];
    std::string P = argv[3];

    // Matrizes criadas usando o struct
    Matriz A = lerMatriz(nomeArquivo1);
    Matriz B = lerMatriz(nomeArquivo2);

    if (A.linhas == 0 || B.linhas == 0) {
        std::cerr << "Erro ao carregar as matrizes." << std::endl;
        return 1;
    }
    if (A.colunas != B.linhas) {
        std::cerr << "Erro: dimensoes incompativeis para multiplicacao." << std::endl;
        return 1;
    }


    return 0;
}