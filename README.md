# PROJETO FINAL DE ITP

O projeto é dividido em duas partes:\
  -uma que recebe um padrão EAN-8 e gera um código de barras;\
  -uma que recebe um arquivo pbm que contem um código de barras e devolve o padrão EAN-8.\

## ⚙️ Executando os testes

### Gerador de código de barras
Para executar o programa de geração de código de barras, após inicializar os arquivos necessários para execução, você deve seguir os seguintes passos logo após o nome do seu programa:

Para escrever o padrão EAN-8, digite -b antes do argumento, por exemplo: -b 40170725\
Para definir os pixels por área, digite -a antes do argumento, por exemplo: -a 4\
Para definir a altura, digite -h antes do argumento, por exemplo: -h 100\
Para definir um nome para o seu arquivo pbm, digite -n antes do argumento, por exemplo: -n nome_do_arquivo

OBS: como as opções de pixels por área (a), altura (h) e nome (n) não são obrigatórias, caso você não queira defini-los, serão atribuidos valores padrão para cada elemento que não foi definido pelo usuário.

Agora, dando exemplos de como isso ficaria no terminal:\
nome_do_programa -b 40170725 -a 3 -h 80 -n projeto_c

nome_programa_c -b 78956247 -h 100

### Extrator de código de barras
Para executar o programa de extração de código de barras, após inicializar os arquivos necessários para execução, você deve seguir os seguintes passos logo após o nome do seu programa:

Adicione o nome do arquivo PBM; \
Caso outro argumento seja passado na linha de comando, o programa informará que o executável só utiliza o arquivo PBM e não apresentará funcionamento.

Agora, dando exemplos de como isso ficaria no terminal:\
programa.exe arquivo.pbm (CERTO)\
programa.exe abcde arquivo.pbm (ERRADO)\
programa.exe arquivo.pbm abcde (ERRADO)

## ✒️ Autores
Autores do projeto e README:

* **Yasmin Maria Lima Aires de Carvalho** - ([https://github.com/linkParaPerfil](https://github.com/yasmin-30))
* **Theo Campos Soares** - ([https://github.com/linkParaPerfil](https://github.com/TheoCamposSoares))
