#ifndef FUNCSSEQUENCIAL_H
#define FUNCSSEQUENCIAL_H

#include <vector>
#include <string>
#include <chrono>
#include "lerMatriz.h"

Matriz multSequencial(const Matriz& A, const Matriz& B);
void gerarMatrizSequencial(const Matriz& C, std::chrono::milliseconds tempoDeExecucao);

#endif