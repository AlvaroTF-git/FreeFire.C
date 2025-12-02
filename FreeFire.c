#include <stdio.h>
#include <stdlib.h>
#include <string.h> //necessário para funções como: strcmp, strcpy

#define NOME 30
#define TIPO 20

typedef struct {
    char nome[NOME];
    char tipo[TIPO];
    int quantidade;
    int prioridade;
} itens;

itens mochila[10]; //vetor que representa a mochila, onde cada posição pode armazenar um item (arma, cura, munição)
int ItensMochila = 0; //quantidade atual de itens na mochila
int ordenadoPorNome = 0; //flag: 1 se a mochila estiver ordenada por nome (A-Z)

void inseriritem() {
    if (ItensMochila >= 10) {
        printf("============================================\n");
        printf("Mochila cheia! Não é possível adicionar mais itens, remova um item caso queira adicionar outro tipo de item.\n");
        return;
    }
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("Orientação: Preencha os dados solicitados somente com letras minusculas ou número, sem espaços!!\n");
    printf("==================================================================================================\n");
    printf("Capacidade atual da mochila -> %d/10\n", ItensMochila);
    printf("Qual o nome do item você deseja adicionar?\n");
    scanf("%s", mochila[ItensMochila].nome);
    printf("============================================\n");
    printf("--- Tipos de itens ---\n");
    printf("-> Arma\n-> Cura\n-> Munição\n-> Proteção\n-> Outro\n");
    printf("============================================\n");
    printf("Qual o tipo do item que você deseja adicionar? (listados acima)\n");
    scanf("%s", mochila[ItensMochila].tipo);
    printf("Qual a quantidade do item?\n");
    printf("============================================\n");
    scanf("%d", &mochila[ItensMochila].quantidade);
    printf("Qual a prioridade do item (1-5)?\n");
    printf("OBS: 1 é a prioridade mais baixa, 5 é a prioridade mais alta.\n");
    scanf("%d", &mochila[ItensMochila].prioridade);
    ItensMochila++;
    printf("Item adicionado à mochila!\n");
    ordenadoPorNome = 0; //inserir um item pode quebrar a ordenação
}

//Função para remover o item da mochila deslocando os itens subsequentes para "fechar o espaço"

void removeritem() {
    int index;
    if (ItensMochila == 0) {
        printf("============================================\n");
        printf("Mochila vazia! Não há itens para remover.\n");
        return;
    }
    printf("============================================\n");
    printf("Itens na mochila:\n");
    for (int i = 0; i < ItensMochila; i++) {
        printf("%d. %s (Tipo: %s, Quantidade: %d)\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("Digite o número do índice onde está o item que deseja remover: \n");
    scanf("%d", &index);

    for (int i = index-1; i < ItensMochila - 1; i++) {
        mochila[i] = mochila[i + 1]; //desloca os itens para "fechar o espaço"
    }
    ItensMochila--; //decrementa a quantidade de itens na mochila
    printf("Item removido da mochila!\n");
    printf("============================================\n");
    printf("--- Itens na mochila ---\n");
    for (int i = 0; i < ItensMochila; i++) {
        printf("%d. %s (Tipo: %s, Quantidade: %d)\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
}

//função para listar os itens na mochila com estrutura de repetição

void listaritens() {
    printf("============================================\n");
    printf("Capacidade da mochila -> %d/10\n", ItensMochila);
    printf("--- Itens na mochila ---\n");
    for (int i = 0; i < ItensMochila; i++) {
        printf("%d. %s (Tipo: %s, Quantidade: %d, Prioridade: %d)\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
}

//Função de busca de item na mochila usando busca binária 

void buscabinaria(){
    char nomebusca[NOME];
    printf("============================================\n");
    printf("Digite o nome do item que deseja buscar na mochila:\n");
    scanf("%s", nomebusca);
    if (!ordenadoPorNome) {
        printf("\nERRO: A busca binária requer que a mochila esteja ordenada por nome (A-Z).\n");
        printf("Ordene por nome antes de usar a busca binária (opção 5 -> escolha 1).\n");
        return;
    }
    int esquerda = 0;
    int direita = ItensMochila - 1;
    int encontrado = 0;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        int cmp = strcmp(mochila[meio].nome, nomebusca);
        if (cmp == 0) {
            printf("Item encontrado na mochila!\n");
            printf("Nome: %s, Tipo: %s, Quantidade: %d, Prioridade: %d\n", mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade, mochila[meio].prioridade);
            encontrado = 1;
            return;
        }
        if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    if (!encontrado) {
        printf("Item não encontrado na mochila.\n");
    }
    return;
}


void ordenarmochila() {
    //Função para ordenar os itens na mochila por Ordem alfabética ou por prioridade usando o algoritmo de ordenação Bubble Sort
    printf("============================================\n");
    printf("Qual Tipo de ordenação deseja utilizar?\n");
    printf("1. Ordenação por nome (A-Z)\n2. Ordenação por prioridade (Maior para menor)\n");
    int opcao; 
    printf("Digite a opção desejada: ");
    scanf("%d", &opcao);
    if (opcao == 1) {
        printf("Ordenando os itens na mochila por nome...\n");
        for (int i = 0; i < ItensMochila - 1; i++) {
            for (int j = 0; j < ItensMochila - i - 1; j++) {
                if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                    itens temp = mochila[j];
                    mochila[j] = mochila[j + 1];
                    mochila[j + 1] = temp;
                }
            }
        }
        ordenadoPorNome = 1; //agora está ordenada por nome
        printf("--- RESULTADO DA ORDENAÇÃO ---\n");
        listaritens();
        return;
    }
    else if (opcao == 2)
    {
        printf("Ordenando os itens na mochila por prioridade...\n");
    for (int i = 0; i < ItensMochila - 1; i++) {
        for (int j = 0; j < ItensMochila - i - 1; j++) {
            if (mochila[j].prioridade < mochila[j + 1].prioridade) {
                itens temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    ordenadoPorNome = 0; //ordenação por prioridade não garante ordem alfabética
    printf("--- RESULTADO DA ORDENAÇÃO ---\n");
    listaritens();   
    }
}

int main() {
    printf("Bem-vindo ao sistema de gerenciamento de mochila do Free Fire!\n");
    int escolha;
    int cont = 1;
    while (cont == 1) {
        printf("============================================\n");
        printf("Escolha uma opção:\n1. Adicionar item\n2. Remover item\n3. Listar itens\n4. Buscar Item (Ordenação por nome obrigatória)\n5. Ordenar a mochila\n6. Sair\n");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                inseriritem();
                break;
            case 2:
                removeritem();
                break;
            case 3:
                listaritens();
                break;
            case 4:
                    if (!ordenadoPorNome) {
                        printf("\nA busca binária exige que a mochila esteja ordenada por nome (A-Z).\n");
                        printf("Deseja entrar no menu de ordenação agora? (1 = sim / 0 = não): ");
                        int deseja;
                        scanf("%d", &deseja);
                        if (deseja == 1) {
                            ordenarmochila();
                            if (!ordenadoPorNome) {
                                printf("Não foi possível ordenar por nome agora. Abortando busca.\n");
                                break;
                            }
                        } else {
                            printf("Operação de busca cancelada. Ordene por nome e tente novamente.\n");
                            break;
                        }
                    }
                    buscabinaria();
                break;
            case 5:
                ordenarmochila();
                break;
            default:
                printf("Saindo do sistema de gerenciamento de mochila. Até a próxima!\n");
                cont = 0;
                break;
    }
    }
    return 0;
}