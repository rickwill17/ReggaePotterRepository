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
    float preco;
	struct dim_produto *prox;
};
typedef struct dim_produto dim_produto;

struct dim_cliente{
	char nome[TAM];
	long int rg;
	char endereco[TAM];
    long int telefone;
    int totalCompras;

	struct dim_cliente *prox;
};
typedef struct dim_cliente dim_cliente;


dim_produto *listaProdutos;
dim_cliente *listaClientes;
/*---------------------------------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------- Inicializando -------------------------------------------------------*/
int InicializaProduto(dim_produto **listaProdutos)
    {
	   *listaProdutos = NULL; // inicializa
	   	return 0;
    }


int InicializaCliente(dim_cliente **listaClientes)
    {
	   *listaClientes = NULL; // inicializa
	   	return 0;
    }

/*---------------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------- Escrevendo Arquivos --------------------------------------------------------------*/

void ArquivoCliente(char nome[TAM], long int rg,long int telefone, char endereco[TAM]){
// criando a variÃ¡vel ponteiro para o arquivo
    FILE *pont_arq;


    char Nome[TAM];
    strcpy(Nome, nome);
    long int RG = rg;
    long int Telefone = telefone;
    char Endereco[TAM];
    strcpy(Endereco, endereco);

  //abrindo o arquivo
    pont_arq = fopen("arquivoCliente.txt", "a");

    fprintf(pont_arq, "%lu ", RG);
    fprintf(pont_arq, "%s ", Nome);
    fprintf(pont_arq, "%lu ", Telefone);
    fprintf(pont_arq, "%s ", Endereco);

  // fechando arquivo
    fclose(pont_arq);

}

void ArquivoProduto(int id,char nome[TAM],char modelo[TAM],char tipo[TAM],int quantidade, float preco){

// criando a variÃ¡vel ponteiro para o arquivo
    FILE *pont_arq;


    int Id = id;
    int Quantidade = quantidade;
    char Nome[TAM];
    strcpy(Nome, nome);
    char Modelo[TAM];
    strcpy(Modelo, modelo);
    char Tipo[TAM];
    strcpy(Tipo, tipo);
    float Preco = preco;

  //abrindo o arquivo
    pont_arq = fopen("arquivoProduto.txt", "a");


    fprintf(pont_arq, "%d ", Id);
    fprintf(pont_arq, "%s ", Nome);
    fprintf(pont_arq, "%s ", Tipo);
    fprintf(pont_arq, "%s ", Modelo);
    fprintf(pont_arq, "%.2f ", Preco);
    fprintf(pont_arq, "%d ", Quantidade);

  // fechando arquivo
    fclose(pont_arq);



}


/*---------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------- Função de Inserir ----------------------------------------------------------*/
int Inserir_fim_LS_Cliente(dim_cliente **inicio){
    dim_cliente *no_cliente, *percorre;
    no_cliente = (dim_cliente *) malloc(sizeof(dim_cliente));



    char nomeC[TAM], enderecoC[TAM];
    int  totalComprasC = 0;
    long int telefoneC, rgC;

    printf("************* Cadastro de Cliente *************\n");
    printf("\tNome:\n\t");
    scanf("%s", nomeC);
    strcpy(no_cliente -> nome,nomeC);
    printf("\tRG:\n\t");
    scanf("%lu", &rgC);
    no_cliente-> rg = rgC;
    printf("\tEndereço:\n\t");
    scanf("%s", enderecoC);
    strcpy(no_cliente -> endereco,enderecoC);
    no_cliente ->totalCompras = totalComprasC;
    printf("\tTelefone:\n\t");
    scanf("%lu", &telefoneC);
    no_cliente ->telefone = telefoneC;


    ArquivoCliente(nomeC, rgC, telefoneC, enderecoC);

    if (*inicio==NULL)
	{ /* lista vazia. */
	    *inicio = no_cliente;
	}
	else { /* lista nao vazia */
	     percorre = *inicio;
	     while (percorre->prox != NULL)
	     {
	         percorre = percorre -> prox;
	     }
	    percorre->prox = no_cliente;
	}
	no_cliente -> prox = NULL;
	return 0;
}

