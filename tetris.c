#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// Estrutura que define uma peça do jogo
typedef struct {
    char nome; 
    int id;
} Elemento;

// Estrutura que gerencia a fila circular inteira
typedef struct {
    Elemento itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// Protótipos das funções
void inicializarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
void inserir(Fila *f, Elemento p);
void remover(Fila *f, Elemento *p);
void mostrarFila(Fila *f);
void MenuJogo();

/* Ponto de partida do programa: apenas inicia o jogo */
int main() {
    MenuJogo();
    return 0;
}

/* Gerencia a interação com o usuário e as escolhas do menu */
void MenuJogo() {
    Fila f;
    Elemento p;
    inicializarFila(&f);
    int opcao;

    do {
        printf("\n-------- JOGO TETRIS STACK --------\n");
        mostrarFila(&f); 
        
        printf("01 - Jogar (Remover) a Peça\n");
        printf("02 - Inserir a Peça\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                if (filaVazia(&f)) {
                    printf("A fila já está vazia!\n");
                } else {
                    remover(&f, &p);
                    printf("Peça jogada: [%c %d]\n", p.nome, p.id);
                }
                break;

            case 2:
                if (filaCheia(&f)) {
                    printf("A fila já está cheia!\n");
                } else {
                    printf("Digite a letra da peça: ");
                    scanf(" %c", &p.nome);
                    printf("Digite o ID da peça: ");
                    scanf("%d", &p.id);
                    inserir(&f, p);
                }
                break;

            case 0:
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
                break;
        }
    } while(opcao != 0);
}
 
/* Prepara a fila zerando os índices e o contador de itens */
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

/* Informa se a fila atingiu o limite máximo de elementos */
int filaCheia(Fila *f) {
    return f->total == MAX;
}

/* Informa se a fila está completamente sem elementos */
int filaVazia(Fila *f) {
    return f->total == 0;
}

/* Insere uma nova peça no fim da fila de forma circular */
void inserir(Fila *f, Elemento p) {
    if (filaCheia(f)) {
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX; // Avança o índice do fim de forma circular
    f->total++;
}

/* Retira a peça mais antiga da fila (do início) de forma circular */
void remover(Fila *f, Elemento *p) {
    if (filaVazia(f)) {
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX; // Avança o índice do início de forma circular
    f->total--;
}

/* Percorre e exibe na tela todos os elementos ativos da fila */
void mostrarFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila atual: (vazia)\n");
        return;
    }

    printf("Fila atual: ");
    int idx = f->inicio;
    for (int i = 0; i < f->total; i++) {
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id); 
        idx = (idx + 1) % MAX; // Avança o índice de exibição de forma circular
    }
    printf("\n");
}
