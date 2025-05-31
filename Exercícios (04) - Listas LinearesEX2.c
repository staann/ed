#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{

    struct No *prox_no;
    int dado;


}No;


typedef struct{

    No *primeiro;
    int tamanho;

}Lista;

Lista* criaLista(void);

void I(int numero,Lista *lista);
void F(int numero,Lista *lista);
void P(Lista *lista);
void D(Lista *lista);
int V(int numero, Lista *lista);
int E(int indice,Lista *lista);
void T(Lista *lista,int numero,int substituir);
int C(Lista *lista, int numero);
void X(Lista *lista);

int main(){
    Lista *lista = criaLista();
    int t = 0; // Flag para controlar o loop principal

    char linha_entrada[100]; // Buffer para ler a linha inteira
    char comando_char;
    int valor1, valor2;
    int itens_parseados;

    // bool alguma_saida_P_D_V = false; // Para a lógica da linha em branco do comando X

    printf("Digite os comandos:\n");

    while (t == 0) {
        if (fgets(linha_entrada, sizeof(linha_entrada), stdin) == NULL) {
            // Erro ao ler a linha ou fim do arquivo (EOF)
            break; // Sai do loop
        }

        // Remove o caractere de nova linha (\n) que fgets pode ter lido, se houver
        linha_entrada[strcspn(linha_entrada, "\n")] = '\0';

        // Tenta primeiro o formato com mais parâmetros: CHAR NUM NUM
        itens_parseados = sscanf(linha_entrada, " %c %d %d", &comando_char, &valor1, &valor2);

        if (itens_parseados == 3) {
            // Conseguiu ler um caractere e DOIS inteiros
            if (comando_char == 'T') { // Supondo que 'A' seja seu novo comando
                T(lista, valor1, valor2);
            } else {
                // fprintf(stderr, "Comando '%c' com dois números não reconhecido.\n", comando_char);
            }
        } else {
            // Não foram 3 itens, tenta o formato CHAR NUM
            itens_parseados = sscanf(linha_entrada, " %c %d", &comando_char, &valor1);
            if (itens_parseados == 2) {
                // Conseguiu ler um caractere e UM inteiro
                if (comando_char == 'I') {
                    I(valor1, lista); // Sua função I
                } else if (comando_char == 'F') {
                    F(valor1, lista); // Sua função F
                } else if (comando_char == 'V') {
                    int qtd_removida = V(valor1,lista); // Sua função V
                    printf("%d\n", qtd_removida);
                    // if (qtd_removida > 0) alguma_saida_P_D_V = true;
                }else if (comando_char == 'E') {
                    int posremovida = E(valor1,lista); // Sua função E
                    printf("%d\n", posremovida);
                    // if (qtd_removida > 0) alguma_saida_P_D_V = true;
                }else if (comando_char == 'C') {
                    int vezes = C(lista,valor1); // Sua função E
                    printf("%d\n", vezes);
                    // if (qtd_removida > 0) alguma_saida_P_D_V = true;
                }
                
                else {
                    // fprintf(stderr, "Comando '%c' com um número não reconhecido.\n", comando_char);
                }
            } else {
                // Não foram 2 itens, tenta o formato CHAR (sem números)
                itens_parseados = sscanf(linha_entrada, " %c", &comando_char);
                if (itens_parseados == 1) {
                    // Conseguiu ler apenas UM caractere
                    if (comando_char == 'P') {
                        P(lista); // Sua função P
                        // alguma_saida_P_D_V = true; (se P sempre produz saída ou modifica a lista)
                    } else if (comando_char == 'D') {
                        D(lista); // Sua função D (corrigida para chamar D)
                        // alguma_saida_P_D_V = true; (similar a P)
                    } else if (comando_char == 'X') {
                        // Lógica do comando X:
                        // if (alguma_saida_P_D_V) {
                        //     printf("\n");
                        // }
                        X(lista); // Sua função X deve ser corrigida para imprimir a lista
                        //printf("Comando X recebido. Saindo...\n"); // Placeholder
                        // Para realmente imprimir a lista aqui, sua função X precisa ser ajustada.
                        // Exemplo:
                        // if (alguma_saida_P_D_V_ocorreu) printf("\n");
                        // X_funcao_que_imprime_a_lista(lista);
                        t = 1; // Sinaliza para terminar o loop while
                    } else {
                        // fprintf(stderr, "Comando '%c' não reconhecido.\n", comando_char);
                    }
                } else {
                    // Linha vazia ou formato completamente inválido (não conseguiu ler nem o char)
                    // fprintf(stderr, "Entrada inválida ou linha vazia.\n");
                }
            }
        }
    }

    // free_lista_completa(lista); // Não se esqueça de liberar a lista no final
    printf("Programa encerrado.\n");
    return 0;
}


