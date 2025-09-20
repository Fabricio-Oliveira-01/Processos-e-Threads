#include <iostream>
#include <fstream>

#include "funcsSequencial.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Uso: ./nome_do_executável <arquivo1.txt> <arquivo2.txt>" << std::endl;
        return 1;
    }

    std::string nomeArquivo1 = argv[1];
    std::string nomeArquivo2 = argv[2];

    // Matrizes criadas usando o struct
    Matriz A = lerMatriz(nomeArquivo1);
    Matriz B = lerMatriz(nomeArquivo2);

    if (A.linhas == 0 || B.linhas == 0) {
        std::cerr << "Erro ao carregar as matrizes.\n";
        return 1;
    }

    Matriz C = multSequencial(A, B); // Verifica se as dimensões são válidas e multiplica

    return 0;
}