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
void X(Lista *lista);

int main(){
    Lista *lista;
    lista = criaLista();
    int t = 0;
    int numero;
    char letra;

    while(t == 0){

        scanf(" %c %d", &letra, &numero);
        fflush(stdin);

        if(letra == "I"){
            //scanf("%d", &numero);
            I(numero,lista);
        }
        else if(letra == "F"){
            //scanf("%d", &numero);
            F(numero,lista);
        }
        else if(letra == "P"){
            P(lista);
        }
        else if(letra == "D"){
            P(lista);
        }
        else if(letra == "X"){
            X(lista);
            t = 1;
        }


    }



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

    printf(" %d\n", numero);
    lista->tamanho++;

}



void F(int numero,Lista *lista){

    No *no;
    no = (No*)malloc(sizeof(No));

    if(lista->tamanho == 1){

        no->dado = numero;
        no->prox_no = NULL;
        lista->primeiro->prox_no = no;
        printf(" %d\n", numero);
        

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

    printf("%d\n", numero);
    lista->tamanho++;


}

void P(Lista *lista){

    No *no;
    no = (No*)malloc(sizeof(No));

    No *noAux;
    noAux = (No*)malloc(sizeof(No));
    int count = 0;
    no = lista->primeiro;


    for(int i = 0; i<lista->tamanho; i++){

        if(no->prox_no == NULL){

            printf("%d\n", no->dado);
            no = NULL;
            free(no);

            noAux = lista->primeiro;

            for(int j = 0; j<count; j++){

                if(j == (count-1)){

                    noAux->prox_no = NULL;
                    break;
                }

                noAux = noAux->prox_no;

            }
            lista->tamanho--;
            break;
        }              
        no = no->prox_no;
        count++;
    }

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

        noAux = lista->primeiro;
        lista->primeiro = noAux->prox_no;
        printf("%d\n", noAux->dado);
        free(noAux);
        
    }
    
    lista->tamanho--;

}

void X(Lista *lista){

    No *noAux;
    noAux = (No*)malloc(sizeof(No));
    noAux = lista->primeiro;

    for(int i = 0; i<lista->tamanho; i++){

        printf("%d\n", noAux->dado);

        noAux = noAux->prox_no;


    }

}