#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura do nó
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Estrutura da lista
typedef struct Lista {
    Node* head;
} Lista;

// Função para criar a lista
void criarLista(Lista* lista) {
    lista->head = NULL;
}

// Função para inserir elementos em ordem crescente
void inserirLista(Lista* lista, int data) {
    Node* novo_node = (Node*)malloc(sizeof(Node));
    novo_node->data = data;
    novo_node->next = NULL;

    // Inserção no início ou quando a lista está vazia
    if (lista->head == NULL || lista->head->data >= novo_node->data) {
        novo_node->next = lista->head;
        lista->head = novo_node;
    } else {
        // Encontrar a posição correta para inserção
        Node* atual = lista->head;
        while (atual->next != NULL && atual->next->data < novo_node->data) {
            atual = atual->next;
        }
        novo_node->next = atual->next;
        atual->next = novo_node;
    }
}

// Função para exibir a lista
void exibirLista(Lista* lista) {
    Node* atual = lista->head;
    printf("Lista: ");
    while (atual != NULL) {
        printf("%d ", atual->data);
        atual = atual->next;
    }
    printf("\n");
}

// Função para verificar se a lista está vazia
bool verificarVazia(Lista* lista) {
    return lista->head == NULL;
}

// Função para buscar um elemento na lista
bool buscarLista(Lista* lista, int data) {
    Node* atual = lista->head;
    while (atual != NULL) {
        if (atual->data == data) {
            return true;
        }
        atual = atual->next;
    }
    return false;
}

// Função para excluir um elemento da lista
bool excluirLista(Lista* lista, int data) {
    Node* atual = lista->head;
    Node* anterior = NULL;

    while (atual != NULL && atual->data != data) {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL) {
        return false; // Elemento não encontrado
    }

    if (anterior == NULL) {
        lista->head = atual->next; // O elemento a ser removido é o primeiro
    } else {
        anterior->next = atual->next; // Remove o elemento
    }
    free(atual);
    return true;
}

// Função para liberar a lista
void liberarLista(Lista* lista) {
    Node* atual = lista->head;
    Node* temp;

    while (atual != NULL) {
        temp = atual;
        atual = atual->next;
        free(temp);
    }

    lista->head = NULL;
}

int main() {
    Lista lista;
    criarLista(&lista);

    // Inserindo elementos em ordem crescente
    inserirLista(&lista, 35);
    inserirLista(&lista, 15);
    inserirLista(&lista, 20);
    inserirLista(&lista, 50);

    exibirLista(&lista); // Saída: Lista: 15 20 35 50

    printf("A lista está vazia? %s\n", verificarVazia(&lista) ? "Sim" : "Não"); // Saída: Não
    printf("Elemento 20 encontrado? %s\n", buscarLista(&lista, 20) ? "Sim" : "Não"); // Saída: Sim

    excluirLista(&lista, 20);
    exibirLista(&lista); // Saída: Lista: 15 35 50

    liberarLista(&lista);
    printf("A lista está vazia? %s\n", verificarVazia(&lista) ? "Sim" : "Não"); // Saída: Sim

    return 0;
}