#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Uso: ./nome_do_executável matriz1.txt matriz2.txt" << std::endl;
        return 1;
    }

    std::string nomeArquivo1 = argv[1];
    std::string nomeArquivo2 = argv[2];

    std::ifstream arquivo1(nomeArquivo1);
    std::ifstream arquivo2(nomeArquivo2);

    if(!arquivo1.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << nomeArquivo1 << std::endl;
        return;
    }
    if(!arquivo2.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << nomeArquivo2 << std::endl;
        return;
    }

    return 0;
}