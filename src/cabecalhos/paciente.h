#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct {
    long long cpf;
    char nomeCompleto[100];
    int idade;
    char telefone[20];
} Paciente;

#endif
