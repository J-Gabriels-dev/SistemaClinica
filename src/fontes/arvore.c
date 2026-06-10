#include <stdio.h>
#include <stdlib.h>

#include "../cabecalhos/arvore.h"

static NoArvore *criarNo(Paciente paciente) {
    NoArvore *novoNo = (NoArvore *) malloc(sizeof(NoArvore));

    if (novoNo == NULL) {
        printf("Erro ao alocar memoria para o paciente.\n");
        exit(1);
    }

    novoNo->paciente = paciente;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;

    return novoNo;
}

NoArvore *inserirPaciente(NoArvore *raiz, Paciente paciente, int *inseriu) {
    if (raiz == NULL) {
        *inseriu = 1;
        return criarNo(paciente);
    }

    if (paciente.cpf < raiz->paciente.cpf) {
        raiz->esquerda = inserirPaciente(raiz->esquerda, paciente, inseriu);
    } else if (paciente.cpf > raiz->paciente.cpf) {
        raiz->direita = inserirPaciente(raiz->direita, paciente, inseriu);
    } else {
        *inseriu = 0;
    }

    return raiz;
}

NoArvore *buscarPaciente(NoArvore *raiz, long long cpf, int *comparacoes) {
    if (raiz == NULL) {
        return NULL;
    }

    (*comparacoes)++;

    if (cpf == raiz->paciente.cpf) {
        return raiz;
    }

    if (cpf < raiz->paciente.cpf) {
        return buscarPaciente(raiz->esquerda, cpf, comparacoes);
    }

    return buscarPaciente(raiz->direita, cpf, comparacoes);
}

static NoArvore *encontrarMenor(NoArvore *raiz) {
    if (raiz == NULL || raiz->esquerda == NULL) {
        return raiz;
    }

    return encontrarMenor(raiz->esquerda);
}

NoArvore *removerPaciente(NoArvore *raiz, long long cpf, int *removeu) {
    NoArvore *temporario;

    if (raiz == NULL) {
        return NULL;
    }

    if (cpf < raiz->paciente.cpf) {
        raiz->esquerda = removerPaciente(raiz->esquerda, cpf, removeu);
    } else if (cpf > raiz->paciente.cpf) {
        raiz->direita = removerPaciente(raiz->direita, cpf, removeu);
    } else {
        *removeu = 1;

        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }

        if (raiz->esquerda == NULL) {
            temporario = raiz->direita;
            free(raiz);
            return temporario;
        }

        if (raiz->direita == NULL) {
            temporario = raiz->esquerda;
            free(raiz);
            return temporario;
        }

        temporario = encontrarMenor(raiz->direita);
        raiz->paciente = temporario->paciente;
        raiz->direita = removerPaciente(raiz->direita, temporario->paciente.cpf, removeu);
    }

    return raiz;
}

void listarPacientesEmOrdem(NoArvore *raiz) {
    if (raiz == NULL) {
        return;
    }

    listarPacientesEmOrdem(raiz->esquerda);
    printf("CPF: %lld | Nome: %s | Idade: %d | Telefone: %s\n",
           raiz->paciente.cpf,
           raiz->paciente.nomeCompleto,
           raiz->paciente.idade,
           raiz->paciente.telefone);
    listarPacientesEmOrdem(raiz->direita);
}

int contarPacientes(NoArvore *raiz) {
    if (raiz == NULL) {
        return 0;
    }

    return 1 + contarPacientes(raiz->esquerda) + contarPacientes(raiz->direita);
}

int calcularAltura(NoArvore *raiz) {
    int alturaEsquerda;
    int alturaDireita;

    if (raiz == NULL) {
        return 0;
    }

    alturaEsquerda = calcularAltura(raiz->esquerda);
    alturaDireita = calcularAltura(raiz->direita);

    if (alturaEsquerda > alturaDireita) {
        return alturaEsquerda + 1;
    }

    return alturaDireita + 1;
}

void liberarArvore(NoArvore *raiz) {
    if (raiz == NULL) {
        return;
    }

    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}
