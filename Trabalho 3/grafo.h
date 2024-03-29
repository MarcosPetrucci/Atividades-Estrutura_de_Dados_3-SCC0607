/* Marcos Vinícius Firmino Pietrucci 10770072 */

#ifndef MAIN_H
#include"main.h"
#endif
#ifndef STDLIB_H
#include<stdlib.h>
#endif
#include"arquivoIndex.h"
#include"arquivoPessoa.h"
#include"arquivoSegue.h"

#ifndef GRAFO
#define GRAFO
/* Estrutura do grafo */
typedef struct no {
  char nomePessoa[40];
  int visitado;
  struct no* segue;
  struct no* prox;
}Vertice;

typedef struct grafo {
    int n;            //Número de vértices
    Vertice** lista;  //Lista de Lista
}Grafo;

#endif

/******** Funções referentes ao grafo *********/
//Função que cria um grafo e retorna um ponteiro para ele
Grafo* cria_grafo(int n);

//Função que libera todo o grafo adequadamente
void libera_grafo(Grafo *gr);

//Função que imprime o grafo conforme especificado
void imprime_grafo(Grafo* gr);

//Função que adiciona um vértice no gráfico, uma pessoa no vetor de de pessoas
void adiciona_vertice_ordenado(Grafo *gr, char nome[40]);

//Função que adiciona a pessoa seguida na sub-lista da pessoa que segue
void adiciona_relacao(Grafo *gr, char nomePessoaQueSegue[40], char nomePessoaQueESeguida[40]);

//Função que lê um arquivo de pessoas e gera o grafo
Grafo* leitura_arq_pessoa_gera_grafo(FILE *arq_pessoa, FILE *arq_index, FILE *arq_segue);

//Função que transpoe um grafo
Grafo* transpoe_grafo(Grafo *gr);

//Função que executa uma busca em largura
int* buscaLargura_Grafo(Grafo *gr_t, char *nomeCelebridade);

//Função que retorna um vértice dado seu índice
Vertice* get_vertice_de_indice(Grafo *gr_t, int indc);

//Função que retorna o índice de um vértice dado seu nome
int get_indc_vertice(Grafo *gr_t, char *nomeAux);

//Função que retorna, dos varios seguidos de um vertice, o mais "próximo" alfabeticamente
Vertice* get_seguidor_nao_visitado(Grafo *gr, Vertice *ini);

//Função que procura ciclos por meio de uma busca em profundidade
int busca_em_profundidade(Grafo *gr, char *nomeProcura);
