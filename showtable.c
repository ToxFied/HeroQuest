#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int **table;
    int n = 22, m = 17, i, j;

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
            else if(i > 7 && i < 12 && (j == 6 || j == 10)) {
                table[i][j] = '#';
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
