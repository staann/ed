#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do Nó
typedef struct No {
    struct No *proximo;
    struct No *back;
    int chave;
    int tempo; // Tempo em que este nó foi inserido
} No;

// Estrutura da Lista
typedef struct {
    No *primeiro;
    int tamanho;
} Lista;

// Protótipos das Funções
Lista* criaLista(void);
void insere_i(Lista *lista, int n_chave, int j_offset_back, int tempo_atual);
void remove_r(Lista *lista, int n_chave_remover);
void finaliza_f(Lista *lista);
void liberaLista(Lista *lista);

int main() {
    Lista *lista = criaLista();
    int tempo_global = 0; // Tempo global do sistema

    char linha_entrada[100];
    char comando_char;
    int valor1, valor2; // Para os parâmetros n e j (ou n para r)
    int itens_parseados;
    int loop_ativo = 1; // Controla o loop principal

    // Removido o "Digite os comandos:" para seguir o padrão de entrada de juízes online
    // printf("Digite os comandos:\n"); 

    while (loop_ativo) {
        if (fgets(linha_entrada, sizeof(linha_entrada), stdin) == NULL) {
            break; // EOF ou erro de leitura
        }
        linha_entrada[strcspn(linha_entrada, "\n")] = '\0'; // Remove newline

        // Tenta parsear CHAR INT INT (para comando 'i')
        itens_parseados = sscanf(linha_entrada, " %c %d %d", &comando_char, &valor1, &valor2);
        if (itens_parseados == 3) {
            if (comando_char == 'i') {
                insere_i(lista, valor1, valor2, tempo_global);
                tempo_global++;
            } else {
                // Comando com 3 parâmetros não reconhecido (ou erro de formato)
            }
        } else {
            // Tenta parsear CHAR INT (para comando 'r')
            itens_parseados = sscanf(linha_entrada, " %c %d", &comando_char, &valor1);
            if (itens_parseados == 2) {
                if (comando_char == 'r') {
                    remove_r(lista, valor1);
                    tempo_global++;
                } else {
                    // Comando com 2 parâmetros não reconhecido
                }
            } else {
                // Tenta parsear CHAR (para comando 'f')
                itens_parseados = sscanf(linha_entrada, " %c", &comando_char);
                if (itens_parseados == 1) {
                    if (comando_char == 'f') {
                        finaliza_f(lista);
                        loop_ativo = 0; // Termina o loop
                    } else {
                        // Comando com 1 parâmetro não reconhecido
                    }
                } else {
                    // Linha vazia ou formato completamente inválido
                }
            }
        }
    }

    liberaLista(lista); // Liberar toda a memória alocada
    // printf("Programa encerrado.\n"); // Opcional
    return 0;
}

Lista* criaLista(void) {
    Lista *lista = (Lista*)malloc(sizeof(Lista));
    if (lista == NULL) {
        perror("Falha ao alocar lista");
        exit(EXIT_FAILURE);
    }
    lista->primeiro = NULL;
    lista->tamanho = 0;
    return lista;
}

void insere_i(Lista *lista, int n_chave, int j_offset_back, int tempo_atual) {
    No *novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Falha ao alocar novo_no para insercao");
        return; // Ou exit(EXIT_FAILURE)
    }
    novo_no->chave = n_chave;
    novo_no->tempo = tempo_atual;
    novo_no->proximo = NULL;
    novo_no->back = NULL; // Padrão

    // Inserção sempre no fim
    if (lista->primeiro == NULL) {
        lista->primeiro = novo_no;
    } else {
        No *aux = lista->primeiro;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novo_no;
    }
    lista->tamanho++;

    // Configurar o ponteiro back
    if (j_offset_back > 0) {
        // O novo nó é o último, seu índice é (lista->tamanho - 1)
        // O nó alvo para back está 'j_offset_back' posições antes dele.
        int indice_alvo_back = (lista->tamanho - 1) - j_offset_back;

        if (indice_alvo_back >= 0) {
            No *no_para_back = lista->primeiro;
            int pos_atual = 0;
            while (no_para_back != NULL && pos_atual < indice_alvo_back) {
                no_para_back = no_para_back->proximo;
                pos_atual++;
            }
            if (no_para_back != NULL && pos_atual == indice_alvo_back) {
                novo_no->back = no_para_back;
            }
            // Se no_para_back for NULL ou pos_atual != indice_alvo_back,
            // significa que o índice alvo não foi encontrado (j_offset_back muito grande
            // em relação ao tamanho atual antes da inserção ou um erro lógico),
            // então novo_no->back permanece NULL.
        }
        // Se indice_alvo_back < 0, novo_no->back também permanece NULL.
    }
    // Se j_offset_back == 0, novo_no->back já é NULL.
}

void remove_r(Lista *lista, int n_chave_remover) {
    if (lista == NULL || lista->primeiro == NULL) {
        return; // Lista vazia, nada a remover
    }

    No *atual = lista->primeiro;
    No *anterior = NULL;

    // Encontra o primeiro nó com a chave n_chave_remover
    while (atual != NULL && atual->chave != n_chave_remover) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Se o nó não foi encontrado
    if (atual == NULL) {
        return; // Chave não encontrada na lista
    }

    // Nó a ser removido foi encontrado ('atual')
    No *no_removido = atual;

    // 1. Desconectar o nó da lista
    if (anterior == NULL) { // Removendo o primeiro nó
        lista->primeiro = atual->proximo;
    } else { // Removendo nó do meio ou do fim
        anterior->proximo = atual->proximo;
    }
    lista->tamanho--;

    // 2. Atualizar ponteiros 'back' de outros nós que apontavam para 'no_removido'
    No *aux_scanner = lista->primeiro;
    while (aux_scanner != NULL) {
        if (aux_scanner->back == no_removido) {
            aux_scanner->back = NULL;
        }
        aux_scanner = aux_scanner->proximo;
    }

    // 3. Liberar a memória do nó removido
    free(no_removido);
}

void finaliza_f(Lista *lista) {
    if (lista == NULL || lista->primeiro == NULL) {
        printf("-1\n");
        return;
    }

    No *no_atual_impressao = lista->primeiro;
    int primeiro_item_impresso = 0; // Flag para controlar o espaço inicial

    while (no_atual_impressao != NULL) {
        if (primeiro_item_impresso) {
            printf(" "); // Adiciona espaço antes do segundo nó em diante
        }

        printf("[%d,%d", no_atual_impressao->chave, no_atual_impressao->tempo);

        if (no_atual_impressao->back != NULL) {
            int pos_back = 0;
            No *scanner_pos_back = lista->primeiro;
            while (scanner_pos_back != NULL && scanner_pos_back != no_atual_impressao->back) {
                scanner_pos_back = scanner_pos_back->proximo;
                pos_back++;
            }
            // Se scanner_pos_back == no_atual_impressao->back, então a posição foi encontrada
            if (scanner_pos_back == no_atual_impressao->back) {
                 printf(",%d", pos_back);
            }
            // Se scanner_pos_back for NULL, o nó back não foi encontrado (não deveria acontecer
            // se a lista estiver consistente e back sempre apontar para nós na lista)
        }
        printf("]");
        primeiro_item_impresso = 1;
        no_atual_impressao = no_atual_impressao->proximo;
    }
    printf("\n"); // Nova linha ao final de toda a impressão
}

void liberaLista(Lista *lista) {
    if (lista == NULL) return;
    No *atual = lista->primeiro;
    No *proximo_no;
    while (atual != NULL) {
        proximo_no = atual->proximo;
        free(atual);
        atual = proximo_no;
    }
    free(lista);
}
