#!/bin/bash

# Verifica se o número de argumentos está correto
# if [ $# -lt 6 ]; then
#     echo "Uso: $0 <arquivo_main.c> <caminho_arquivo_txt> <num_bees> <num_colors> <limit> <max_iter>"
#     exit 1
# fi

# Diretório do script
script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# Diretório do arquivo principal
main_file="$script_dir/../$1"

# Verifica se o arquivo principal existe
if [ ! -f "$main_file" ]; then
    echo "Erro: Arquivo principal '$main_file' não encontrado."
    exit 1
fi

# Diretório de inclusão
include_dir="$script_dir/../include/"

# Verifica se o diretório de inclusão existe
if [ ! -d "$include_dir" ]; then
    echo "Erro: Diretório de inclusão '$include_dir' não encontrado."
    exit 1
fi

# Compilação
echo "Compilando..."
gcc "$main_file" -I"$include_dir" "$script_dir"/../lib/*.c -o "$script_dir/../main"

# Verifica se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilação bem-sucedida. Executável 'main' gerado."

    # Execução
    # echo "Executando..."
    # "$script_dir/main" "$2" "$3" "$4" "$5" "$6"
else
    echo "Erro: Falha na compilação."
fi
