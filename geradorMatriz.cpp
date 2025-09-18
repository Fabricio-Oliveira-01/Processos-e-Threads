#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "criarMatrizes.cpp"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cout << "Uso: ./nome_do_executável <Dimensão 1 e 2 da Primeira Matriz> <Dimensões 1 e 2 da Segunda matriz>" << std::endl;
        return 1;
    }

    while(true) {
        std::string entrada;
        std::getline(std::cin, entrada);
    }
        



    return 0;
}