Lista* criaLista(void){

    Lista *lista;
    lista = (Lista*)malloc(sizeof(Lista));

    lista->primeiro = NULL;
    lista->tamanho = 0;

    return lista;

}


void I(int numero,Lista *lista){

    No *no;
    no = (No*)malloc(sizeof(No));

    no->dado = numero;
    no->prox_no = lista->primeiro;
    lista->primeiro = no;

    //printf(" %d\n", numero);
    //printf("\n");
    lista->tamanho++;

}
//#76,87,54,90


void F(int numero,Lista *lista){

    No *no;
    no = (No*)malloc(sizeof(No));

    if(lista->tamanho == 1){

        no->dado = numero;
        no->prox_no = NULL;
        lista->primeiro->prox_no = no;
        //printf("%d\n", numero);
        //printf("\n");

    }

    else if(lista->tamanho == 0){

        no->dado = numero;
        no->prox_no = lista->primeiro;
        lista->primeiro = no;
        

    }

    else{

        no = lista->primeiro;
        No *noAux;
        noAux = (No*)malloc(sizeof(No));

        for(int i = 0; i<lista->tamanho; i++){

            if(no->prox_no == NULL){

                noAux->dado = numero;
                noAux->prox_no = NULL;

                no->prox_no = noAux;

                break;
            }              
            no = no->prox_no;
        }
    }

    //printf("%d\n", numero);
    //printf("\n");
    lista->tamanho++;


}

void P(Lista *lista) {
    // 1. Tratar o caso de a própria lista não existir ou estar vazia
    if (lista == NULL || lista->primeiro == NULL) {
        // Não há nada para remover.
        // Você pode optar por imprimir uma mensagem de erro/aviso aqui,
        // dependendo dos requisitos do seu programa. Ex:
        // printf("Lista vazia, não é possível aplicar P.\n");
        return;
    }

    No *no_a_remover = lista->primeiro;
    No *anterior = NULL;

    // 2. Se a lista tem apenas UM elemento
    if (no_a_remover->prox_no == NULL) {
        printf("%d\n", no_a_remover->dado); // Imprime o valor do único elemento
        lista->primeiro = NULL;             // A lista agora está vazia
        free(no_a_remover);                 // Libera o nó
        lista->tamanho--;                   // Decrementa o tamanho
        return;
    }

    // 3. Se a lista tem MÚLTIPLOS elementos
    // Percorre a lista até que 'no_a_remover' seja o último nó.
    // 'anterior' irá rastrear o nó logo antes de 'no_a_remover'.
    while (no_a_remover->prox_no != NULL) {
        anterior = no_a_remover;
        no_a_remover = no_a_remover->prox_no;
    }

    // Neste ponto:
    // - 'no_a_remover' é o último nó da lista.
    // - 'anterior' é o penúltimo nó da lista.

    printf("%d\n", no_a_remover->dado); // Imprime o valor do último elemento

    if (anterior != NULL) { // Verificação de segurança, mas neste fluxo, anterior não será NULL
        anterior->prox_no = NULL; // O penúltimo nó agora se torna o último
    }
    free(no_a_remover);       // Libera o nó que era o último
    lista->tamanho--;           // Decrementa o tamanho
}


