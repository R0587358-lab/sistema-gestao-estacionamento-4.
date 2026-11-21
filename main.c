
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILEIRAS 4
#define COLUNAS 5
#define TOTAL_VAGAS (FILEIRAS * COLUNAS)

#define TAM_ID 7
#define TAM_DESC 60
#define CAPACIDADE_INICIAL 2
#define TAM_BUFFER 128

#define CARRO 1
#define MOTO 2

#define LEITURA_OK 1
#define LEITURA_FIM 0
#define LEITURA_LONGA 2

#define INS_OK 0
#define INS_LOTADO 1
#define INS_POSICAO_INVALIDA 2
#define INS_VAGA_OCUPADA 3
#define INS_SEM_MEMORIA 4

typedef struct {
    char identificador[TAM_ID + 1];
    char descricao[TAM_DESC + 1];
    int categoria;
    int fileira;
    int coluna;
} Veiculo;

typedef struct {
    int mapa[FILEIRAS][COLUNAS];
    Veiculo *veiculos;
    int quantidade;
    int capacidade;
} Estacionamento;

int lerLinha(char *destino, int tamanho) {
    size_t n;
    int c;

    if (fgets(destino, tamanho, stdin) == NULL) {
        destino[0] = '\0';
        return LEITURA_FIM;
    }

    n = strlen(destino);
    if (n > 0 && destino[n - 1] == '\n') {
        destino[n - 1] = '\0';
        n--;
        if (n > 0 && destino[n - 1] == '\r') {
            destino[n - 1] = '\0';
        }
        return LEITURA_OK;
    }

    if (feof(stdin)) {
        return LEITURA_OK;
    }
    while ((c = getchar()) != '\n' && c != EOF) {

    }
    return LEITURA_LONGA;
}

int converterInteiro(const char *texto, int *valor) {
    char *fim;
    long numero = strtol(texto, &fim, 10);

    if (fim == texto) {
        return 0;
    }
    while (*fim == ' ' || *fim == '\t') {
        fim++;
    }
    if (*fim != '\0') {
        return 0;
    }
    if (numero < -1000000L || numero > 1000000L) {
        return 0;
    }
    *valor = (int)numero;
    return 1;
}

int lerInteiro(const char *mensagem, int *valor) {
    char buffer[TAM_BUFFER];

    printf("%s", mensagem);
    if (lerLinha(buffer, TAM_BUFFER) != LEITURA_OK) {
        return 0;
    }
    return converterInteiro(buffer, valor);
}

void normalizarIdentificador(char *id) {
    int i;
    for (i = 0; id[i] != '\0'; i++) {
        if (id[i] >= 'a' && id[i] <= 'z') {
            id[i] = (char)(id[i] - 'a' + 'A');
        }
    }
}

int identificadorValido(const char *id) {
    int i;

    if (strlen(id) != TAM_ID) {
        return 0;
    }
    for (i = 0; i < TAM_ID; i++) {
        int letra = (id[i] >= 'A' && id[i] <= 'Z');
        int digito = (id[i] >= '0' && id[i] <= '9');
        if (!letra && !digito) {
            return 0;
        }
    }
    return 1;
}

int descricaoValida(const char *descricao) {
    size_t tamanho = strlen(descricao);
    size_t i;

    if (tamanho == 0 || tamanho > TAM_DESC) {
        return 0;
    }
    for (i = 0; i < tamanho; i++) {
        if (descricao[i] != ' ' && descricao[i] != '\t') {
            return 1;
        }
    }
    return 0;
}

int categoriaValida(int categoria) {
    if (categoria == CARRO) {
        return 1;
    }
    if (categoria == MOTO) {
        return 1;
    }
    return 0;
}

int posicaoValida(int fileira, int coluna) {
    return fileira >= 1 && fileira <= FILEIRAS &&
           coluna >= 1 && coluna <= COLUNAS;
}

int vagaLivre(Estacionamento *e, int fileira, int coluna) {
    if (!posicaoValida(fileira, coluna)) {
        return 0;
    }
    return e->mapa[fileira - 1][coluna - 1] == 0;
}

int lerIdentificador(const char *mensagem, char *buffer) {
    printf("%s", mensagem);
    if (lerLinha(buffer, TAM_BUFFER) != LEITURA_OK) {
        return 0;
    }
    normalizarIdentificador(buffer);
    return 1;
}


