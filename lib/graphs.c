#include "graphs.h"

#include <stdio.h>
#include <stdlib.h>

int **new_matrix(int rows, int columns)
{
    int val;
    int **matrix = malloc(sizeof(int *) * rows);

    for (int i = 0; i < rows; i++)
        matrix[i] = malloc(sizeof(int) * columns);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            scanf("%d", &val);
            matrix[i][j] = val;
        }

    return matrix;
}

int **new_matrix_from_file(int rows, int columns, FILE *file)
{
    int val;
    int **matrix = malloc(sizeof(int *) * rows);

    for (int i = 0; i < rows; i++)
        matrix[i] = malloc(sizeof(int) * columns);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            if (fscanf(file, "%d", &val) != 1) {
                fprintf(stderr, "Erro ao ler matriz.\n");
                exit(1);
            }
            matrix[i][j] = val;
        }

    return matrix;
}

graph_t *new_graph(int num_V)
{
    graph_t *G = malloc(sizeof(graph_t));
    G->V = num_V;
    G->E = 0; // TODO: write code to count edges;
    G->adj = new_matrix(num_V, num_V);
    return G;
}

graph_t *new_graph_from_file(int num_V, FILE *file)
{
    graph_t *G = malloc(sizeof(graph_t));
    G->V = num_V;
    G->E = 0; // TODO: escreva o código para contar as arestas
    G->adj = new_matrix_from_file(num_V, num_V, file);
    return G;
}


void insert_edge(graph_t *G, int i, int j, int weight)
{
    if (G->adj[i][j] == 0)
    {
        G->adj[i][j] = weight;
        G->E++;
    }
}

void remove_edge(graph_t *G, int i, int j)
{
    if (G->adj[i][j] != 0)
    {
        G->adj[i][j] = 0;
        G->E--;
    }
}

void graph_toString(graph_t *G)
{
    for (int i = 0; i < G->V; i++)
    {
        for (int j = 0; j < G->V; j++)
            printf("%4d ", G->adj[i][j]);
        printf("\n");
    }
}

void free_graph(graph_t *G)
{
    for (int i = 0; i < G->V; i++)
        free(G->adj[i]);
    free(G->adj);
    free(G);
}