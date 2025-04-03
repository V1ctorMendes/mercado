#include "mercado.h"

// Variáveis globais para produtos e carrinho
static int contador_produto = 0;
static int contador_carrinho = 0;
static Produto produtos[50];
static Carrinho carrinho[50];

// Exibe informações de um produto
void infoProduto(Produto prod) {
    printf("Código: %d \nNome: %s \nPreço: %.2f\n", prod.codigo, strtok(prod.nome, "\n"), prod.preco);
}

// Exibe o menu principal
void menu() {
    printf("================ Bem-vindo(a) - Solução Mercado ===========\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Listar produtos\n");
    printf("3 - Comprar produto\n");
    printf("4 - Visualizar carrinho\n");
    printf("5 - Fechar pedido\n");
    printf("6 - Sair do sistema\n");

    int opcao;
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1: cadastrarProduto(); break;
        case 2: listarProdutos(); break;
        case 3: comprarProduto(); break;
        case 4: visualizarCarrinho(); break;
        case 5: fecharPedido(); break;
        case 6:
            printf("Volte sempre!\n");
            sleep(2);
            exit(0);
        default:
            printf("Opção inválida.\n");
            sleep(2);
            menu();
    }
}

// Cadastra um novo produto
void cadastrarProduto() {
    printf("Cadastro de Produto\n");

    printf("Informe o nome do produto: \n");
    fgets(produtos[contador_produto].nome, 30, stdin);

    printf("Informe o preço do produto: \n");
    scanf("%f", &produtos[contador_produto].preco);
    getchar();

    produtos[contador_produto].codigo = contador_produto + 1;
    printf("O produto %s foi cadastrado com sucesso.\n", strtok(produtos[contador_produto].nome, "\n"));

    contador_produto++;
    sleep(2);
    menu();
}

// Lista todos os produtos cadastrados
void listarProdutos() {
    if (contador_produto > 0) {
        printf("Listagem de produtos:\n");
        for (int i = 0; i < contador_produto; i++) {
            infoProduto(produtos[i]);
            printf("------------------\n");
            sleep(1);
        }
    } else {
        printf("Não temos produtos cadastrados.\n");
    }
    sleep(2);
    menu();
}

// Adiciona um produto ao carrinho
void comprarProduto() {
    listarProdutos();
    printf("Informe o código do produto para adicionar ao carrinho:\n");
    int codigo;
    scanf("%d", &codigo);
    getchar();

    Produto p = pegarProdutoPorCodigo(codigo);
    if (p.codigo != 0) {
        carrinho[contador_carrinho].produto = p;
        carrinho[contador_carrinho].quantidade = 1;
        contador_carrinho++;
        printf("O produto %s foi adicionado ao carrinho.\n", strtok(p.nome, "\n"));
    } else {
        printf("Produto não encontrado.\n");
    }
    sleep(2);
    menu();
}

// Exibe os produtos no carrinho
void visualizarCarrinho() {
    if (contador_carrinho > 0) {
        printf("Produtos no Carrinho:\n");
        for (int i = 0; i < contador_carrinho; i++) {
            infoProduto(carrinho[i].produto);
            printf("Quantidade: %d\n", carrinho[i].quantidade);
            printf("-----------------\n");
        }
    } else {
        printf("Carrinho vazio.\n");
    }
    sleep(2);
    menu();
}

// Busca um produto pelo código
Produto pegarProdutoPorCodigo(int codigo) {
    for (int i = 0; i < contador_produto; i++) {
        if (produtos[i].codigo == codigo) {
            return produtos[i];
        }
    }
    Produto p = {0, "", 0.0};
    return p;
}

// Verifica se um produto já está no carrinho
int *temNoCarrinho(int codigo) {
    static int retorno[] = {0, 0}; // {existe (1 ou 0), índice}
    for (int i = 0; i < contador_carrinho; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            retorno[0] = 1;
            retorno[1] = i;
        }
    }
    return retorno;
}

// Finaliza a compra e exibe o valor total
void fecharPedido() {
    if (contador_carrinho > 0) {
        float valorTotal = 0.0;
        printf("Produtos no Carrinho:\n");
        for (int i = 0; i < contador_carrinho; i++) {
            Produto p = carrinho[i].produto;
            int quantidade = carrinho[i].quantidade;
            valorTotal += p.preco * quantidade;
            infoProduto(p);
            printf("Quantidade: %d\n", quantidade);
            printf("---------------\n");
        }
        printf("Total da compra: R$ %.2f\n", valorTotal);
        contador_carrinho = 0;
        printf("Compra finalizada. Obrigado!\n");
        sleep(5);
    } else {
        printf("Carrinho vazio.\n");
    }
    menu();
}