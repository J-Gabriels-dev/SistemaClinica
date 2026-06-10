#include <stdio.h>

#include "../cabecalhos/sistema.h"
#include "../cabecalhos/arvore.h"

static long long lerCpf() {
    long long cpf;

    printf("CPF (somente numeros): ");
    scanf("%lld", &cpf);

    return cpf;
}

static Paciente lerDadosPaciente() {
    Paciente paciente;

    paciente.cpf = lerCpf();

    printf("Nome completo: ");
    scanf(" %99[^\n]", paciente.nomeCompleto);

    printf("Idade: ");
    scanf("%d", &paciente.idade);

    printf("Telefone de contato: ");
    scanf(" %19[^\n]", paciente.telefone);

    return paciente;
}

static void exibirPaciente(Paciente paciente) {
    printf("\nCPF: %lld\n", paciente.cpf);
    printf("Nome completo: %s\n", paciente.nomeCompleto);
    printf("Idade: %d\n", paciente.idade);
    printf("Telefone: %s\n", paciente.telefone);
}

static void exibirMenu() {
    printf("\n===== Sistema de Cadastro da Clinica =====\n");
    printf("1 - Cadastrar paciente\n");
    printf("2 - Buscar paciente por CPF\n");
    printf("3 - Excluir paciente por CPF\n");
    printf("4 - Listar pacientes em ordem crescente de CPF\n");
    printf("5 - Exibir quantidade de pacientes e altura da arvore\n");
    printf("0 - Encerrar\n");
    printf("Escolha uma opcao: ");
}

static void cadastrarPaciente(NoArvore **raiz) {
    Paciente paciente = lerDadosPaciente();
    int inseriu = 0;

    *raiz = inserirPaciente(*raiz, paciente, &inseriu);

    if (inseriu) {
        printf("\nPaciente cadastrado com sucesso.\n");
    } else {
        printf("\nCPF ja cadastrado. O paciente nao foi inserido.\n");
    }
}

static void consultarPaciente(NoArvore *raiz) {
    long long cpf = lerCpf();
    int comparacoes = 0;
    NoArvore *encontrado = buscarPaciente(raiz, cpf, &comparacoes);

    if (encontrado != NULL) {
        printf("\nPaciente encontrado.\n");
        exibirPaciente(encontrado->paciente);
    } else {
        printf("\nPaciente nao cadastrado.\n");
    }

    printf("Comparacoes realizadas: %d\n", comparacoes);
}

static void excluirPaciente(NoArvore **raiz) {
    long long cpf = lerCpf();
    int removeu = 0;

    *raiz = removerPaciente(*raiz, cpf, &removeu);

    if (removeu) {
        printf("\nPaciente removido com sucesso.\n");
    } else {
        printf("\nPaciente nao cadastrado.\n");
    }
}

static void listarPacientes(NoArvore *raiz) {
    if (raiz == NULL) {
        printf("\nNao ha pacientes cadastrados.\n");
        return;
    }

    printf("\nPacientes em ordem crescente de CPF:\n");
    listarPacientesEmOrdem(raiz);
}

static void exibirEstatisticas(NoArvore *raiz) {
    printf("\nTotal de pacientes cadastrados: %d\n", contarPacientes(raiz));
    printf("Altura da arvore: %d\n", calcularAltura(raiz));
}

void executarSistema() {
    NoArvore *raiz = NULL;
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        if (opcao == 1) {
            cadastrarPaciente(&raiz);
        } else if (opcao == 2) {
            consultarPaciente(raiz);
        } else if (opcao == 3) {
            excluirPaciente(&raiz);
        } else if (opcao == 4) {
            listarPacientes(raiz);
        } else if (opcao == 5) {
            exibirEstatisticas(raiz);
        } else if (opcao != 0) {
            printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberarArvore(raiz);
    printf("\nSistema encerrado. Memoria liberada.\n");
}

/*
Comentario final:
A busca na ABB tende a ser mais rapida que na lista original da clinica porque
ela nao precisa olhar todos os pacientes um por um em cada comparacao, o
sistema decide se deve continuar procurando pelo lado esquerdo ou pelo lado
direito da arvore, ignorando uma parte dos cadastros.

Essa vantagem pode ser perdida se os CPFs forem cadastrados em ordem crescente
ou em ordem decrescente nesse caso, a arvore fica parecida com uma lista,
com os pacientes praticamente enfileirados um depois do outro.

*/
