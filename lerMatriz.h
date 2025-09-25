#ifndef FUNCS_H
#define FUNCS_H

#include <vector>
#include <string>

struct Matriz {
    int linhas;
    int colunas;
    std::vector<std::vector<double>> valores;
};

Matriz lerMatriz(const std::string& nomeArquivo);

#endif