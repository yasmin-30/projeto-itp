#ifndef FUNCOES_H
#define FUNCOES_H
#include <stdio.h>

typedef struct {
    int largura;
    int altura;
    int **matriz;
} ImagemPBM;

int codigo[8];

extern const char *L_CODE[10];
extern const char *R_CODE[10];

ImagemPBM *carregar_imagem(const char *nome_arquivo);

int validar_cabecalho(FILE *arquivo);

int verificar_arquivo(const char *nome_arquivo);

void liberar_imagem(ImagemPBM *imagem);

int verificar_sequencia(int *linha, int inicio, const char *sequencia, int largura_modulo);

int encontrar_codigo_barras(ImagemPBM *imagem);

int decodificar_digito(const char *sequencia, int is_left);

int extrair_identificador(ImagemPBM *imagem, char ident[]);

#endif // FUNCOES_H
