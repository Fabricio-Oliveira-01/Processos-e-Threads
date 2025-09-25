#include <iostream>
#include <cmath>
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
    int numProcessos = ceil((double) totalElementos / P); //Arredondamento para evitar que não hajam processos suficientes

    for(int i = 0; i < numProcessos; i++) { //Percorre todos os processos
        pid_t pid = fork();

        if (pid == 0) { //Processo filho
            auto tempoInicial = std::chrono::high_resolution_clock::now();

            int inicioElem = i * P; //Índice do primeiro elemento que o processo deve calcular
            int fimElem = std::min(inicioElem + P, totalElementos); //Índice do último elemento que o processo deve calcular
            //std::min aqui garante que o valor nunca ultrapasse o tamanho total da matriz resultado

            std::ofstream fout("Processo_" + std::to_string(i) + ".txt"); //Nome do arquivo
            fout << A.linhas << " " << B.colunas << std::endl; //Cabeçalho

            for(int j = inicioElem; j < fimElem; j++) {
                int linhaC = j / B.colunas;
                int colunaC = j % B.colunas;
                double valor = calcularElemento(A, B, linhaC, colunaC);
                fout << linhaC << " " << colunaC << " " << valor << std::endl;
            }

            auto tempoFinal = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> tempoTotal = tempoFinal - tempoInicial;
            fout << tempoTotal.count() << std::endl;

            fout.close();
            _exit(0);
        }
    }

    for(int i = 0; i < numProcessos; i++) { //Processo pai espera os processos filhos terminarem
        wait(NULL);
    }

    std::cout << "Cálculo concluído. Foram gerados " << numProcessos << " arquivos." << std::endl;
}