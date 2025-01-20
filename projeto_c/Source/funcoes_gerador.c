#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../Headers/funcoes_comuns.h"
#include "../Headers/funcoes_gerador.h"

int codigo[8]; //variável global por ser usada em muitas funções

char* conversor(){  
    char *conversao;
    conversao = calloc(67, sizeof(char));
    strcpy(conversao, "101"); //marca inicial  
    
    for(int i = 0; i < 8; i++){
        if(i < 4){
            strcat(conversao, left_code[codigo[i]]);
        }else{
            if(i == 4){
                strcat(conversao, "01010"); //marca central
            }

            strcat(conversao, right_code[codigo[i]]);
        }
    }
    strcat(conversao, "101"); //marca final
    
    return conversao;
}

int** preencher_codigo(char conversao[], int **imagem, int espacamento, int area, int altura){
    int linha = strlen(conversao);

    for(int i = espacamento; i < altura+espacamento; i++){
        int localizacao = 0;
        
        for(int j = espacamento; j < (linha*area)+espacamento; j+=area){

            if(conversao[localizacao] == '1'){
                for(int k = 0; k < area; k++){
                    imagem[i][j+k] = 1;
                }
            }
  
            localizacao += 1;
        }
    }
    return imagem;
}

void gerar(int** imagem, int dimensao_x, int dimensao_y, char nome[]){
    FILE *fp;
    fp = fopen(nome, "r");
    
    if(fp != NULL){
        char resposta[3];
        
        printf("O arquivo já existe! Posso sobrescrevê-lo? (sim/não)\n");
        scanf(" %s", resposta);

        if(resposta[0] == 'n'){
            printf("Arquivo resultante já existe!\n");
            
            for(int i = 0; i < dimensao_x; i++){ //liberação de memória alocada
                free(imagem[i]);
            }
            free(imagem);

            exit(1);
        }
    }

    fp = fopen(nome, "w+");
    
    fprintf(fp,"P1\n");
    fprintf(fp,"%d %d\n", dimensao_x, dimensao_y);

    for(int line = 0; line < dimensao_y; line++){
        for(int col = 0; col < dimensao_x; col++){
            fprintf(fp, "%d", imagem[line][col]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}
