#ifndef GRAPH_HEADER
#define GRAPH_HEADER

#include <stdio.h>

typedef struct _graph_t {
    int V;
    int E;
    int **adj;
} graph_t;

/// @brief Creates a new_matrix and fill it's cells from console
/// @param rows number of rows
/// @param columns number of columns
/// @return a new matrix
int** new_matrix(int rows, int columns);

int **new_matrix_from_file(int rows, int columns, FILE *file);

/// @brief 
/// @param num_V 
/// @return 
graph_t* new_graph(int num_V);

graph_t *new_graph_from_file(int num_V, FILE *file);

/// @brief 
/// @param G 
/// @param i 
/// @param j 
/// @param weight 
void insert_edge(graph_t* G, int i, int j, int weight);

/// @brief 
/// @param G 
/// @param i 
/// @param j 
void remove_edge(graph_t* G, int i, int j);

/// @brief 
/// @param G 
void graph_toString(graph_t* G);

/// @brief 
/// @param G 
void free_graph(graph_t* G);

#endif