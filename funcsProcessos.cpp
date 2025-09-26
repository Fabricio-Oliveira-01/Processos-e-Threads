#include <iostream>
#include <cmath>
#include <algorithm>
#include <unistd.h>
#include <chrono>
#include <fstream>
#include <sys/wait.h>

#include "funcsProcessos.h"

double calcularElemento(const Matriz& A, const Matriz& B, int linhaC, int colunaC) {
    double soma = 0.0;
    for(int i = 0; i < A.colunas; i++) {
        soma += A.valores[linhaC][i] * B.valores[i][colunaC];
    }
    return soma;
}

void multProcessos(const Matriz& A, const Matriz& B, int P) {
    int totalElementos = A.linhas * B.colunas;
    int numProcessos = ceil((double) totalElementos / P); // Usa ceil para arredondar para cima e garantir que todos os elementos sejam cobertos

    for(int i = 0; i < numProcessos; i++) { //Percorre todos os processos
        pid_t pid = fork();

        if (pid == 0) { //Processo filho
            auto tempoInicial = std::chrono::high_resolution_clock::now();

            int inicioElem = i * P; //Índice do primeiro elemento que o processo deve calcular
            int fimElem = inicioElem + P;
            if (fimElem > totalElementos) { //Garante que o fim não ultrapassa o valor total de elementos
                fimElem = totalElementos;
            }

            std::ofstream arquivoResultado("Processo_" + std::to_string(i) + ".txt");

            // Cabeçalho: dimensões da matriz resultado
            arquivoResultado << A.linhas << " " << B.colunas << std::endl;

            for (int j = inicioElem; j < fimElem; j++) {
                int linhaC = j / B.colunas;
                int colunaC = j % B.colunas;
                double valor = calcularElemento(A, B, linhaC, colunaC);
                arquivoResultado << "c" << (linhaC + 1) << (colunaC + 1) << " " << valor << std::endl;
            }

            auto tempoFinal = std::chrono::high_resolution_clock::now();

            auto tempoDeExecucao = std::chrono::duration_cast<std::chrono::milliseconds>(tempoFinal - tempoInicial);
            arquivoResultado << tempoDeExecucao.count() << std::endl;

            arquivoResultado.close();
            _exit(0);
        }
    }

    for(int i = 0; i < numProcessos; i++) { //Processo pai espera os processos filhos terminarem
        wait(NULL);
    }

    std::cout << "Cálculo concluído. Foram gerados " << numProcessos << " arquivos." << std::endl;
}