#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "criarMatrizes.h"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cout << "Uso: ./nome_do_executável <Dimensão 1 e 2 da Primeira Matriz> <Dimensões 1 e 2 da Segunda matriz>" << std::endl;
        return 1;
    }

    int linha1 = std::stoi(argv[1]);
    int coluna1 = std::stoi(argv[2]);
    int linha2 = std::stoi(argv[3]);
    int coluna2 = std::stoi(argv[4]);
  
    geracaoDeMatriz(linha1, coluna1, "matriz1.txt");
    geracaoDeMatriz(linha2, coluna2, "matriz2.txt");

    std::cout << std::endl;
    std::cout << "Matrizes geradas com sucesso!" << std::endl;

    return 0;
}


