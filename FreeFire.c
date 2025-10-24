#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

void inseriritem(Item *itens, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Digite o nome do item %d: ", i + 1);
        scanf("%s", itens[i].nome);

        printf("Digite o tipo do item %d: ", i + 1);
        scanf("%s", itens[i].tipo);

        printf("Digite a quantidade do item %d: ", i + 1);
        scanf("%d", &itens[i].quantidade);

        printf("\n");
    }
}

void removerItem(Item *itens, int *qtd)
{
    char nome[30];
    int pos = -1; //posição

    if (*qtd == 0)
    {
        printf("A mochila está vazia.\n");
        return;
    }

    printf("Digite o nome do item que deseja remover: ");
    scanf("%s", nome);

    // busca sequencial pelo nome
    for (int i = 0; i < *qtd; i++)
    {
        if (strcmp(itens[i].nome, nome) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("Item '%s' não encontrado.\n", nome);
        return;
    }

    // desloca os itens à esquerda
    for (int i = pos; i < *qtd - 1; i++)
    {
        itens[i] = itens[i + 1];
    }

    (*qtd)--; 
    printf("Item '%s' removido com sucesso.\n", nome);
}

void listarItens(Item *itens, int qtd)
{
    if (qtd == 0)
    {
        printf("\nA mochila está vazia.\n");
        return;
    }

        printf("\n--- Itens na mochila ---\n");
        for (int i = 0; i < qtd; i++)
        {
            printf("Item %d:\n", i + 1);
            printf("  Nome: %s\n", itens[i].nome);
            printf("  Tipo: %s\n", itens[i].tipo);
            printf("  Quantidade: %d\n", itens[i].quantidade);
            printf("--------------------------\n");
        }
}

void buscarItem(Item *itens, int qtd)
{
   
        char nome[30];
        int encontrado = -1;

        if (qtd == 0)
        {
            printf("A mochila está vazia.\n");
            return;
        }

        printf("Digite o nome do item que deseja buscar: ");
        scanf("%s", nome);

        for (int i = 0; i < qtd; i++)
        {
            if (strcmp(itens[i].nome, nome) == 0)
            {
                encontrado = i;
                break;
            }
        }

        if (encontrado == -1)
        {
            printf("Item '%s' não encontrado.\n", nome);
        }
        else
        {
            printf("\nItem encontrado:\n");
            printf("  Nome: %s\n", itens[encontrado].nome);
            printf("  Tipo: %s\n", itens[encontrado].tipo);
            printf("  Quantidade: %d\n", itens[encontrado].quantidade);
        }
}

int main()
{
    Item *mochila;
    int capacidade = 10;
    int qtdItens = 0;
    int opcao;

    // alocando dinamicamente
    mochila = (Item *)malloc(capacidade * sizeof(Item));
    if (mochila == NULL)
    {
        printf("Erro de alocação!\n");
        return 1; // sai do programa
    }

    do
    {
        printf("\n--- Menu ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (qtdItens < capacidade)
            {
                inseriritem(&mochila[qtdItens], 1); // cadastra 1 item de cada vez
                qtdItens++;
            }
            else
            {
                printf("Mochila cheia!\n");
            }
            break;
        case 2:
            removerItem(mochila, &qtdItens);
            break;
        case 3:
            listarItens(mochila, qtdItens);
            break;
        case 4:
            buscarItem(mochila, qtdItens);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    free(mochila); // libera memória
    return 0;
}
