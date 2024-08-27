#!/bin/bash

# Path to the CSV file
csv_file="instances.csv"

# Read the CSV file line by line
tail -n +2 "$csv_file" | while IFS=';' read -r num_vertex inst_name xk k; do
    # Remove parentheses and replace '?' with 'k'
    xk=$(echo "$xk" | sed 's/[()]//g' | sed 's/?/'x'/')

    # Run the C program with the extracted arguments
    #for bees in 10 25 50 75 100 150 200 250 300 350 400 450 500; do
    for bees in 50 100 200 300 400; do
        #for limit in 5 10 15 20 25 50 75 100 150 200; do
        for limit in 5 10 25 50; do
            #for max_iter in 20 30 40 50 60 70 80; do            
            for max_iter in 20 50 70 80; do
                #for color in {$k..($k+5)}; do 
                for (( color = $k+5; color >= $k; color-- ))  do
                    for n_test in {1..10}; do
                        echo ./main "n_vert: $num_vertex" "inst: $inst_name" "bees: $bees" "limit: $limit" "max_iter: $max_iter" "colors: $color"  "test_i: $n_test"
                        ./main $num_vertex data/instances/$inst_name.txt $bees $color $limit $max_iter results/$inst_name.txt
                    done
                done
            done
        done
    done
done
# <num_vertex> <caminho_arquivo_txt> <num_bees> <num_colors> <limit> <max_iter>