int Inserir_fim_LS_Produto(dim_produto **inicio){
    dim_produto *no_produto, *percorre;
    no_produto = (dim_produto *) malloc(sizeof(dim_produto));


    int idProduto, numeracaoProduto, quantidadeProduto;
    char nomeProduto[TAM];
    char tipoProduto[TAM];
    char modeloProduto[TAM];
    float precoProduto;

    printf("\tID:\n\t");
    scanf("%d", &idProduto);
    no_produto -> id = idProduto;
    printf("\tNome: \n\t");
    scanf("%s", nomeProduto);
    strcpy(no_produto -> nome,nomeProduto);
    printf("\tTipo: \n\t");
    scanf("%s", tipoProduto);
    strcpy(no_produto -> tipo,tipoProduto);
    printf("\tModelo: \n\t");
    scanf("%s", modeloProduto);
    strcpy(no_produto -> modelo, modeloProduto);
    printf("\tQuantidade:\n\t");
    scanf("%d",&quantidadeProduto);
    no_produto-> quantidade = quantidadeProduto;

    printf("\tPreço da unidade (reais):\n\t");
    scanf("%f", &precoProduto);
    no_produto -> preco = precoProduto;

    ArquivoProduto(idProduto, nomeProduto, modeloProduto, tipoProduto, quantidadeProduto, precoProduto );

    no_produto -> prox = NULL;

    if (*inicio==NULL)
	{ //lista vazia.
	    *inicio = no_produto;
	}
	else {  //lista nao vazia
	     percorre = *inicio;
	     while (percorre->prox != NULL)
	     {
	         percorre = percorre -> prox;
	     }
	    percorre->prox = no_produto;
	}
	return 0;
	}
/*---------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------- Função de Venda ------------------------------------------------------------*/

int RealizarVenda(dim_produto **inicio){
    int controle, cod, num;

    dim_produto *percorre, *verificaCod;

    printf("Digite o id do produto:\n");
    scanf("%d",&cod);
    printf("Digite a quantidade:\n");
    scanf("%d",&num);


    if (*inicio==NULL)
	{
	printf("Lista vazia!\n");
    return 2; // Lista vazia
	}else{
        percorre = *inicio;
        verificaCod = *inicio;
        if(verificaCod->prox == NULL){
            if(verificaCod->id==cod){
                if(verificaCod->quantidade < num){
                    printf("Quantidade insuficiente.\n");
                }else{
                    verificaCod->quantidade =(verificaCod->quantidade)-num;
                    printf("Subtotal: %.2f.\n",(verificaCod->preco)*num);
                    printf("1- Continuar.\n");
                    printf("2- Sair.\n");
                    scanf("%d",&controle);

                    if(controle == 1){
                        return controle;
                    }else{
                        controle = verificarCadastro();
                    }
                    return controle;
                 }
            }
        }
        else{
            while (verificaCod->prox != NULL){
                percorre = percorre -> prox;
                verificaCod =  verificaCod->prox;
                if(verificaCod->id==cod){
                    verificaCod ->quantidade = (verificaCod ->quantidade)-num;
                    printf("1- Continuar.\n");
                    printf("2- Sair.\n");
                    scanf("%d",&controle);

                    if(controle == 1){
                        return controle;
                    }else{
                        controle = verificarCadastro();
                    }
                    return controle;
                }
            }
        }
	}

}


/*---------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------- Funçao de Consultar Cliente -------------------------------------------------*/

int ConsultarCliente(long int RgCliente ,dim_cliente *inicio){

    int RG = RgCliente, controle = 0;

    if(inicio == NULL){
        return 1;
    }

    while(controle == 0){
        if(inicio->rg != RG){
            inicio = inicio -> prox;
            if(inicio == NULL){
                return 1;
            }

        }
        else{
        printf("\n");
        printf("\tNome: %s\n", inicio ->nome);
        printf("\tRG: %lu\n", inicio->rg);
        printf("\tTelefone: %lu\n", inicio->telefone);
        printf("\tTotal de compras: %d\n", inicio->totalCompras);
        printf("\n");
        controle = 1;
        }
    }
    printf("\n\n");
    return 0;
}

