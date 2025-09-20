#include <iostream>
#include <fstream>

#include "funcsSequencial.h"

// Struct (declarado no .h) para retornar matriz, linhas e colunas
Matriz lerMatriz(std::string nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    if(!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo" << nomeArquivo << std::endl;
        return {0, 0, {}}; // Retorna matriz vazia seguindo o formato do struct
    }

    Matriz M;

    arquivo >> M.linhas >> M.colunas; // Armazena as dimensões da primeira linha
    M.valores.resize(M.linhas, std::vector<int>(M.colunas)); // Redimensiona o vetor "dados" do struct para o formato da matriz

    for(int i = 0; i < M.linhas; i++) {
        for(int j = 0; j < M.colunas; j++) {
            arquivo >> M.valores[i][j];
        }
    }

    arquivo.close();
    return M;
}



// Multiplicação de matrizes: A(i, j) * B(j, k) = C(i, k)
Matriz multSequencial(const Matriz& A, const Matriz& B) {
    if (A.colunas != B.linhas) {
        std::cerr << "Erro: dimensões incompatíveis para multiplicação." << std::endl;
        return {0, 0, {}}; // Retorna matriz vazia seguindo o formato do struct
    }

    Matriz C;
    C.linhas = A.linhas;
    C.colunas = B.colunas;
    C.valores.assign(C.linhas, std::vector<int>(C.colunas, 0)); // Atribui os novos valores de linhas e colunas para o vetor da matriz
    
    // Multiplicação de matrizes:
    // Soma dos produtos dos elementos correspondentes de uma linha da primeira matriz com uma coluna da segunda
    for (int i = 0; i < A.linhas; i++) {
        for (int j = 0; j < B.colunas; j++) {
            for (int k = 0; k < A.colunas; k++) { // B.linhas = A.colunas para que a multiplicação seja válida, então ambos servem
                // A cada iteração, soma o resultado do produto à posição atual de C,
                // até percorrer todos os valores da linha de A e da coluna de B, para partir para a próxima posição de C
                C.valores[i][j] += A.valores[i][k] * B.valores[k][j];
            }
        }
    }

    return C;
}