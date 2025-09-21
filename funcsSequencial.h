#ifndef FUNCSSEQUENCIAL_H
#define FUNCSSEQUENCIAL_H

#include <vector>
#include <string>
#include <chrono>


struct Matriz {
    int linhas;
    int colunas;
    std::vector<std::vector<double>> valores;
};

Matriz lerMatriz(const std::string& nomeArquivo);
Matriz multSequencial(const Matriz& A, const Matriz& B);
void gerarMatrizSequencial(const Matriz& C, std::chrono::milliseconds tempoDeExecucao);

#endif