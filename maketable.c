#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int **table;
    int n = 22, m = 17, i, j, level =1;

    // Allocate memory for the table
    table = (int**) malloc(n * sizeof(int*));
    for(i = 0; i < n; i++) {
        table[i] = (int*) malloc(m * sizeof(int));
    }

    // Build symmetrical stage
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            table[i][j] = ' '; // Default fill (ASCII space)

            // Top wall
            if(i == 0 && j >= 3 && j <= 13) {
                table[i][j] = '#';
            }
            // Left and right walls
            else if(i > 0 && i < 7 && (j == 3 || j == 13)) {
                table[i][j] = '#';
            }
            // Middle platform
            else if(i == 7 && ((j > 2 && j < 7) || (j > 9 && j < 14))) {
                table[i][j] = '#';
            }
            // Bottom pillars
            else if(i > 7 && i < 11 && (j == 6 || j == 10)) {
                table[i][j] = '#';
            }
        }
    }

    for(int l =0; l<level ; l++){
        int k =i;
        for(i=11; i<k+10; i++){
            for(j=0; j<m; j++){
                table[i][j] = ' ';
                if(i == 11 && (j<7 || j>9)){
                    table[i][j] = '#';
                }
                else if(i > 11 && i<k+9){
                    if(j==0 || j==m-1){
                        table[i][j] = '#';
                    }
                }
            }
        }
    }

    // Print the stage
    for(i = 0; i < n; i++) {
        printf("\t\t");
        for(j = 0; j < m; j++) {
            printf("%c", table[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    for(i = 0; i < n; i++) {
        free(table[i]);
    }
    free(table);

    return 0;
}
