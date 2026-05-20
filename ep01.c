#include <stdio.h>
#include <stdlib.h>

typedef struct node* link;

struct node{
    int key;
    link left;
    link right;
};


link inserirArvore(link raiz, int valor){
    if(raiz == NULL){
        link novoNO = (link) malloc(link);
        novoNO->key = valor;
        novoNO->left = NULL;
        novoNo->right = NULL;
    }
    // Se o valor for menor, vai para a subárvore esquerda
    if (valor < raiz->key) {
        raiz->left = inserirArvore(raiz->left, valor);
    }
    // Se o valor for maior, vai para a subárvore direita
    else if (valor > raiz->key) {
        raiz->right = inserirArvore(raiz->right, valor);
    }
    
    // Retorna o nó atualizado
    return raiz;
}


int main(){
    char linha[256];
    FILE *arquivo = fopen("morse.txt", "r");;

    while(fgets(linha, sizeof(linha), arquivo)){
        printf("Conteúdo lido: %s", linha);
        inserirArvore(raiz, linha);
    }



    return 0;
}