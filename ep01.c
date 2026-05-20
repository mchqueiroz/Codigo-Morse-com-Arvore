#include <stdio.h>
#include <stdlib.h>

typedef struct node* link;

struct node{
    char key;
    link left;// .
    link right;// -
};


// Função auxiliar para alocar um novo nó vazio
link criarNo() {
    link novo = (link)malloc(sizeof(struct node));
    if (novo != NULL) {
        novo->key = '\0'; // Inicializa vazio (nó de passagem)
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

    for (const char* p = codigoMorse; *p != '\0'; p++) {
        if (*p == '.') {
            if (atual->left == NULL) {
                atual->left = criarNo();
            }
            atual = atual->left;
        } else if (*p == '-') {
            if (atual->right == NULL) {
                atual->right = criarNo();
            }
            atual = atual->right;
        }
    }
    atual->key = valor; // Atribui o caractere ao nó final
    return raiz; 
}


int main(){
    link tree = NULL;
    char linha[256];
    FILE *arquivo = fopen("morse.txt", "r");;

    while(fgets(linha, sizeof(linha), arquivo)){
        printf("Conteúdo lido: %s", linha);
        tree = inserirArvore(tree, linha[0], linha + 2); // Considerando que cada linha contém um único caractere e o código morse começa na terceira posição

    }

    return 0;
}