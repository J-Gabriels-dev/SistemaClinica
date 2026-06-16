#include <stdio.h>
#include <stdlib.h>

#include "../cabecalhos/arvore.h"

#include <stdio.h>
#include <stdlib.h>

#include "../cabecalhos/arvore.h"

// Função que cria um novo nó da árvore com os dados do paciente
static NoArvore *criarNo(Paciente paciente) {

    // Aloca memória para o novo nó
    NoArvore *novoNo = (NoArvore *) malloc(sizeof(NoArvore));

    // Verifica se a alocação foi realizada com sucesso
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria para o paciente.\n");
        exit(1);
    }

    // Armazena os dados do paciente no nó
    novoNo->paciente = paciente;

    // Inicializa os ponteiros dos filhos como NULL
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;

    return novoNo;
}

// Insere um paciente na árvore usando o CPF como chave
NoArvore *inserirPaciente(NoArvore *raiz, Paciente paciente, int *inseriu) {

    // Se a árvore estiver vazia, cria um novo nó
    if (raiz == NULL) {
        *inseriu = 1;
        return criarNo(paciente);
    }

    // CPF menor vai para a subárvore esquerda
    if (paciente.cpf < raiz->paciente.cpf) {
        raiz->esquerda = inserirPaciente(raiz->esquerda, paciente, inseriu);

    // CPF maior vai para a subárvore direita
    }else if (paciente.cpf > raiz->paciente.cpf) {
        raiz->direita = inserirPaciente(raiz->direita, paciente, inseriu);

    // CPF já existe na árvore
    } else {
        *inseriu = 0;
    }

    return raiz;
}

// Busca um paciente pelo CPF
NoArvore *buscarPaciente(NoArvore *raiz, long long cpf, int *comparacoes) {

    // Se não encontrou o paciente
    if (raiz == NULL) {
        return NULL;
    }

    // Conta uma comparação realizada
    (*comparacoes)++;

    // CPF encontrado
    if (cpf == raiz->paciente.cpf) {
        return raiz;
    }

    // Continua a busca na esquerda
    if (cpf < raiz->paciente.cpf) {
        return buscarPaciente(raiz->esquerda, cpf, comparacoes);
    }

    // Continua a busca na direita
    return buscarPaciente(raiz->direita, cpf, comparacoes);
}

// Encontra o nó com menor CPF da árvore
static NoArvore *encontrarMenor(NoArvore *raiz) {

    // Se não existir filho à esquerda, este é o menor nó
    if (raiz == NULL || raiz->esquerda == NULL) {
        return raiz;
    }

    // Continua procurando à esquerda
    return encontrarMenor(raiz->esquerda);
}

// Remove um paciente da árvore pelo CPF
NoArvore *removerPaciente(NoArvore *raiz, long long cpf, int *removeu) {

    NoArvore *temporario;

    // Árvore vazia
    if (raiz == NULL) {
        return NULL;
    }

    // Procura o nó a ser removido
    if (cpf < raiz->paciente.cpf) {
        raiz->esquerda = removerPaciente(raiz->esquerda, cpf, removeu);

    } else if (cpf > raiz->paciente.cpf) {
        raiz->direita = removerPaciente(raiz->direita, cpf, removeu);

    } else {

        // Nó encontrado
        *removeu = 1;

        // Caso 1: nó sem filhos
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }

        // Caso 2: nó com apenas filho à direita
        if (raiz->esquerda == NULL) {
            temporario = raiz->direita;
            free(raiz);
            return temporario;
        }

        // Caso 3: nó com apenas filho à esquerda
        if (raiz->direita == NULL) {
            temporario = raiz->esquerda;
            free(raiz);
            return temporario;
        }

        // Caso 4: nó com dois filhos
        // Procura o menor nó da subárvore direita
        temporario = encontrarMenor(raiz->direita);

        // Copia os dados do sucessor para o nó atual
        raiz->paciente = temporario->paciente;

        // Remove o sucessor da árvore
        raiz->direita = removerPaciente(
            raiz->direita,
            temporario->paciente.cpf,
            removeu
        );
    }

    return raiz;
}

// Lista os pacientes em ordem crescente de CPF
void listarPacientesEmOrdem(NoArvore *raiz) {

    if (raiz == NULL) {
        return;
    }

    // Visita a esquerda
    listarPacientesEmOrdem(raiz->esquerda);

    // Exibe os dados do paciente
    printf("CPF: %lld | Nome: %s | Idade: %d | Telefone: %s\n",
           raiz->paciente.cpf,
           raiz->paciente.nomeCompleto,
           raiz->paciente.idade,
           raiz->paciente.telefone);

    // Visita a direita
    listarPacientesEmOrdem(raiz->direita);
}

// Conta a quantidade total de pacientes cadastrados
int contarPacientes(NoArvore *raiz) {

    if (raiz == NULL) {
        return 0;
    }

    // Conta o nó atual + esquerda + direita
    return 1 + contarPacientes(raiz->esquerda)
             + contarPacientes(raiz->direita);
}

// Calcula a altura da árvore
int calcularAltura(NoArvore *raiz) {

    int alturaEsquerda;
    int alturaDireita;

    // Árvore vazia possui altura 0
    if (raiz == NULL) {
        return 0;
    }

    // Calcula altura das subárvores
    alturaEsquerda = calcularAltura(raiz->esquerda);
    alturaDireita = calcularAltura(raiz->direita);

    // Retorna a maior altura + 1
    if (alturaEsquerda > alturaDireita) {
        return alturaEsquerda + 1;
    }

    return alturaDireita + 1;
}

// Libera toda a memória utilizada pela árvore
void liberarArvore(NoArvore *raiz) {

    if (raiz == NULL) {
        return;
    }

    // Libera primeiro os filhos
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);

    // Libera o nó atual
    free(raiz);
}