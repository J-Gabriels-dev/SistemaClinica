#include <stdio.h>
#include <stdlib.h>

#include "../cabecalhos/arvore.h"

static NoArvore *criarNo(Paciente paciente) {
    NoArvore *novoNo = (NoArvore *) malloc(sizeof(NoArvore));

    /* Se nao houver memoria disponivel, o cadastro nao pode continuar. */
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
    /* Quando chega em uma posicao vazia, cria o novo paciente ali. */
    if (raiz == NULL) {
        *inseriu = 1;
        return criarNo(paciente);
    }

    /* CPFs menores ficam a esquerda e CPFs maiores ficam a direita. */
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

    /* Conta quantos nos foram visitados ate encontrar ou encerrar a busca. */
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
    /* O menor valor de uma subarvore sempre esta mais a esquerda. */
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

        /* Caso 1: no folha, sem filhos. */
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }

        /* Caso 2: no com apenas o filho da direita. */
        if (raiz->esquerda == NULL) {
            temporario = raiz->direita;
            free(raiz);
            return temporario;
        }

        /* Caso 2: no com apenas o filho da esquerda. */
        if (raiz->direita == NULL) {
            temporario = raiz->esquerda;
            free(raiz);
            return temporario;
        }

        /* Caso 3: no com dois filhos, substituido pelo sucessor. */
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

    /* Percurso em ordem mostra os pacientes pelo CPF em ordem crescente. */
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

    /* Libera primeiro os filhos e depois o proprio no. */
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}
