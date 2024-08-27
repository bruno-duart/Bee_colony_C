#ifndef SOLUTIONS_HEADER
#define SOLUTIONS_HEADER

#include "graphs.h"

typedef struct _solution_t
{
    int *array;
    int num_conflitos;
    // int spilling;
} solution_t;

/// @brief
/// @param num_vertices
/// @return
solution_t *new_solution(int num_vertices);

/// @brief
/// @param sol
void free_solution(solution_t *sol);

/// @brief
/// @param sol
/// @param graph
void evaluate_fitness(solution_t *sol, graph_t *graph);

void random_solution(int num_color, graph_t *graph, solution_t *so);

/// @brief
/// @param num_color
/// @param graph
/// @return
solution_t *initial_solution(int num_color, graph_t *graph);

/// @brief
/// @param num_color
/// @param nth_index
/// @param graph
/// @return
// solution_t *greedy_solution_nth_index(int num_color, int nth_index, graph_t *graph);

/// @brief
/// @param sol
/// @param num_vertex
void solution_toString(solution_t *sol, int num_vertex);

/// @brief
/// @param
/// @param old
/// @param graph
void copy_solution(solution_t *new, solution_t *old, graph_t *graph);

/// @brief
/// @param new_sol
/// @param sol
/// @param graph
/// @param num_colors
void explore_neighborhood(solution_t *new_sol, solution_t *sol, graph_t *graph, int num_colors);

#endif