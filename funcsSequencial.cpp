#include <iostream>
#include <fstream>
#include <iomanip> //Para setprecision
#include "funcsSequencial.h"


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


// Multiplicação de matrizes: A(i, j) * B(j, k) = C(i, k)
Matriz multSequencial(const Matriz& A, const Matriz& B) {
    Matriz C;
    C.linhas = A.linhas;
    C.colunas = B.colunas;
    C.valores.resize(C.linhas); // Para redimensionar as linhas do vetor da matriz C
    for (int i = 0; i < C.linhas; i++) {
        C.valores[i].resize(C.colunas, 0); // Para redimensionar as colunas e inicializar as posições
    }
    
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


void gerarMatrizSequencial(const Matriz& C, std::chrono::milliseconds tempoDeExecucao) {
    std::ofstream arquivoResultado("matriz_resultado.txt");
    if(!arquivoResultado.is_open()) {
        std::cerr << "Erro ao abrir o arquivo matriz_resultado.txt" << std::endl;
        return;
    }

    arquivoResultado << C.linhas << " " << C.colunas << std::endl; // Valores inseridos na primeira linha

    for(int i = 0; i < C.linhas; i++) {
        for(int j = 0; j < C.colunas; j++) {
            arquivoResultado << "c" << i + 1 << j + 1 << " " << std::fixed << std::setprecision(3) << C.valores[i][j] << std::endl;
            // Soma-se +1 para que os valores impressos comecem a partir de 1, não de 0
        }
    }

    arquivoResultado << tempoDeExecucao.count() << std::endl;
    arquivoResultado.close();
}