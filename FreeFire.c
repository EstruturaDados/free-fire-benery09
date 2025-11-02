#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define MAX_NOME 30
#define MAX_TIPO 20

typedef struct
{
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade;
} Componente;

// Ler string com fgets
void lerString(char *str, int tamanho)
{
    fgets(str, tamanho, stdin);
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

// Ler inteiro seguro
int lerInt()
{
    char buffer[20];
    int valor;
    fgets(buffer, 20, stdin);
    sscanf(buffer, "%d", &valor);
    return valor;
}

// Mostrar componentes
void mostrarComponentes(Componente *v, int n)
{
    printf("\n--- Componentes ---\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d. Nome: %s | Tipo: %s | Prioridade: %d\n", i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// Bubble Sort por nome
void bubbleSortNome(Componente *v, int n, int *comparacoes)
{
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            (*comparacoes)++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0)
            {
                Componente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente *v, int n, int *comparacoes)
{
    *comparacoes = 0;
    for (int i = 1; i < n; i++)
    {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0 && (++(*comparacoes), strcmp(v[j].tipo, chave.tipo) > 0))
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente *v, int n, int *comparacoes)
{
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            (*comparacoes)++;
            if (v[j].prioridade < v[min_idx].prioridade)
                min_idx = j;
        }
        if (min_idx != i)
        {
            Componente temp = v[i];
            v[i] = v[min_idx];
            v[min_idx] = temp;
        }
    }
}

// Busca binária por nome (apenas após ordenar por nome)
int buscaBinariaPorNome(Componente *v, int n, char *nome, int *comparacoes)
{
    int inicio = 0, fim = n - 1;
    *comparacoes = 0;
    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(nome, v[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return -1;
}

// Cadastro de componentes
void cadastrarComponentes(Componente *v, int *qtd)
{
    if (*qtd >= MAX_COMPONENTES)
    {
        printf("Limite atingido!\n");
        return;
    }
    printf("Nome do componente: ");
    lerString(v[*qtd].nome, MAX_NOME);
    printf("Tipo do componente: ");
    lerString(v[*qtd].tipo, MAX_TIPO);
    printf("Prioridade (1-10): ");
    v[*qtd].prioridade = lerInt();
    (*qtd)++;
}

// === MAIN ===
int main()
{
    Componente componentes[MAX_COMPONENTES];
    int qtd = 0, opcao;

    do
    {
        printf("\n--- MENU TORRE DE FUGA ---\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Listar componentes\n");
        printf("3 - Ordenar por nome (Bubble Sort)\n");
        printf("4 - Ordenar por tipo (Insertion Sort)\n");
        printf("5 - Ordenar por prioridade (Selection Sort)\n");
        printf("6 - Busca binária por nome\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        opcao = lerInt();

        switch (opcao)
        {
        case 1:
            cadastrarComponentes(componentes, &qtd);
            break;
        case 2:
            mostrarComponentes(componentes, qtd);
            break;
        case 3:
        {
            int comparacoes;
            clock_t inicio = clock();
            bubbleSortNome(componentes, qtd, &comparacoes);
            clock_t fim = clock();
            mostrarComponentes(componentes, qtd);
            printf("Comparações: %d\n", comparacoes);
            printf("Tempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
            break;
        }
        case 4:
        {
            int comparacoes;
            clock_t inicio = clock();
            insertionSortTipo(componentes, qtd, &comparacoes);
            clock_t fim = clock();
            mostrarComponentes(componentes, qtd);
            printf("Comparações: %d\n", comparacoes);
            printf("Tempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
            break;
        }
        case 5:
        {
            int comparacoes;
            clock_t inicio = clock();
            selectionSortPrioridade(componentes, qtd, &comparacoes);
            clock_t fim = clock();
            mostrarComponentes(componentes, qtd);
            printf("Comparações: %d\n", comparacoes);
            printf("Tempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
            break;
        }
        case 6:
        {
            char nomeBusca[MAX_NOME];
            printf("Digite o nome do componente para busca binária: ");
            lerString(nomeBusca, MAX_NOME);
            int comparacoes;
            int pos = buscaBinariaPorNome(componentes, qtd, nomeBusca, &comparacoes);
            if (pos != -1)
            {
                printf("Componente encontrado!\nNome: %s | Tipo: %s | Prioridade: %d\n",
                       componentes[pos].nome, componentes[pos].tipo, componentes[pos].prioridade);
            }
            else
            {
                printf("Componente não encontrado.\n");
            }
            printf("Comparações: %d\n", comparacoes);
            break;
        }
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
