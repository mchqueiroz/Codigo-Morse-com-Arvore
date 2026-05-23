/*
----------------------------------------------------------------------
                        TRABALHO DE EDA, EP 01

INTEGRANTES:
Leonardo Rodrigues Batista - RA: 845971
Beatriz de Oliveira Franca - RA: 847155
Vitor Matheus Oliveira Usar - RA: 845250
Michael Queiroz Cardoso - RA: 845062
----------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARACTERES_ENTRADA 1000

typedef struct node* link;

struct node{
    char key;
    link left; // .
    link right; // -
};

link criarNo() {
    link novo = (link)malloc(sizeof(struct node));
    if (novo != NULL){
        novo->key = '\0';
        novo->left = NULL;
        novo->right = NULL;
    }
    return novo;
}

link inserirArvore(link raiz, char valor, const char* codigoMorse){
    if (raiz == NULL) {
        raiz = criarNo();
    }

    link atual = raiz;

    for (const char* p = codigoMorse; *p != '\0'; p++){ // Percorre cada caractere do codigo Morse
        if (*p == '.'){ // Se o caractere for '.', move para a subarvore esquerda
            if (atual->left == NULL) {
                atual->left = criarNo();
            }
            atual = atual->left;
        } else if (*p == '-'){ // Se o caractere for '-', move para a subarvore direita
            if (atual->right == NULL) {
                atual->right = criarNo();
            }
            atual = atual->right;
        }
    }
    atual->key = valor;
    return raiz; 
}

link inicializarArvoreMorse(link raiz){
    FILE *arquivo = fopen("morse.txt", "r"); // Abre o arquivo para leitura

    char linha[10]; // Buffer para ler linhas do arquivo
    char letra; // Variavel para armazenar a letra lida do arquivo
    char codigo[50]; // Buffer para armazenar o codigo Morse lido do arquivo

    // Le o arquivo linha por linha, extrai a letra e o codigo Morse, e insere na arvore
    while(fgets(linha, sizeof(linha), arquivo)){ // Le cada linha do arquivo
        if (sscanf(linha, " %c %s", &letra, codigo) == 2){ // Extrai a letra e o codigo Morse da linha
            raiz = inserirArvore(raiz, letra, codigo); // Insere a letra na arvore de acordo com o codigo Morse
        }
    }

    fclose(arquivo);

    return raiz;
}

void imprimirPreOrdem(link raiz, char* string, int sizeString){
    if (raiz == NULL) // arvore ou subarvore vazia
        return;

    if (string == NULL){
        char* novaString = (char*)malloc(5 * sizeof(char)); // string que guarda o codigo Morse do caractere do no
        for (int i=0; i < 5; i++){
            novaString[i] = ' ';
        }
        novaString[0] = '.';
        imprimirPreOrdem(raiz->left, novaString, sizeString + 1);
    
        novaString[0] = '-';
        imprimirPreOrdem(raiz->right, novaString, sizeString + 1);

        free(novaString);
    } else{
        for (int i=sizeString; i < 5; i++) // como "string" eh um ponteiro, outras funcoes concorrentes podem
            string[i] = ' ';               // altera-la antes de um no printar, portanto esse "for" evita
                                           // prints errados com "." ou "-" extras.
                        
        for(int i=0; i < sizeString - 1; i++){
            printf("    |");
        }

        printf("\'");
        for(int i=0; i < 5; i++){
            if (i == 4)
                printf("%c",  string[i]);
            else
                printf("%c ", string[i]);
        }
        printf("\'");
        if (raiz->key != '\0')
            printf(" -> %c\n", raiz->key);
        else
            printf("\n");
        
        string[sizeString] = '.'; // vai pra esquerda, adiciona um "." ao codigo Morse
        imprimirPreOrdem(raiz->left, string, sizeString + 1);
    
        string[sizeString] = '-'; // vai pra direita, adiciona um "-" ao codigo Morse
        imprimirPreOrdem(raiz->right, string, sizeString + 1);
    }
}

char buscarArvore(link raiz, const char* codigoMorse){
    link atual = raiz;

    for (const char* p = codigoMorse; *p != '\0'; p++){ // Percorre cada caractere do codigo Morse
        if (*p == '.'){ // Se o caractere for '.', move para a subarvore esquerda
            if (atual->left == NULL){
                return '\0'; // Código Morse invalido
            }
            atual = atual->left;
        } else if (*p == '-'){ // Se o caractere for '-', move para a subarvore direita
            if (atual->right == NULL){
                return '\0'; // Codigo Morse invalido
            }
            atual = atual->right;
        }
    }
    return atual->key; // Retorna a letra correspondente ao codigo Morse
}

void traduzirLetra(link raiz, char letra, char* string, int sizeString, int* achou){
    if (raiz == NULL)
        return;

    // funcionamento dessa funcao inteira eh identico ao "imprimirPreOrdem", percorrendo toda a arvore
    // ate encontrar a letra necessaria, enquanto monta a string do codigo Morse pra cada letra. Para evitar
    // um desempenho pior, ela tem uma variavel (que eh um ponteiro), para avisar pra posteriores recursoes
    // se a letra jah nao foi encontrada, evitando procura extras desnecessarias.
    if (achou == NULL){
        int* boolAchou = (int*)malloc(sizeof(int));
        *boolAchou = 0;
        achou = boolAchou;
    }
    if (*achou == 1)
        return;

    if (string == NULL){
        char* novaString = (char*)malloc(5 * sizeof(char)); // string que guarda o codigo-morse do caractere do no
        for (int i=0; i < 5; i++){
            novaString[i] = ' ';
        }
        novaString[0] = '.';
        traduzirLetra(raiz->left, letra, novaString, sizeString + 1, achou);
    
        novaString[0] = '-';
        traduzirLetra(raiz->right, letra, novaString, sizeString + 1, achou);

        free(novaString);
        free(achou);
    } else{
        
        for (int i=sizeString; i < 5; i++)
            string[i] = '\0';
        
        if (raiz->key == letra){
            *achou = 1;
            for (int i=0; i < 5; i++)
                printf("%c", string[i]);
            return;
        }
        
        string[sizeString] = '.';
        traduzirLetra(raiz->left, letra, string, sizeString + 1, achou);
    
        string[sizeString] = '-';
        traduzirLetra(raiz->right, letra, string, sizeString + 1, achou);
    }
}

void traduzirAlfanumerico(char* entrada, link raiz){
    for(int i = 0; entrada[i] != '\0'; i++){
        if (entrada[i] == ' ') {
            printf(" / "); //espaço em morse é barra
        } else {
            traduzirLetra(raiz, entrada[i], NULL, 0, NULL);
            printf(" ");
        }
    }
}

void traduzirMorse(char* entrada, link raiz){
    char* tk[50]; // Array de ponteiros para tokens (palavras) da entrada
    for(int i = 0; i < 50; i++){ 
        tk[i] = NULL;
    }
    
    // Usa APENAS o espaço como delimitador inicial
    char* token = strtok(entrada, " "); 
    int index = 0;
    while(token != NULL && index < 50) {
        tk[index] = token; 
        
        // Se o token for a barra, significa que terminou uma palavra
        // Em vez de buscar na arvore, apenas imprimimos um espaço no texto normal
        if (strcmp(tk[index], "/") == 0) {
            printf(" "); 
        } else {
            // Caso contrario, busca normalmente a sequencia Morse na arvore
            char letraTraduzida = buscarArvore(raiz, tk[index]);
            
            if (letraTraduzida != '\0') {
                printf("%c", letraTraduzida);
            } else {
                printf("?"); // Código inválido
            }
        }

        index++;
        token = strtok(NULL, " "); // Continua usando estritamente o espaço
    }
}

void traduzirEntrada(FILE* arquivo, link raiz){ // se lendo um arquivo, "entrada" == NULL. Se lendo a entrada-padrao, "arquivo" == NULL
    char entrada[MAX_CARACTERES_ENTRADA];
    if (arquivo != NULL){
        fgets(entrada, MAX_CARACTERES_ENTRADA, arquivo);
        entrada[strlen(entrada)] = '\0';
    }

    printf("\nResultado da Traducao de \"%s\": ", entrada);

    if ((entrada[0] >= 65 && entrada[0] <= 90) || (entrada[0] >= 48 && entrada[0] <= 57)) // entrar para traduzir para morse
        traduzirAlfanumerico(entrada, raiz);
    else
        traduzirMorse(entrada, raiz);

    printf("\n");
}

int main(){
    link arvore = NULL; // Arvore vazia

    arvore = inicializarArvoreMorse(arvore); // Inicializa a arvore Morse

    imprimirPreOrdem(arvore, NULL, 0); // imprimir a arvore Morse em pre-ordem

    printf("Você deseja ler uma entrada da entrada-padrão (digite 1) ou de um arquivo (digite 2)? ");
    int resp;
    scanf("%d\n", &resp);

    char entrada[MAX_CARACTERES_ENTRADA];
    if (resp == 1){
        printf("\nDigite o texto ou codigo Morse para processar: ");
        traduzirEntrada(stdin, arvore);
    } else{
        printf("Digite o nome do arquivo para processar, incluindo o \".txt\": ");
        
        scanf("\n%s", entrada);
        FILE* arquivo = fopen(entrada, "r");
        traduzirEntrada(arquivo, arvore);
        fclose(arquivo);
    }
    
    return 0;

}