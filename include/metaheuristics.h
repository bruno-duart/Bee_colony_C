// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>
// #include <math.h>
// #include "grafos.h"
// #include "forward_list.h"

// //solution_t *explore_neighborhood(solution_t *sol, Graph_t *graph, int num_colors);
// solution_t *simulated_annealing(solution_t *sol, Graph_t *graph, int num_colors);
// void insert_tabu_move(list_t *list, int undo_color, int index);
// int is_tabu_move(list_t *list, int undo_color, int index);
// void decrease_iterations(list_t *list);
// solution_t *tabu_search(solution_t *sol, Graph_t *graph, int num_colors);
// int find_max_conflicts(int *arr, int arr_size);
// int *count_conflicts(solution_t *sol, Graph_t *graph);
// void remove_vertex(Graph_t *graph, solution_t *sol);
// solution_t *reduce_conflicts(Graph_t *graph, int num_color);

#ifndef METAHEURISTICS_HEADER
#define METAHEURISTICS_HEADER

#include "graphs.h"
#include "solutions.h"

typedef struct _bee_t {
    solution_t *sol;
    int num_iter_no_improv;
} bee_t;

/// @brief
/// @param G
/// @param num_bees
/// @param method 'r' to random, 'g' to greedy
/// @return
solution_t **initialize_colony(graph_t *G, int num_bees, int num_colors, char method);

void print_colony(int num_bees, solution_t **colony, int num_vertex);

void free_colony(int num_vertex, solution_t **colony);

/// @brief
/// @param G
/// @param bee_colony
void employed_bee_phase(graph_t *G, int num_bees, int num_colors, solution_t **bee_colony, int *limit_no_improve);

/// @brief
/// @param G
/// @param bee_colony
void onlooker_bee_phase(graph_t *G, solution_t **bee_colony, int num_bees, int num_colors, int *limit_no_improve);

/// @brief 
/// @param graph 
/// @param bee_colony 
/// @param num_bees 
/// @param num_colors 
/// @param limit_no_improv 
/// @param limit 
void scout_bee_phase(graph_t *graph, solution_t **bee_colony, int num_bees, int num_colors, int *limit_no_improv, int limit);

void waggle_dance(graph_t *G, int num_bees, int idx_bee, solution_t **bee_colony);

/// @brief
/// @param G
/// @param bee_hive
void random_choice_local_search_colony(graph_t *G, int num_bees, int num_colors, solution_t **bee_hive, int *limit_no_improve);

void random_choice_local_search(graph_t *G, int num_colors, solution_t *bee);

int find_best_bee(int num_bees, solution_t **colony);

/// @brief
/// @param G
/// @param num_bees
/// @param max_iter
/// @return
solution_t *ABC_Graph_Coloring(graph_t *G, int num_bees, int num_colors, int max_iter, int limit, int *last_iter);

#endif