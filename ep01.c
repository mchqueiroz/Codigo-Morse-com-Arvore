#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* link;

struct node{
    char key;
    link left;// .
    link right;// -
};

link criarNo() {
    link novo = (link)malloc(sizeof(struct node));
    if (novo != NULL) {
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

    for (const char* p = codigoMorse; *p != '\0'; p++) {// Percorre cada caractere do código Morse
        if (*p == '.') {// Se o caractere for '.', move para a subárvore esquerda
            if (atual->left == NULL) {
                atual->left = criarNo();
            }
            atual = atual->left;
        } else if (*p == '-') {// Se o caractere for '-', move para a subárvore direita
            if (atual->right == NULL) {
                atual->right = criarNo();
            }
            atual = atual->right;
        }
    }
    atual->key = valor;
    return raiz; 
}

char buscarArvore(link raiz, const char* codigoMorse){
    link atual = raiz;

    for (const char* p = codigoMorse; *p != '\0'; p++) {// Percorre cada caractere do código Morse
        if (*p == '.') {// Se o caractere for '.', move para a subárvore esquerda
            if (atual->left == NULL) {
                return '\0'; // Código Morse inválido
            }
            atual = atual->left;
        } else if (*p == '-') {// Se o caractere for '-', move para a subárvore direita
            if (atual->right == NULL) {
                return '\0'; // Código Morse inválido
            }
            atual = atual->right;
        }
    }
    return atual->key; // Retorna a letra correspondente ao código Morse
}


int main(){
    char linha[256];// Buffer para ler linhas do arquivo
    char entrada[100];// Buffer para ler a entrada do usuário
    char* tk[50];// Array de ponteiros para tokens (palavras) da entrada
    char letra;// Variável para armazenar a letra lida do arquivo
    char codigo[50];// Buffer para armazenar o código Morse lido do arquivo

    FILE *arquivo = fopen("morse.txt", "r");// Abre o arquivo para leitura
    link tree = NULL;// Inicializa a árvore como vazia

    tree = criarNo();// Cria o nó raiz da árvore

    for(int i = 0; i < 50; i++){ 
        tk[i] = NULL;
    }
 
    // Lê o arquivo linha por linha, extrai a letra e o código Morse, e insere na árvore
    while(fgets(linha, sizeof(linha), arquivo)){// Lê cada linha do arquivo
        if (sscanf(linha, " %c %s", &letra, codigo) == 2) {// Extrai a letra e o código Morse da linha
            printf("Lido: %c -> %s\n", letra, codigo);// Imprime a letra e o código Morse lidos para verificação
            tree = inserirArvore(tree, letra, codigo);// Insere a letra na árvore de acordo com o código Morse
        }
    }

    fclose(arquivo);

    printf("Digite o texto ou codigo Morse para processar: ");

    if(fgets(entrada, sizeof(entrada), stdin) != NULL) {
        // Remove a quebra de linha do final da string
        entrada[strcspn(entrada, "\n\r")] = '\0';

        // Usa APENAS o espaço como delimitador inicial
        char* token = strtok(entrada, " "); 
        int index = 0;

        printf("\nResultado da Traducao: ");
        
        while(token != NULL && index < 50) {
            tk[index] = token; 
            
            // Se o token for a barra, significa que terminou uma palavra.
            // Em vez de buscar na árvore, apenas imprimimos um espaço no texto normal.
            if (strcmp(tk[index], "/") == 0) {
                printf(" "); 
            } else {
                // Caso contrário, busca normalmente a sequência Morse na árvore
                char letraTraduzida = buscarArvore(tree, tk[index]);
                
                if (letraTraduzida != '\0') {
                    printf("%c", letraTraduzida);
                } else {
                    printf("?"); // Código inválido
                }
            }

            index++;
            token = strtok(NULL, " "); // Continua usando estritamente o espaço
        }
        printf("\n");

    }
    return 0;

}