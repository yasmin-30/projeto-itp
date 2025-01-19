#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../Headers/funcoes_gerador.h"

int codigo[8]; //variável global por ser usada em muitas funções

/*LEFT E RIGHT CODE - podem ser usados tanto para escanear (pega um conjunto de 7 digitos e compara com os do left ou right code para descobrir
o número, que será o índice de um dos vetores) quanto para gerar o código*/
char* left_code[] = {"0001101","0011001","0010011","0111101","0100011","0110001","0101111","0111011","0110111","0001011"};
char* right_code[] = {"1110010","1100110","1101100","1000010","1011100","1001110","1010000","1000100","1001000","1110100"};

//COLOCAR \n NOS TEXTOS
int verificacao(char ident[]){
    char aceitos[11] = "0123456789";
    int cont = 0;
    int multiplo, digito_verificador;
    float soma_ponderada = 0;

    if(strlen(ident) == 8){ //verifica se o identificador possui 8 digitos
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 10; j++){
                if(ident[i] == aceitos[j]){ //verifica se todos os digitos são números e converte de string para integer
                    cont++;
                    codigo[i] = j;
                }
            }
        }
    }else{
        printf("Identificador não possui 8 dígitos.\n");
        return 1;
    }
    
    if(cont != 8){
        printf("Identificador contém valores não numéricos.\n");
        return 1;
    }

    for(int i = 0; i < 7; i++){ //calcula a soma ponderada usada para calcular o digito verificador
        if(i%2==0){
            soma_ponderada += codigo[i]*3;
        }else{
            soma_ponderada += codigo[i];
        }
    }

    multiplo = soma_ponderada;
    if(multiplo%10 != 0){
        multiplo = ceil(soma_ponderada/10)*10;
    }

    digito_verificador = multiplo - soma_ponderada; 
    if(digito_verificador != codigo[7]){ //verifica se o digito verificador calculado é igual ao que aparece no identificador
        printf("O dígito verificador do identificador é inválido (não corresponde aos valores anteriores).\n");
        return 1;
    }else{
        return 0;
    }
}

char* conversor(){  
    char *conversao;
    conversao = calloc(67, sizeof(char));
    strcpy(conversao, "101"); //marca inicial  
    
    for(int i = 0; i < 8; i++){ //talvez colocar essa parte de formar a sequência em outra função
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