/*---------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------- Funçao de Pesquisa ----------------------------------------------------------*/

int verificarCadastro(){
    int opc = 0, aux = 0;


    printf("O cliente possui cadastro?\n");
    printf("1- Sim.\n");
    printf("2- Nao.\n");
    scanf("%d", &opc);

    if(opc == 2){
        printf("Cuidado!Estoque desatulizado!\n Sempre Cadastre o cliente antes da compra!!!\n");
        aux = 1;

        Inserir_fim_LS_Cliente(&listaClientes);
    }else{
       aux = confirmarVenda(listaClientes);
    }

    return aux;
}
/*---------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------------------*/
int confirmarVenda(dim_cliente *inicio){

    long int RG;
    int controle = 0;

    printf("Digite o RG do cliente:");
    scanf("%lu", &RG);

    if(inicio == NULL){
        printf("Lista vazia!");
        return 1;
    }

    while(controle != 1){
        if(inicio->rg == RG){
                inicio->totalCompras+=1;
                return 2;
            }
        if(inicio->rg != RG){
            inicio = inicio -> prox;
            if(inicio == NULL){
            controle = 1;
            }
        }
    }

}

/*---------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------- Funções de Exiber -----------------------------------------------------------*/

int ExibirEstoque(dim_produto *inicio){
    int i;
    if(inicio == NULL){
        return 1;
    }

    while(inicio != NULL){
        printf("\n");


        int id, numeracao, quantidade;
        char nome[TAM];
        char tipo[TAM];
        char modelo[TAM];


        printf("\tID: %d\n",inicio ->id);
        printf("\tProduto: %s\n", inicio ->nome);
        printf("\tTipo: %s\n", inicio ->tipo);
        printf("\tModelo: %s\n", inicio ->modelo);
        printf("\tQuantidade: %d\n", inicio ->quantidade);
        printf("\n");
        inicio = inicio -> prox;
    }
    printf("\n\n");
    return 0;

}
/*--------------------------------------------------- Função Principal -----------------------------------------------------------*/


int main(){


    InicializaCliente(&listaClientes);
    InicializaProduto(&listaProdutos);

    long int rgCliente = 0, rgCliente2 = 0;
    int codProd, quantProd, controleVenda;
    int opc, aux = 0, aux1 = 0, aux2 = 0, aux3 = 0, controle = 0;
    while(controle != 1){

        printf("\n\n\n");
        printf("************* Menu Principal *************\n");
        printf("Escolha a opção desejada:\n\n");
        printf("\t1. Cadastro de Produto.\n");
        printf("\t2. Cadastro de Cliente.\n");
        printf("\t3. Consultar Estoque.\n");
        printf("\t4. Consultar Cliente.\n");
        printf("\t5. Efetuar Venda.                Sempre cadastre o cliente antes!\n\n");
        printf("\t0. Sair.\n\n");
        scanf("%d",&opc);

        switch(opc){
            case 1:
                Inserir_fim_LS_Produto(&listaProdutos);
            break;
            case 2:
                Inserir_fim_LS_Cliente(&listaClientes);
            break;
            case 3:
                printf("************* Estoque *************\n");
                    aux = ExibirEstoque(listaProdutos);
                    if(aux == 1){
                        printf(" Lista vazia!\n");
                    }
            break;
            case 4:
                printf("************* Consultar Cliente *************\n");
                printf("Digite o RG do Cliente:\n");
                scanf("%lu",&rgCliente);
                aux2 = ConsultarCliente(rgCliente, listaClientes);
                if(aux2 == 1){
                        printf(" Não Encontrado!\n");
                    }
            break;
            case 5:
                while(controleVenda != 2){
                    printf("************* Venda *************\n");
                    controleVenda = RealizarVenda(&listaProdutos);
                }
                controleVenda = 0;
            break;

            case 0:
                controle = 1;
            break;
        }
    }
    return 0;
}
/*---------------------------------------------------------------------------------------------------------------------------------*/

