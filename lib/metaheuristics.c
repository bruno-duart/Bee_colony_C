#include "metaheuristics.h"
#include "graphs.h"
#include "solutions.h"

#include <stdio.h>
#include <stdlib.h>

int randint(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

int randint_diff(int min, int max, int avoid)
{
    int num;
    do
        num = randint(min, max);
    while (num == avoid);
    return num;
}

void calc_probabilities_bees(int num_bees, solution_t **bee_colony, double *probabilities)
{
    int sum_fit = 0;

    for (int i = 0; i < num_bees; ++i)
    {
        sum_fit += bee_colony[i]->num_conflitos;
    }
    for (int i = 0; i < num_bees; ++i)
    {
        probabilities[i] = (double)bee_colony[i]->num_conflitos / sum_fit;
    }
}

void employed_bee_phase(graph_t *G, int num_bees, int num_colors, solution_t **bee_colony, int *limit_no_improve)
{
    random_choice_local_search_colony(G, num_bees, num_colors, bee_colony, limit_no_improve);
}

void onlooker_bee_phase(graph_t *G, solution_t **bee_colony, int num_bees, int num_colors, int *limit_no_improve)
{
    // Implementação da fase da Abelha Observadora
    double *probabilities = (double *)malloc(sizeof(double) * num_bees);
    calc_probabilities_bees(num_bees, bee_colony, probabilities);

    double r;
    int old_fit;

    for (int i = 0; i < num_bees; ++i)
    {
        r = (double)rand() / RAND_MAX;
        // printf("bee: %f - r: %f\n", probabilities[i], r);
        if (r < probabilities[i])
        {
            old_fit = bee_colony[i]->num_conflitos;
            //random_choice_local_search(G, num_colors, bee_colony[i]);
            waggle_dance(G, num_bees, i, bee_colony);
            if (old_fit <= bee_colony[i]->num_conflitos)
                limit_no_improve[i]++;
        }
    }

    free(probabilities);
}

void scout_bee_phase(graph_t *graph, solution_t **bee_colony, int num_bees, int num_colors, int *limit_no_improv, int limit)
{
    // Implementação da fase da Abelha Escoteira
    for (int i = 0; i < num_bees; ++i)
    {
        if (limit_no_improv[i] > limit)
        {
            random_solution(num_colors, graph, bee_colony[i]);
            limit_no_improv[i] = 0;
        }
    }
}

void waggle_dance(graph_t *G, int num_bees, int idx_bee, solution_t **bee_colony)
{
    // printf("----------------------------------\n");
    int idx_other_bee = randint_diff(0, num_bees-1, idx_bee);
    // printf("idx_bee: %d\n", idx_bee);
    // printf("idx_other_bee: %d\n", idx_other_bee);

    int rand_vertex = randint(0, G->V - 1);
    // printf("rand_vertex: %d\n", rand_vertex);

    int old_color = bee_colony[idx_bee]->array[rand_vertex];
    int old_fit = bee_colony[idx_bee]->num_conflitos;
    
    // printf("old_color: %d\n", old_color);
    // printf("old_fit: %d\n", old_fit);

    bee_colony[idx_bee]->array[rand_vertex] = bee_colony[idx_other_bee]->array[rand_vertex];

    evaluate_fitness(bee_colony[idx_bee], G);

    // printf("new_color: %d\n", bee_colony[idx_bee]->array[rand_vertex]);
    // printf("new_fit: %d\n", bee_colony[idx_bee]->num_conflitos);

    if (bee_colony[idx_bee]->num_conflitos >= old_fit)
    {
        bee_colony[idx_bee]->array[rand_vertex] = old_color;
        bee_colony[idx_bee]->num_conflitos = old_fit;
    }
}

void random_choice_local_search(graph_t *G, int num_colors, solution_t *bee)
{
    int rand_vertex, old_color, old_fit;
    rand_vertex = randint(0, G->V - 1);
    old_color = bee->array[rand_vertex];
    old_fit = bee->num_conflitos;
    bee->array[rand_vertex] = randint_diff(1, num_colors, old_color);
    evaluate_fitness(bee, G);
    if (bee->num_conflitos > old_fit)
    {
        bee->array[rand_vertex] = old_color;
        bee->num_conflitos = old_fit;
    }
}

void random_choice_local_search_colony(graph_t *G, int num_bees, int num_colors, solution_t **bee_hive, int *limit_no_improve)
{
    int old_fit;
    for (int i = 0; i < num_bees; ++i)
    {
        old_fit = bee_hive[i]->num_conflitos;
        random_choice_local_search(G, num_colors, bee_hive[i]);
        if (old_fit <= bee_hive[i]->num_conflitos)
            limit_no_improve[i]++;
    }
}

solution_t **initialize_colony(graph_t *G, int num_bees, int num_colors, char method)
{
    solution_t **colony = malloc(sizeof(solution_t *) * num_bees);

    for (int idx_bee = 0; idx_bee < num_bees; idx_bee++)
    {
        if (method == 'r')
            colony[idx_bee] = initial_solution(num_colors, G);
    }
    return colony;
}

void print_colony(int num_bees, solution_t **colony, int num_vertex)
{
    for (int i = 0; i < num_bees; i++)
    {
        printf("%d : ", colony[i]->num_conflitos);
        solution_toString(colony[i], num_vertex);
    }
}

void free_colony(int num_bees, solution_t **colony)
{
    for (int i = 0; i < num_bees; i++)
        free_solution(colony[i]);

    free(colony);
}

int find_best_bee(int num_bees, solution_t **colony)
{
    int best_found = 0;

    if (num_bees > 1)
        for (int i = 1; i < num_bees; ++i)
        {
            if (colony[i]->num_conflitos < colony[best_found]->num_conflitos)
                best_found = i;
        }
    return best_found;
}

solution_t *ABC_Graph_Coloring(graph_t *G, int num_bees, int num_colors, int max_iter, int limit, int *last_iter)
{
    // Supondo que você tenha uma função para inicializar a colônia de abelhas
    solution_t **bee_colony = initialize_colony(G, num_bees, num_colors, 'r');

    int *limit_no_improve = (int *)malloc(sizeof(int) * num_bees);

    for (int i = 0; i < num_bees; i++)
    {
        limit_no_improve[i] = 0;
    }

    // print_colony(num_bees, bee_colony, G->V);
    solution_t *best_bee = new_solution(G->V);

    int idx_best_bee = find_best_bee(num_bees, bee_colony);
    copy_solution(best_bee, bee_colony[idx_best_bee], G);
    int num_iter_no_improv = 0, iter = 0;

    while (num_iter_no_improv < max_iter)
    {
        // printf("Iter: %d\n", iter++);
        // printf("-----------Employed----------\n");

        //     // Fase da Abelha Empregada
        employed_bee_phase(G, num_bees, num_colors, bee_colony, limit_no_improve);
        // print_colony(num_bees, bee_colony, G->V);

        // printf("-----------Onlooker---------\n");
        //     // Fase da Abelha Observadora
        onlooker_bee_phase(G, bee_colony, num_bees, num_colors, limit_no_improve);
        // print_colony(num_bees, bee_colony, G->V);
        // for (int i = 0; i < num_bees; i++)
        // {
        //     printf("%d ", limit_no_improve[i]);
        // }
        // printf("\n----------Scout-----------\n");
        // //     // Fase da Abelha Escoteira
        scout_bee_phase(G, bee_colony, num_bees, num_colors, limit_no_improve, limit);
        // print_colony(num_bees, bee_colony, G->V);
        // for (int i = 0; i < num_bees; i++)
        // {
        //     printf("%d ", limit_no_improve[i]);
        // }

        // printf("\n--------------------------\n");

        idx_best_bee = find_best_bee(num_bees, bee_colony);
        if (best_bee->num_conflitos > bee_colony[idx_best_bee]->num_conflitos)
        {
            copy_solution(best_bee, bee_colony[idx_best_bee], G);
            num_iter_no_improv = 0;
        }
        else
        {
            num_iter_no_improv++;
        }
        (*last_iter)++;
    }

    // idx_best_bee = find_best_bee(num_bees, bee_colony);
    // copy_solution(best_bee, bee_colony[idx_best_bee], G);

    free_colony(num_bees, bee_colony);
    free(limit_no_improve);
    return best_bee;
}
