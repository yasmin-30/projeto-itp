#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Headers/funcoes_extrator.h"
#include "../Headers/funcoes_comuns.h"
#define cabecalho_pbm "P1"


ImagemPBM *carregar_imagem(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) return NULL;

    // validar cabeçalho
    if (!validar_cabecalho(arquivo)) {
        fclose(arquivo);
        return NULL;
    }

    // alocação de memória da struct
    ImagemPBM *imagem = malloc(sizeof(ImagemPBM));
    if (!imagem) {
        fclose(arquivo);
        return NULL;
    }

    // ler largura e altura
    if (fscanf(arquivo, "%d %d", &imagem->largura, &imagem->altura) != 2) {
        free(imagem);
        fclose(arquivo);
        return NULL;
    }

    // alocação de memória para a matriz
    imagem->matriz = malloc(imagem->altura * sizeof(int *));
    if (!imagem->matriz) {
        free(imagem);
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < imagem->altura; i++) {
        imagem->matriz[i] = malloc(imagem->largura * sizeof(int));
        if (!imagem->matriz[i]) {
            // liberar memória em caso de erro
            for (int k = 0; k < i; k++) free(imagem->matriz[k]);
            free(imagem->matriz);
            free(imagem);
            fclose(arquivo);
            return NULL;
        }
    }

    // gerar matriz
    for (int i = 0; i < imagem->altura; i++) {
        char linha[imagem->largura + 1];
        fgets(linha, imagem->largura + 1, arquivo);
        
        for (int j = 0; j < imagem->largura; j++) {
            imagem->matriz[i][j] = linha[j] - '0';
        }
    }

    fclose(arquivo);
    return imagem;
}

int validar_cabecalho(FILE *arquivo) {
    char header[3];
    if (fscanf(arquivo, "%2s", header) != 1 || strcmp(header, cabecalho_pbm) != 0) {
        return 0; // Cabeçalho inválido
    }
    return 1;
}

int verificar_arquivo(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        fprintf(stderr, "Erro: O arquivo '%s' não existe ou não pode ser aberto.\n", nome_arquivo);
        return 0;
    }
    if (!validar_cabecalho(arquivo)) {
        fprintf(stderr, "Erro: O arquivo '%s' não é um arquivo PBM válido.\n", nome_arquivo);
        fclose(arquivo);
        return 0;
    }
    fclose(arquivo);
    return 1;
}

void liberar_imagem(ImagemPBM *imagem) {
    for (int i = 0; i < imagem->altura; i++) {
        free(imagem->matriz[i]);
    }
    free(imagem->matriz);
    free(imagem);
}

int verificar_sequencia(int *linha, int inicio, const char *sequencia, int largura_modulo) {
    int idx = 0;  // índice para acompanhar a posição na sequência
    for (int i = 0; i < strlen(sequencia); i++) {
        for (int j = 0; j < largura_modulo; j++) {
            if (linha[inicio + idx] != (sequencia[i] - '0')) {
                return 0;
            }
            idx++; // avançar para o próximo bit na sequência
        }
    }
    return 1;
}

int encontrar_codigo_barras(ImagemPBM *imagem) {
    int meio = imagem->altura / 2; 
    int largura_util = imagem->largura; 
    int largura_modulo = largura_util / 67; 

    if (largura_modulo <= 0) {
        return 0;
    }

    // largura do módulo
    for (int j = 0; j <= largura_util - 67 * largura_modulo; j++) {
        if (verificar_sequencia(imagem->matriz[meio], j, "101", largura_modulo) &&
            verificar_sequencia(imagem->matriz[meio], j + 3 * largura_modulo + 28 * largura_modulo, "01010", largura_modulo) &&
            verificar_sequencia(imagem->matriz[meio], j + 3 * largura_modulo + 28 * largura_modulo + 5 * largura_modulo + 28 * largura_modulo, "101", largura_modulo)) {
            return largura_modulo;
        }
    }
    return 0;
}

int decodificar_digito(const char *sequencia, int is_left) {
    const char **tabela = is_left ? L_CODE : R_CODE;
    for (int i = 0; i < 10; i++) {
        if (strcmp(sequencia, tabela[i]) == 0) {
            return i;
        }
    }
    return -1;
}

char *extrair_identificador(ImagemPBM *imagem) {
    int largura_modulo = encontrar_codigo_barras(imagem);
    if (largura_modulo == 0) return NULL;

    char *identificador = malloc(9 * sizeof(char));
    int indice = 0;

    int meio = imagem->altura / 2;

    for (int j = 0; j <= imagem->largura - 67 * largura_modulo; j++) {
        if (verificar_sequencia(imagem->matriz[meio], j, "101", largura_modulo)) {
            for (int k = 0; k < 4; k++) {
                char lcode[8] = {0};
                for (int m = 0; m < 7; m++) {
                    lcode[m] = imagem->matriz[meio][j + 3 * largura_modulo + k * 7 * largura_modulo + m * largura_modulo] + '0';
                }
                identificador[indice++] = '0' + decodificar_digito(lcode, 1);
            }
            for (int k = 0; k < 4; k++) {
                char rcode[8] = {0};
                for (int m = 0; m < 7; m++) {
                    rcode[m] = imagem->matriz[meio][j + 3 * largura_modulo + 28 * largura_modulo + 5 * largura_modulo + k * 7 * largura_modulo + m * largura_modulo] + '0';
                }
                identificador[indice++] = '0' + decodificar_digito(rcode, 0);
            }
            identificador[8] = '\0';
            return identificador;
        }
    }
    free(identificador);
    return NULL;
}
