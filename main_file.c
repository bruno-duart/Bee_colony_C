#include "graphs.h"
#include "solutions.h"
#include "metaheuristics.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc < 7) {
        printf("Uso: %s <num_vertex> <caminho_arquivo_txt> <num_bees> <num_colors> <limit> <max_iter>\n", argv[0]);
        return 1;
    }

    int num_vertex = atoi(argv[1]);
    char *caminho_arquivo_txt = argv[2];
    int num_bees = atoi(argv[3]);
    int num_colors = atoi(argv[4]);
    int limit = atoi(argv[5]);
    int max_iter = atoi(argv[6]);
    char *caminho_result = argv[7];
    int *iter = (int*)malloc(sizeof(int));
    *iter = 0;

    srand(time(NULL));
    // Lê o grafo a partir do arquivo txt
    FILE *arquivo = fopen(caminho_arquivo_txt, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    graph_t *g = new_graph_from_file(num_vertex, arquivo);

    fclose(arquivo);
    clock_t time0 = clock();
    solution_t *best = ABC_Graph_Coloring(g, num_bees, num_colors, max_iter, limit, iter);
    time0 = clock() - time0;
    // printf("Best: %d - ", best->num_conflitos);
    // solution_toString(best, g->V);
    FILE *results = fopen(caminho_result, "a");
    if (results == NULL) {
        printf("Erro ao abrir o arquivo de resultados.\n");
        return 1;
    }
    fprintf(results, "%d;%f;%d;%d;%d;%d;%d\n", best->num_conflitos, (double)time0/CLOCKS_PER_SEC, *iter, num_bees, num_colors, limit, max_iter);
    fclose(results);
    free_solution(best);
    free_graph(g);
    free(iter);
    return 0;
}

// ./main 11 data/instances/myciel3.txt 20 6 5 100
//     <num_vertex> <caminho_arquivo_txt> <num_bees> <num_colors> <limit> <max_iter>