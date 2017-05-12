#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50

/*------------------------------------------------------------Estruturas------------------------------------------------------------*/
struct dim_produto{
	int id, numeracao, quantidade;
    char nome[TAM];
    char tipo[TAM];
    char modelo[TAM];
    //float preco;
	struct dim_produto *prox;
};
typedef struct dim_produto dim_produto;

struct dim_cliente{
	char nome[TAM];
	long int rg;
	char endereco[TAM];
    int telefone;
    int totalCompras;

	struct dim_cliente *prox;
};
typedef struct dim_cliente dim_cliente;







/*---------------------------------------------------------------------------------------------------------------------------------*/


int main(){

        int opc;


        printf("\n\n\n");
	
        printf("************* Menu Principal *************\n");
        printf("Escolha a opção desejada:\n\n");
        printf("\t1. Cadastro de Produto.\n");
        printf("\t2. Cadastro de Cliente.\n");
        printf("\t3. Consultar Estoque.\n");
        printf("\t4. Efetuar Venda.\n\n");
        printf("\t0. Sair.\n\n");
        scanf("%d",&opc);



    return 0;
}
