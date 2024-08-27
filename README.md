# Bee_colony_C

 * Estrutura de grafo: matriz de adjacências (int)
 * Estrutura de uma solução : struct com array de inteiros (cores dos vértices) e int (fitness)
 * Implementação da metaheurística Artificial Bee Colony:
   *  Para compilar, utilizzar comando "bash shell_script/compile.sh main_file.c"
   *  Realizado "gridsearch" nos parâmetros .Parâmetros testados estão no arquivo 'shell_script/read_instance.sh': necessário rodar com comando bash "bash shell_script/read_instance.sh"
   *  Para executar somente um caso de teste, seguir o padrão:
     
 ``` ./main <num_vertex> <caminho_arquivo_txt> <num_bees> <num_colors> <limit> <max_iter> ```

Ex: 

    ./main 11 data/instances/myciel3.txt 20 6 5 100  

Pasta include: contém os arquivos ".h"
Pasta lib: contém as implementações em ".c"
Utilizando o read_instance.sh, resultados serão salvos na pasta 'results'


Necessário ter compilador gcc instalado.
Código testado e executado somente em sistema linux.
