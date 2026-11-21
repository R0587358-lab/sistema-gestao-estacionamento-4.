
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


void inicializarMapa(int mapa[FILEIRAS][COLUNAS]) {
    int i, j;
    for (i = 0; i < FILEIRAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            mapa[i][j] = 0;
        }
    }
}

int contarOcupadas(int mapa[FILEIRAS][COLUNAS]) {
    int i, j, total = 0;
    for (i = 0; i < FILEIRAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            if (mapa[i][j] == 1) {
                total++;
            }
        }
    }
    return total;
}

void exibirMapa(int mapa[FILEIRAS][COLUNAS]) {
    int i, j;

    printf("\n=== MAPA DE VAGAS ===\n");
    printf("   ");
    for (j = 0; j < COLUNAS; j++) {
        printf("C%d ", j + 1);
    }
    printf("\n");
    for (i = 0; i < FILEIRAS; i++) {
        printf("F%d ", i + 1);
        for (j = 0; j < COLUNAS; j++) {
            printf("%c  ", mapa[i][j] == 1 ? 'X' : '.');
        }
        printf("\n");
    }
    printf("Legenda: X = ocupada; . = livre\n");
}

int inicializarEstacionamento(Estacionamento *e) {
    inicializarMapa(e->mapa);
    e->quantidade = 0;
    e->capacidade = 0;
    e->veiculos = malloc(CAPACIDADE_INICIAL * sizeof(Veiculo));
    if (e->veiculos == NULL) {
        return 0;
    }
    e->capacidade = CAPACIDADE_INICIAL;
    return 1;
}

void liberarEstacionamento(Estacionamento *e) {
    free(e->veiculos);
    e->veiculos = NULL;
    e->quantidade = 0;
    e->capacidade = 0;
}

int ampliarCapacidade(Estacionamento *e) {
    int novaCapacidade = e->capacidade * 2;
    Veiculo *temporario = realloc(e->veiculos, novaCapacidade * sizeof(Veiculo));

    if (temporario == NULL) {
        return 0;
    }
    e->veiculos = temporario;
    e->capacidade = novaCapacidade;
    return 1;
}

int buscarVeiculo(const Estacionamento *e, const char *id) {
    int i;
    for (i = 0; i < e->quantidade; i++) {
        if (strcmp(e->veiculos[i].identificador, id) == 0) {
            return i;
        }
    }
    return -1;
}

int inserirVeiculo(Estacionamento *e, const Veiculo *novo) {
    if (e->quantidade >= TOTAL_VAGAS) {
        return INS_LOTADO;
    }
    if (!posicaoValida(novo->fileira, novo->coluna)) {
        return INS_POSICAO_INVALIDA;
    }
    if (!vagaLivre(e, novo->fileira, novo->coluna)) {
        return INS_VAGA_OCUPADA;
    }
    if (e->quantidade == e->capacidade) {
        if (!ampliarCapacidade(e)) {
            return INS_SEM_MEMORIA;
        }
    }
    e->veiculos[e->quantidade] = *novo;
    e->quantidade++;
    e->mapa[novo->fileira - 1][novo->coluna - 1] = 1;
    return INS_OK;
}

void removerVeiculoPorIndice(Estacionamento *e, int indice) {
    int i;
    Veiculo *v = &e->veiculos[indice];

    e->mapa[v->fileira - 1][v->coluna - 1] = 0;
    for (i = indice; i < e->quantidade - 1; i++) {
        e->veiculos[i] = e->veiculos[i + 1];
    }
    e->quantidade--;
}

int moverVeiculoPara(Estacionamento *e, int indice, int fileira, int coluna) {
    Veiculo *v = &e->veiculos[indice];

    if (!posicaoValida(fileira, coluna) || !vagaLivre(e, fileira, coluna)) {
        return 0;
    }
    e->mapa[v->fileira - 1][v->coluna - 1] = 0;
    e->mapa[fileira - 1][coluna - 1] = 1;
    v->fileira = fileira;
    v->coluna = coluna;
    return 1;
}

int contarCategoria(const Estacionamento *e, int categoria) {
    const Veiculo *p;
    int total = 0;

    for (p = e->veiculos; p < e->veiculos + e->quantidade; p++) {
        if (p->categoria == categoria) {
            total++;
        }
    }
    return total;
}