void D(Lista *lista){

    No *noAux;
    noAux = (No*)malloc(sizeof(No));

    if(lista->tamanho == 1){

        noAux = lista->primeiro;
        printf("%d\n", noAux->dado);
        free(noAux);
        lista->primeiro = NULL;

    }

    else{

        noAux = lista->primeiro->prox_no;
        printf("%d\n", lista->primeiro->dado);
        lista->primeiro->prox_no = NULL;
        lista->primeiro = noAux;
        //lista->primeiro->prox_no = NULL;
        //lista->primeiro = noAux;
        //printf("%d\n", noAux->dado);
        //free(noAux);
        
    }
    
    lista->tamanho--;

}

void X(Lista *lista){

    

    No *noAux;
    noAux = (No*)malloc(sizeof(No));
    noAux = lista->primeiro;
    printf("\n");

    for(int i = 0; i<lista->tamanho; i++){

        printf("%d\n", noAux->dado);

        noAux = noAux->prox_no;


    }

    exit(0);
}


int V(int valor_a_remover,Lista *lista) {
    if (lista == NULL || lista->primeiro == NULL) {
        return 0; // Lista não existe ou está vazia, nada a remover.
    }

    No *atual = lista->primeiro;
    No *anterior = NULL;
    int contador_removidos = 0;

    while (atual != NULL) {
        if (atual->dado == valor_a_remover) {
            No *no_para_remover = atual; // Guarda o nó a ser removido

            if (anterior == NULL) { // Removendo o nó cabeça (primeiro da lista)
                lista->primeiro = atual->prox_no;
                atual = lista->primeiro; // Avança 'atual' para o novo primeiro
            } else { // Removendo nó do meio ou do fim
                anterior->prox_no = atual->prox_no;
                atual = atual->prox_no; // Avança 'atual', 'anterior' permanece
            }

            free(no_para_remover);
            lista->tamanho--;
            contador_removidos++;
        } else {
            // O nó atual não corresponde ao valor, então avançamos os ponteiros
            anterior = atual;
            atual = atual->prox_no;
        }
    }
    return contador_removidos;
}






int E(int indice,Lista *lista){


    if (lista == NULL || lista->primeiro == NULL) {
        return 0; // Lista não existe ou está vazia, nada a remover.
    }

    No *atual = lista->primeiro;
    No *anterior = NULL;
    int contador = 1;
    int removido = 0;


    while (atual!= NULL){

        if(contador == indice){
            No *no_para_remover = atual;
            removido = no_para_remover->dado;

            if (anterior == NULL) { // Removendo o nó cabeça (primeiro da lista)
                lista->primeiro = atual->prox_no;
                atual = lista->primeiro; // Avança 'atual' para o novo primeiro
            } else { // Removendo nó do meio ou do fim
                anterior->prox_no = atual->prox_no;
                atual = atual->prox_no; // Avança 'atual', 'anterior' permanece
            }  //2 , 3 ,5 ,7 8
            //removido = no_para_remover->dado;
            free(no_para_remover);
            lista->tamanho--;
            //atual = NULL;
            return removido;
        } else {
            // O nó atual não corresponde ao valor, então avançamos os ponteiros
            anterior = atual;
            atual = atual->prox_no;
            contador++;
        }

    }

    return removido;
}


void T(Lista *lista, int numero, int substituir){

    if (lista == NULL || lista->primeiro == NULL) {
        // Lista não existe ou está vazia, nada a remover.
    }

    No *atual = lista->primeiro;


    while (atual!= NULL){

        if(atual->dado == numero){


            atual->dado = substituir;
            atual = NULL;
        } else {
            // O nó atual não corresponde ao valor, então avançamos os ponteiros
            atual = atual->prox_no;
        }

    }


}



int C(Lista *lista, int numero){


    int contador = 0;
    if (lista == NULL || lista->primeiro == NULL) {
        return contador;
        // Lista não existe ou está vazia, nada a remover.
    }

    No *atual = lista->primeiro;

    while (atual!= NULL){

        if(atual->dado == numero){

            contador++;

        } 
        
            // O nó atual não corresponde ao valor, então avançamos os ponteiros
        atual = atual->prox_no;
    

    }
    return contador;


}
