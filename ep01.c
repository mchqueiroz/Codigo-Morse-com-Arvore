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
    atual->key = valor;
    return raiz; 
}


int main(){
    link tree = NULL;
    char linha[256];
    FILE *arquivo = fopen("morse.txt", "r");;

    tree = criarNo();

    char letra;
    char codigo[50];

    while(fgets(linha, sizeof(linha), arquivo)){
        if (sscanf(linha, " %c %s", &letra, codigo) == 2) {
            printf("Lido: %c -> %s\n", letra, codigo);
            tree = inserirArvore(tree, letra, codigo);
        }
    }

    fclose(arquivo);

    return 0;
}

