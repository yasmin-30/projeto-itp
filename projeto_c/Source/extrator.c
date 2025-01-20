#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Headers/funcoes_extrator.h"
#include "../Headers/funcoes_comuns.h"
#define cabecalho_pbm "P1"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo_pbm>\n", argv[0]);
        return 1;
    }
    const char *nome_arquivo = argv[1];
    // verificar se o arquivo é válido
    if (!verificar_arquivo(nome_arquivo)) {
        return 1;
    }
    // carregar a imagem PBM
    ImagemPBM *imagem = carregar_imagem(nome_arquivo);
    if (!imagem) {
        fprintf(stderr, "Erro ao carregar a imagem PBM.\n");
        return 1;
    }
    // verificar se existe código
    if (!encontrar_codigo_barras(imagem)) {
        fprintf(stderr, "Código de barras não encontrado na imagem.\n");
        liberar_imagem(imagem);
        return 1;
    }
    // extrair o identificador
    char ident[8];
    extrair_identificador(imagem, ident);
    if (verificacao(ident, codigo) {
        printf("%s\n", ident);
    } else {
        fprintf(stderr, "Erro ao extrair o identificador do código de barras.\n");
    }
    liberar_imagem(imagem);
    return 0;
}
