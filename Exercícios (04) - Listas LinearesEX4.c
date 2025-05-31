#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{

    struct No *proximo;
    struct No *back;
    int chave;
    int tempo;

}No;


typedef struct{

    No *primeiro;
    int tamanho;

}Lista;

void i(Lista *lista, int chave, int j, int tempo);
void r(Lista *lista, int chave, int tempo);
Lista *criaLista(void);

int main(){

    Lista *lista = criaLista();
    int *tempo;
    tempo = (int*)malloc(sizeof(int));
    tempo = 0;
    char linha_entrada[100]; // Buffer para ler a linha inteira
    char comando_char;
    int valor1, valor2;
    int itens_parseados;
    int t =0;

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
        } else {
            // Não foram 3 itens, tenta o formato CHAR NUM
            itens_parseados = sscanf(linha_entrada, " %c %d", &comando_char, &valor1);
            if (itens_parseados == 2) {

            } else {
                // Não foram 2 itens, tenta o formato CHAR (sem números)
                itens_parseados = sscanf(linha_entrada, " %c", &comando_char);
                if (itens_parseados == 1) {

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


Lista *criaLista(void){
    Lista *lista;
    lista = (Lista*)malloc(sizeof(Lista));

    lista->primeiro = NULL;
    lista->tamanho = 0;

    return lista;
}


void i(Lista *lista, int chave, int j, int tempo){

    No *no;
    no = (No*)malloc(sizeof(No));
    No *noAux;
    //noAux = (No*)malloc(sizeof(No));

    if(lista->tamanho == 0){

        no->chave = chave;
        no->proximo = NULL;
        no->back = NULL;
        no->tempo = tempo;
        lista->primeiro = no;
        lista->tamanho++;
        tempo++;

    }else{
        
        noAux = lista->primeiro;

        while(noAux->proximo != NULL){

            noAux = noAux->proximo;
        }

        if(noAux->proximo == NULL){

            no->chave = chave;
            no->proximo = NULL;
            no->back = NULL;
            no->tempo = tempo;
            noAux->proximo = no;
            tempo++;
            lista->tamanho++;

            if(j != 0){

                noAux = lista->primeiro;

                for(int i = 0; i < ((lista->tamanho)-1); i++){

                    if( i == ((lista->tamanho)-2)){
                        
                        no->back = noAux;
                        break;

                    }

                    noAux = noAux->proximo;

                }

            }



        }




    }



}


void r(Lista *lista, int chave, int tempo){

    No *no;
    no = (No*)malloc(sizeof(No));
    No *anterior = NULL;
    No *noAux;


    no = lista->primeiro;

    while(no->chave != chave){

        anterior = no;
        no = no->proximo;

    }

    if(no->chave == chave){


        if(no == lista->primeiro){

            lista->primeiro = no->proximo;
            no->proximo = NULL;
            noAux = lista->primeiro;
            lista->tamanho--;

            while(noAux != NULL){

                if(noAux->back == no){

                    noAux->back = NULL;

                }

                noAux = noAux->proximo;


            }

        }else{

            lista->tamanho--;
            anterior->proximo = no->proximo;
            no->proximo = NULL;

            noAux = lista->primeiro;

            while(noAux != NULL){

                if(noAux->back == no){

                    noAux->back = NULL;

                }

                noAux = noAux->proximo;


            }




        }


    }


}
