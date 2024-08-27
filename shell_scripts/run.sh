#!/bin/bash

#!/bin/bash

# Verifica se o número de argumentos está correto
# if [ $# -lt 6 ]; then
#     echo "Uso: $0 <arquivo_main.c> <caminho_arquivo_txt> <num_bees> <num_colors> <limit> <max_iter>"
#     exit 1
# fi

# Diretório do script
script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# Diretório do arquivo principal
# main_file="$script_dir/../$1"

# Verifica se o arquivo principal existe
# if [ ! -f "$main_file" ]; then
#     echo "Erro: Arquivo principal '$main_file' não encontrado."
#     exit 1
# fi

# Diretório que contém as instâncias
data_dir="$script_dir/../data"

# Verifica se o diretório de inclusão existe
if [ ! -d "$data_dir" ]; then
    echo "Erro: Diretório de instâncias '$data_dir' não encontrado."
    exit 1
fi

# Verifica se a compilação foi bem-sucedida
# if [ $? -eq 0 ]; then
#     echo "Compilação bem-sucedida. Executável 'main' gerado."

#     # Execução
#     # echo "Executando..."
#     # "$script_dir/main" "$2" "$3" "$4" "$5" "$6"
# else
#     echo "Erro: Falha na compilação."
# fi



# for file in $data_dir/instances/*; do
#     for bees in 10 25 50 75 100 150 200 250 300 350 400 450 500; do
#         for limit in 1 5 10 20 50 100; do
#             for max_iter in 10 50 100 500; do
#                 echo main $file $bees $limit $max_iter
#             done
#         done
#     done
# done
# <num_vertex> <caminho_arquivo_txt> <num_bees> <num_colors> <limit> <max_iter>