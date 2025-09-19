#include "criarMatrizes.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <random>

void geracaoDeMatriz (int linha, int coluna, const std::string& nomeArquivo){

    //Vetor de vetores. Cria um vetor onde cada elemento é um vetor. Não precisa gerenciar memória.
    std::vector<std::vector<int>> matriz(linha, std::vector<int>(coluna));

    //Configura o gerador de números aleatórios, mas não inicializa ele.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1000);

    //Cria, para cada posição, um número aleatório.
    for(int i = 0; i < linha; i++) {
        for(int j = 0; j < coluna; j++) {
            matriz[i][j] = distrib(gen); 
        }
    }

    //biblioteca fstream trabalhando.
    std::ofstream arquivo_saida(nomeArquivo);

    if(!arquivo_saida.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << nomeArquivo << std::endl;
        return;
    }

    arquivo_saida << linha << " " << coluna << std::endl;
    
    //Laco for para escrever no arquivo os numeros nas posicoes
    for(int i = 0; i < linha; i++) {
        for(int j = 0; j < coluna; j++){
            arquivo_saida << matriz[i][j] << "\t";  
        }
        arquivo_saida << std::endl;
    }

    std::cout << "Matriz " << linha << " por " << coluna << " criada e salva em " << nomeArquivo << std::endl;

}