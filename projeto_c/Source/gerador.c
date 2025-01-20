#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h> //biblioteca do getopt
#include <ctype.h> //biblioteca do atoi
#include "../Headers/funcoes_comuns.h"
#include "../Headers/funcoes_gerador.h"

int main(int argc, char **argv){
    
    //definição das entradas padrão
    char *b; //código de barras
    char *e = "5"; //espacamento
    char *a = "4"; //pixels por area
    char *h = "100"; //altura
    char *n = "codigo_barras"; //nome
    int opt;
    opterr = 0; //desabilita mensagem de erro

    //caso nenhum dos argumentos necessários tenha sido passado
    if(argc < 2){
        printf("As entradas não foram recebidas!\n");
        return 1;
    }else if(strcmp(argv[1], "-b") != 0){
        printf("O código de barras não foi escrito!.\n");
        return 1;
    }
    
    char identificador[10], nome[50];
    char *conversao;
    int espacamento, area, altura, tamanho_linha;
    int resultado;
    int **imagem;
    int dimensao_x, dimensao_y;

    while ((opt = getopt (argc, argv, "b:e:a:h:n:")) != -1){ //getopt analisa argumentos de linha de comando

        switch (opt){
            case 'b':
                b = optarg;
                break;
            case 'e':
                e = optarg;
                break;
            case 'a':
                a = optarg;
                break;
            case 'h':
                h = optarg;
                break;
            case 'n':
                n = optarg;
                break;
            case '?':
                if (optopt == 'b' || optopt == 'e' || optopt == 'a' || optopt == 'h' || optopt == 'n'){ //verifica se alguma opção não recebeu argumento
                    fprintf(stderr, "A opcao -%c requer um argumento.\n", optopt);
                }else{
                    fprintf(stderr,"Uma ou mais opções inválidas!\n");
                }
                return 1;

            default:
                return 1;
        }
    }

    if(optind < argc){ //verifica se há argumentos a mais
        printf("Os argumentos recebidos apresentam um erro.\n");
        return 1;
    }
    

    espacamento = atoi(e); //atoi converte string para inteiros
    area = atoi(a);
    altura = atoi(h);
    strcpy(nome, n);
    strcat(nome, ".pbm");
    
    resultado = verificacao(b, codigo);
    if(resultado == 1){
        return 1;
    }
    
    conversao = conversor();

    //alocação da matriz imagem
    tamanho_linha = strlen(conversao);
    imagem = calloc(altura*area+(2*espacamento), sizeof(int*));
    if(imagem == NULL){
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    for(int i = 0; i < altura*area+(2*espacamento); i++){
        imagem[i] = calloc(tamanho_linha*area+(2*espacamento), sizeof(int));

        if(imagem[i] == NULL){
        printf("Erro ao alocar memória!\n");
        return 1;
        }
    }

    imagem = preencher_codigo(conversao, imagem, espacamento, area, altura);
    
    free(conversao);

    dimensao_x = (tamanho_linha*area)+2*espacamento; //largura final
    dimensao_y = altura+2*espacamento; //altura final

    gerar(imagem, dimensao_x, dimensao_y, nome);

    //liberação de memória alocada
    for(int i = 0; i < dimensao_x; i++){ 
        free(imagem[i]);
    }
    free(imagem);

    return 0;
}
