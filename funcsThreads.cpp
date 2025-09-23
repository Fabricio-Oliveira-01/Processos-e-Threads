#include "funcsThreads.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <pthread.h>

//Variaveis globais
std::vector<std::vector<int>> matriz1;
std::vector<std::vector<int>> matriz2;
std::vector<std::vector<int>> matriz_resultante;

bool arquivosDeMatriz(const std::string& nomeArquivo, std::vector<std::vector<int>>& matriz) {
    std::ifstream arquivo(nomeArquivo);
    if(!arquivo.is_open()) {
        return false;
    }

    int linhas, colunas;
    arquivo >> linhas >> colunas;

    //Alocacao de tamanho da matriz.
    matriz.resize(linhas, std::vector<int>(colunas));
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            arquivo >> matriz[i][j];
            }
        }

    arquivo.close();
    return true;
}


void* rotina_thread(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*)args;

    auto inicio = std::chrono::high_resolution_clock::now();

    for (int index = thread_args->start_index; index < thread_args->end_index; index++) {
        int linha = index / thread_args->num_colunas_res;
        int coluna = index % thread_args->num_colunas_res;

        int soma = 0;
        for (size_t k = 0; k < matriz1[0].size(); k++){
            soma += matriz1[linha][k] * matriz2[k][coluna];
        }
        matriz_resultante[linha][coluna] = soma;
    }

    auto fim = std::chrono::high_resolution_clock::now();
    auto duracao = std::chrono::duration_cast <std::chrono::milliseconds> (fim - inicio);
    long long tempo_ms = duracao.count();

    std::string nomeArquivoResultado = "Threat_" + std::to_string(thread_args->id) + ".txt" ;
    std::ofstream arquivo_saida(nomeArquivoResultado);

    for (int index = thread_args->start_index; index < thread_args->end_index; index++){
        int linha = index / thread_args->num_colunas_res;
        int coluna = index % thread_args->num_colunas_res;

        arquivo_saida << "c" << linha << "," << coluna << " " << matriz_resultante[linha][coluna] << std::endl;
    }

    arquivo_saida << tempo_ms << std::endl;
    arquivo_saida.close();

    delete thread_args;

    pthread_exit(NULL);
}