#ifndef FUNCSSEQUENCIAL_H
#define FUNCSSEQUENCIAL_H

#include <vector>
#include <string>

struct Matriz {
    int linhas;
    int colunas;
    std::vector<std::vector<int>> valores;
};

Matriz lerMatriz(std::string nomeArquivo);
Matriz multSequencial(const Matriz& A, const Matriz& B);

#endif