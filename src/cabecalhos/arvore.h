#ifndef ARVORE_H
#define ARVORE_H

#include "paciente.h"

typedef struct NoArvore {
    Paciente paciente;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

NoArvore *inserirPaciente(NoArvore *raiz, Paciente paciente, int *inseriu);
NoArvore *buscarPaciente(NoArvore *raiz, long long cpf, int *comparacoes);
NoArvore *removerPaciente(NoArvore *raiz, long long cpf, int *removeu);
void listarPacientesEmOrdem(NoArvore *raiz);
int contarPacientes(NoArvore *raiz);
int calcularAltura(NoArvore *raiz);
void liberarArvore(NoArvore *raiz);

#endif
