/* Marcos Vinícus Firmino Pietrucci 10770072 */

#include "modo7.h"
#ifndef FORNECIDO_H_
#define FORNECIDO_H_
#include"fornecido.h"
#endif
#ifndef STDLIB_H
#define STDLIB_H
#include<stdlib.h>
#endif

//Função que inicia a leitura das entradas e o processamento do modo 7
void modo7()
{
    //Continuar com a leitura
    char arq_segue_nome[30], nome_arq_ordenado[30];

    //Lê as entradas
    le_entradas_modo7(arq_segue_nome, nome_arq_ordenado);

    //Abre os arquivos pertinentes
    FILE *arq_segue = le_arquivo(arq_segue_nome, "rb", 1);
    if(arq_segue == NULL || !teste_consistencia_cabecalho(arq_segue, 7)) 
        return;
    FILE *arq_ordenado = le_arquivo(nome_arq_ordenado, "wb", 1);
    if(arq_ordenado == NULL)
        return;
    
    //Lê os dados do arquivo
    int num_segue = 0;
    Segue *vetSegue = le_dados_arqSegue_BIN(arq_segue, &num_segue);

    //Ordena os dados
    ordena_vetSegue(vetSegue, num_segue);

    //Escreve o arquivo Segue em disco
    escreve_arqSegue(arq_ordenado, vetSegue, num_segue);

    free(vetSegue);
    fclose(arq_ordenado);
    fclose(arq_segue);

    binarioNaTela2(nome_arq_ordenado);
}

//Função que lê as entradas do modo 7
void le_entradas_modo7(char *arq_segue_nome, char *nome_arq_ordenado)
{
    char lixo;
    scanf("%c", &lixo);
    fflush(stdin);
    scanf("%s", arq_segue_nome);
    fflush(stdin);
    scanf("%c", &lixo);
    fflush(stdin);    
    scanf("%s", nome_arq_ordenado);
}

//Função que comprara dois registros de "Segue" segundo os critérios definidos
int compara_vetSegue(Segue a, Segue b)
{
    int v1,v2,v3,v4;
    v1 = a.idPessoaQueSegue - b.idPessoaQueSegue;
    v2 = a.idPessoaQueESeguida - b.idPessoaQueESeguida;
    v3 = strcmp(a.dataInicioQueSegue, b.dataInicioQueSegue); //Será que o mais antigo tem prioridade? Ou o mais recente??
    v4 = strcmp(a.dataFimQueSegue, b.dataFimQueSegue);

   if(v1 > 0) //Primeiro critério: idPessoaQueSegue
   {
       return 1;
   }
   else
   {
       if(v1 == 0)
       {
           if(v2 > 0) //Segundo critério: idPessoaQueESeguida
            {
                return 1;
            }
            else
            {
                if(v2 == 0)
                {
                    if(v3 < 0) //Terceiro critério: dataInicioQueSegue
                    {
                        return 1;
                    }
                    else
                    {
                        if(v3 == 0)
                        {
                            if(v4 < 0) //Quarto critério: dataFimQueSegue
                            {
                                return 1; 
                            }
                            else
                            {   //Mesmo que ocorra um empate total, retorna um valor válido para a comparação
                                return 0;
                            }
                        }
                        return 0;
                    }
                }
                return 0;
            }
       }

       return 0;
   }
   
}

void ordena_vetSegue(Segue *vetSegue, int num_segue)
{
    //Será utilizado insertion sort para ordenar
    int i, j;
    Segue key;  
    for (i = 1; i < num_segue; i++) 
    {  
        key = vetSegue[i];  
        j = i - 1;  
        while (j >= 0 && compara_vetSegue(vetSegue[j], key)) 
        {  
            vetSegue[j + 1] = vetSegue[j];  
            j = j - 1;  
        }  
        vetSegue[j + 1] = key;  
    } 
}
