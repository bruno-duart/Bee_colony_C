#include "solutions.h"
#include "graphs.h"

#include <stdio.h>
#include <stdlib.h>

solution_t *new_solution(int num_vertices)
{
    /**
     * Função para inicializar uma nova solução.
     * @param num_vertices : número de vértices contidos em uma solução
     * @return solution_t : uma nova solução
     */
    solution_t *sol = malloc(sizeof(solution_t));
    sol->array = malloc(sizeof(int) * num_vertices);
    sol->num_conflitos = 0;

    for (int i = 0; i < num_vertices; i++)
        sol->array[i] = -1;

    return sol;
}

void free_solution(solution_t *sol)
{
    /**
     * Função para liberar a memória alocada de uma solução.
     * É liberada a memória do array de vértices e em seguida
     * a memória da estrutura solution_t
     * @param sol : solução a ter sua memória liberada
     */
    free(sol->array);
    free(sol);
}

void evaluate_fitness(solution_t *sol, graph_t *graph)
{
    /**
     * Função para calcular a fitness de cada solução. Comparam-se as cores
     * de cada vértice com as cores de seus adjacentes. A matriz é percorrida
     * linha a linha, e conta o número de conflitos.
     * @param sol : solução a ter sua fitness calculada
     * @param graph : grafo que contém a matriz de adjacências
     *
     */
    sol->num_conflitos = 0;
    for (int i = 0; i < graph->V; i++)
    {
        if (graph->adj[i][i] != -1)
        {
            for (int j = i + 1; j < graph->V; j++)
            {
                if (sol->array[i] == sol->array[j] && graph->adj[i][j] != 0)
                {
                    sol->num_conflitos++;
                }
            }
        }
    }
    // for(int i=0; i < graph->V; i++){
    //     if(sol->array[i] == -1){
    //         sol->spilling++;
    //     }
    // }
}

void random_solution(int num_color, graph_t *graph, solution_t *sol){
 for (int i = 0; i < graph->V; i++)
    {
        if (graph->adj[i][i] == -1)
        {
            sol->array[i] = -1;
        }
        else
        {
            sol->array[i] = (rand() % num_color) + 1;
        }
    }

    evaluate_fitness(sol, graph);

}

solution_t *initial_solution(int num_color, graph_t *graph)
{
    /**
     * Função para construir uma solução inicial. As cores de cada
     * vértice são escolhidas aleatoriamente. Após o término dos
     * sorteios, a fitness é calculada.
     * @param num_color : número de cores disponíveis para seleção
     * @param graph : grafo a partir do qual a solução é criada
     * @return solution_t : uma nova solução
     */
    solution_t *sol = new_solution(graph->V);

    random_solution(num_color, graph, sol);  
    return sol; 
}
void solution_toString(solution_t *sol, int num_vertex)
{
    /**
     * Função para exibir o array de cores de uma solução.
     * @param sol: solução a ser exibida
     * @param num_vertex: número de vértices a ser exibido
     */
    for (int i = 0; i < num_vertex; i++)
    {
        printf("%4d ", sol->array[i]);
    }
    printf("\n");
}

void copy_solution(solution_t *new, solution_t *old, graph_t *graph)
{
    /**
     * Função para copiar as cores e a fitness de uma solução
     * para outra.
     * @param new : solução que vai receber a cópia
     * @param old : solução que vai ser copiada
     * @param graph : grafo que contém os vértices
     */
    for (int i = 0; i < graph->V; i++)
    {
        new->array[i] = old->array[i];
    }
    new->num_conflitos = old->num_conflitos;
}

void explore_neighborhood(solution_t *new_sol, solution_t *sol, graph_t *graph, int num_colors)
{
    /**
     * Função para realizar uma exploração na vizinhança.
     * Uma nova solução é obtida ao variar a cor de um unico vértice.
     * @param new_sol : endereço de memória para a nova solução
     * @param sol: solução a ter a vizinhança explorada
     * @param graph: grafo de adjacências
     * @param num_colors: número de cores disponíveis
     */
    int num_index;
    do
    {
        num_index = rand() % graph->V;
    } while (graph->adj[num_index][num_index] == -1);

    copy_solution(new_sol, sol, graph);

    do
    {
        new_sol->array[num_index] = (rand() % num_colors) + 1;
    } while (new_sol->array[num_index] == sol->array[num_index]);

    evaluate_fitness(new_sol, graph);
}