#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE 10

typedef struct
{
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Inserir novo item
void inserirItemVetor(Item *itens, int *qtd)
{
    if (*qtd >= CAPACIDADE)
    {
        printf("Mochila cheia!\n");
        return;
    }

    printf("Digite o nome do item: ");
    scanf("%s", itens[*qtd].nome);

    printf("Digite o tipo do item: ");
    scanf("%s", itens[*qtd].tipo);

    printf("Digite a quantidade do item: ");
    scanf("%d", &itens[*qtd].quantidade);

    (*qtd)++;
    printf("Item adicionado com sucesso!\n");
}

// Remover item por nome
void removerItemVetor(Item *itens, int *qtd)
{
    if (*qtd == 0)
    {
        printf("A mochila está vazia.\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nome);

    int pos = -1;
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
        printf("Item não encontrado.\n");
        return;
    }

    for (int i = pos; i < *qtd - 1; i++)
    {
        itens[i] = itens[i + 1];
    }

    (*qtd)--;
    printf("Item removido com sucesso!\n");
}

// Listar todos os itens
void listarItensVetor(Item *itens, int qtd)
{
    if (qtd == 0)
    {
        printf("A mochila está vazia.\n");
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

// Buscar item por nome (busca sequencial)
void buscarSequencialVetor(Item *itens, int qtd)
{
    if (qtd == 0)
    {
        printf("A mochila está vazia.\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nome);

    for (int i = 0; i < qtd; i++)
    {
        if (strcmp(itens[i].nome, nome) == 0)
        {
            printf("\nItem encontrado:\n");
            printf("  Nome: %s\n", itens[i].nome);
            printf("  Tipo: %s\n", itens[i].tipo);
            printf("  Quantidade: %d\n", itens[i].quantidade);
            return;
        }
    }

    printf("Item não encontrado.\n");
}

// Ordenar vetor (Bubble Sort)
void ordenarVetor(Item *itens, int qtd)
{
    if (qtd < 2)
    {
        printf("Poucos itens para ordenar.\n");
        return;
    }

    Item temp;
    for (int i = 0; i < qtd - 1; i++)
    {
        for (int j = 0; j < qtd - i - 1; j++)
        {
            if (strcmp(itens[j].nome, itens[j + 1].nome) > 0)
            {
                temp = itens[j];
                itens[j] = itens[j + 1];
                itens[j + 1] = temp;
            }
        }
    }

    printf("Itens ordenados com sucesso!\n");
}

// Busca binária
void buscarBinariaVetor(Item *itens, int qtd)
{
    if (qtd == 0)
    {
        printf("A mochila está vazia.\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item para busca binária: ");
    scanf("%s", nome);

    int inicio = 0, fim = qtd - 1, meio;
    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;
        int cmp = strcmp(nome, itens[meio].nome);

        if (cmp == 0)
        {
            printf("\nItem encontrado (busca binária):\n");
            printf("  Nome: %s\n", itens[meio].nome);
            printf("  Tipo: %s\n", itens[meio].tipo);
            printf("  Quantidade: %d\n", itens[meio].quantidade);
            return;
        }
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }

    printf("Item não encontrado na busca binária.\n");
}

// === MAIN ===
int main()
{
    Item *mochila = (Item *)malloc(CAPACIDADE * sizeof(Item));
    if (mochila == NULL)
    {
        printf("Erro de alocação.\n");
        return 1;
    }

    int qtd = 0;
    int opcao;

    do
    {
        printf("\n--- MENU MOCHILA (VETOR) ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item (sequencial)\n");
        printf("5 - Ordenar itens por nome\n");
        printf("6 - Buscar item (binária)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            inserirItemVetor(mochila, &qtd);
            break;
        case 2:
            removerItemVetor(mochila, &qtd);
            break;
        case 3:
            listarItensVetor(mochila, qtd);
            break;
        case 4:
            buscarSequencialVetor(mochila, qtd);
            break;
        case 5:
            ordenarVetor(mochila, qtd);
            break;
        case 6:
            buscarBinariaVetor(mochila, qtd);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    free(mochila);
    return 0;
}
