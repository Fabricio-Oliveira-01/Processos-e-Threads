#include "funcsThreads.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <pthread.h>

//Aviso ao compilador, nao precisando definir novas variaveis dentro da main.
extern std::vector<std::vector<int>> matriz1;
extern std::vector<std::vector<int>> matriz2;
extern std::vector<std::vector<int>> matriz_resultante;

int main(int argc, char* argv[]) {

    if(argc != 4) {
        std::cerr << "Uso: ./thread <arquivo_matriz1> <arquivo_matriz2> <P>" << std::endl;
        return 1;
    }

    std::string nomeArquivo1 = argv[1];
    std::string nomeArquivo2 = argv[2];
    int P = std::stoi(argv[3]);

    if(!arquivosDeMatriz(nomeArquivo1, matriz1) || !arquivosDeMatriz(nomeArquivo2, matriz2)) {
        std::cerr << "Erro ao ler uma ou mais matrizes dos arquivos." << std::endl;
        return 1;
    }

    //Regra da multiplicacao de matrizes
    if(matriz1.empty() || matriz2.empty() || matriz1[0].size() != matriz2.size()) {
        std::cerr << "Erro: Matrizes nao sao compativeis para multiplicar ou estao vazias" << std::endl;
        return 1;
    }
    
    //Pega os tamanhos das matrizes, criando uma vazia para preencher com os threads.
    int n1 = matriz1.size();
    int m2 = matriz2[0].size();
    matriz_resultante.resize(n1, std::vector<int>(m2));

    //ceil busca o teto do numero. Aqui entra a formula n1*m2/P.
    int total_elementos = n1 * m2;
    int num_thread = ceil((double) total_elementos / P);
    if(num_thread == 0 && total_elementos > 0) {
        num_thread = 1;
    }

    //Array que guarda um identificador de Thread ao criar um array do tamanho total.
    std::cout << "Calculo iniciado com " << num_thread << " threads!." << std::endl;

    pthread_t threads[num_thread];

    for (int i = 0; i < num_thread; i++) {
        int start = i * P;
        int end = start + P;
        if(end > total_elementos) {
            end = total_elementos;
        }

        //Criacao e acesso aos ponteiros. Por estarem no struct do threads_funcoes.h, precisa.
        ThreadArgs* args = new ThreadArgs;
        args->id = i;
        args->start_index = start;
        args->end_index = end;
        args->num_colunas_res = m2;
        pthread_create(&threads[i], NULL, rotina_thread, (void*)args); //Achei importante pontuar. O for criar um novo thread, ou novo trabalho.
    }

    for (int i = 0; i < num_thread; i++) {
        pthread_join(threads[i], NULL);
    }

    std::cout << "Resultados salvos individualmente em arquivos separados!" << std::endl;
    return 0;
}