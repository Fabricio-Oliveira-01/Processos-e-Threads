#include <iostream>
#include <fstream>

#include "lerMatriz.h"


// Struct (declarado no .h) para retornar matriz, linhas e colunas
Matriz lerMatriz(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    if(!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo" << nomeArquivo << std::endl;
        return {0, 0, {}}; // Retorna matriz vazia seguindo o formato do struct
    }

    Matriz M;
    arquivo >> M.linhas >> M.colunas; // Armazena as dimensões da primeira linha
    M.valores.resize(M.linhas, std::vector<double>(M.colunas)); // Redimensiona o vetor "dados" do struct para o formato da matriz

    for(int i = 0; i < M.linhas; i++) {
        for(int j = 0; j < M.colunas; j++) {
            arquivo >> M.valores[i][j];
        }
    }

    arquivo.close();
    return M;
}