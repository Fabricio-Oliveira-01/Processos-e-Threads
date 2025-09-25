#ifndef FUNCSPROCESSOS_H
#define FUNCSPROCESSOS_H

#include "lerMatriz.h"

double calcularElemento(const Matriz& A, const Matriz& B, int linhas, int colunas);
void multProcessos(const Matriz& A, const Matriz& B, int P);

#endif