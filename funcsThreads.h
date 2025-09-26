#ifndef FUNCSTHREADS_H
#define FUNCSTHREADS_H

#include <vector>
#include <string>

struct ThreadArgs {
    int id;
    int start_index;
    int end_index;
    int num_colunas_res;
};

bool arquivosDeMatriz(const std::string& nomeArquivo, std::vector<std::vector<double>>& matriz);

void* rotina_thread(void* args);

#endif