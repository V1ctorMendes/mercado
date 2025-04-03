#ifndef MERCADO_H  
#define MERCADO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> 

// Estrutura que representa um produto no mercado
typedef struct {
    int codigo;    // Código do produto
    char nome[30]; // Nome do produto
    float preco;   // Preço do produto
} Produto;

// Estrutura que representa um item no carrinho de compras
typedef struct {
    Produto produto; // Produto armazenado
    int quantidade;  // Quantidade do produto no carrinho
} Carrinho;

// Declaração das funções utilizadas no sistema
void infoProduto(Produto prod);
void menu();
void cadastrarProduto();
void listarProdutos();
void comprarProduto();
void visualizarCarrinho();
Produto pegarProdutoPorCodigo(int codigo);
int *temNoCarrinho(int codigo);
void fecharPedido();

#endif