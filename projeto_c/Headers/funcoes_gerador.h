#ifndef GERADOR_H
#define GERADOR_H

int codigo[8];
char* left_code[10];
char* right_code[10];

int converter_string(char numero[]);
char *conversor_codigo();
int** preencher_codigo(char conversao[], int **imagem, int espacamento, int area, int altura);
void gerar(int** imagem, int dimensao_x, int dimensao_y, char nome[]);

#endif
