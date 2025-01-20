#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../Headers/funcoes_comuns.h"

char* left_code[] = {"0001101","0011001","0010011","0111101","0100011","0110001","0101111","0111011","0110111","0001011"};
char* right_code[] = {"1110010","1100110","1101100","1000010","1011100","1001110","1010000","1000100","1001000","1110100"};

int verificacao(char ident[], int codigo[]){
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
