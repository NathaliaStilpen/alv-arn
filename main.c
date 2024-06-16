#include "avl.h"
#include "arn.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    avl *arv;
    arn *T;
    int res, i, j, tam = 10000, rot_insercao = 0, rot_remocao = 0, qtde_elem, qtde_elem_remocao, num_repeticoes = 5, op, x, qtde_elemARB, qtde_elemR_ARB;
    double tempo_total_insercao = 0.0, tempo_medio_insercao,
            tempo_total_remocao = 0.0, tempo_medio_remocao, tempo_total_busca = 0.0, tempo_medio_busca;
    clock_t t_ini_insercao, t_fim_insercao, t_ini_remocao, t_fim_remocao, t_ini_busca, t_fim_busca;
    no *busca;
    tno *busca2;

    srand(time(NULL));
    printf("\nEscolha \n1 - AVL\n2 -  Arvore Rubro Negra\n");
    printf("Digite a opcao : ");
    scanf("%d", &op);
    printf("\n");
    switch (op) {
        case 1:
            printf("RESULTADOS AVL\n");
            for (j = 0; j < num_repeticoes; j++) {
                arv = criaArvore();
                if (arv == NULL) {
                    printf("Erro ao criar a árvore AVL\n");
                    return 1;
                }

                //Realizando a inserção
                printf("Inserindo... repeticao %d\n", j + 1);
                t_ini_insercao = clock();
                for (i = 1; i < tam + 1; i++) {
                    res = insereNo(arv, i);
                    if (res != 1) {
                        printf("Erro na inserção do elemento %d\n", i);
                        return 1;
                    }
                }

                t_fim_insercao = clock();
                tempo_total_insercao +=
                        (double) (t_fim_insercao - t_ini_insercao) * 1000 / CLOCKS_PER_SEC;
                rot_insercao = qtde_Rotacoes(arv);
                qtde_elem = getNumElementos(arv);

                //Realizando busca de elementos aleatórios
                printf("Buscando... repeticao %d\n", j + 1);
                t_ini_busca = clock();
                for (i = 1; i < 1000 + 1; i++) {
                    x = 1 + (rand() % 10000);
                    encontraNo(arv, x);
                    busca = encontraNo(arv, x);
                    if (busca == NULL) {
                        printf("Elemento %d não encontrado.\n", x);
                    }
                }
                t_fim_busca = clock();
                tempo_total_busca += (double) (t_fim_busca - t_ini_busca) * 1000 / CLOCKS_PER_SEC;

                //Realizando a remoção
                printf("Removendo... repeticao %d\n", j + 1);
                t_ini_remocao = clock();
                for (i = 1; i < tam + 1; i++) {
                    res = removeNo(arv, i);
                    if (res != 1) {
                        printf("Erro na remocao do elemento %d\n", i);
                        return 1;
                    }
                }


                t_fim_remocao = clock();
                tempo_total_remocao +=
                        (double) (t_fim_remocao - t_ini_remocao) * 1000 / CLOCKS_PER_SEC;
                rot_remocao = qtde_Rotacoes(arv) - rot_insercao;
                qtde_elem_remocao = getNumElementos(arv);
            }
            // imprimePreOrdem(getRaiz(arv));

            tempo_medio_insercao = tempo_total_insercao / num_repeticoes;
            tempo_medio_busca = tempo_total_busca / num_repeticoes;
            tempo_medio_remocao = tempo_total_remocao / num_repeticoes;


            printf("\nTempo medio de insercao: %.2f ms\n", tempo_medio_insercao);
            printf("Tempo medio de remocao: %.2f ms\n", tempo_medio_remocao);
            printf("Tempo medio de busca: %.2f ms\n", tempo_medio_busca);
            printf("\nQuantidade de rotacoes (insercao): %d\n", rot_insercao);
            printf("Quantidade de rotacoes (remocao): %d\n", rot_remocao);
            printf("\nQuantidade de elementos na arvore apos insercao: %d\n", qtde_elem);
            printf("Quantidade de elementos na arvore apos remocao: %d\n", qtde_elem_remocao);
            break;
        case 2:
            printf("RESULTADO ARB\n");
            for (j = 0; j < num_repeticoes; j++) {
                T = criarRN();
                if (T == NULL) {
                    printf("Erro ao criar a árvore ARB\n");
                    return 1;
                }

                //Realizando a inserção
                printf("Inserindo repeticao %d\n", j + 1);
                t_ini_insercao = clock();
                for (i = 1; i < tam + 1; i++) {
                    incluirRN(T, i);
                }

                //Contagem do tempo, rotações e quantidade de elementos da árvore após a inserção
                t_fim_insercao = clock();
                tempo_total_insercao +=
                        (double) (t_fim_insercao - t_ini_insercao) * 1000 / CLOCKS_PER_SEC;
                rot_insercao = qtde_RotacoesRN(T);
                qtde_elemARB = qtde_ElementosRN(T);

                //Realizando busca de elementos aleatórios
                printf("Buscando repeticao %d\n", j + 1);
                t_ini_busca = clock();
                for (i = 0; i < 1000; i++) {
                    x = 1 + (rand() % 10000);
                    busca2 = buscarRN(T, x);
                    if (busca2 == NULL) {
                        printf("Elemento %d não encontrado.\n", x);
                    }
                }
                t_fim_busca = clock();
                tempo_total_busca += (double) (t_fim_busca - t_ini_busca) * 1000 / CLOCKS_PER_SEC;
                tno *x;
                //Realizando a remoção
                printf("Removendo repeticao %d\n", j + 1);
                t_ini_remocao = clock();
                for (i = 1; i < tam + 1; i++) {
                    x = buscarRN(T, i);
                    removerRN(T, x);
                }

                //Contagem do tempo, rotações e quantidade de elementos da árvore após a remoção
                t_fim_remocao = clock();
                tempo_total_remocao +=
                        (double) (t_fim_remocao - t_ini_remocao) * 1000 / CLOCKS_PER_SEC;
                rot_remocao = qtde_RotacoesRN(T) - rot_insercao;
                qtde_elemR_ARB = qtde_ElementosRN(T);

                apagarRN(T);
            }
            // imprimePreOrdem(getRaiz(arv));

            // Calculando tempo médio de inserção e remoção (após 5 repetições)
            tempo_medio_insercao = tempo_total_insercao / num_repeticoes;
            tempo_medio_busca = tempo_total_busca / num_repeticoes;
            tempo_medio_remocao = tempo_total_remocao / num_repeticoes;

            // Imprimindo resultados
            printf("\nTempo medio de insercao: %.2f ms\n", tempo_medio_insercao);
            printf("Tempo medio de remocao: %.2f ms\n", tempo_medio_remocao);
            printf("Tempo medio de busca: %.2f ms\n", tempo_medio_busca);
            printf("\nQuantidade de rotacoes (insercao): %d\n", rot_insercao);
            printf("Quantidade de rotacoes (remocao): %d\n", rot_remocao);
            printf("\nQuantidade de elementos na arvore apos insercao: %d\n", qtde_elemARB);
            printf("Quantidade de elementos na arvore apos remocao: %d\n", qtde_elemR_ARB);
    }

    return 0;
}
