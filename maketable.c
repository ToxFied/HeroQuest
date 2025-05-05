#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int **table;
    int n = 22, m = 17, i, j, level =1;

    table = (int**) malloc(n * sizeof(int*));
    for(i = 0; i < n; i++) {
        table[i] = (int*) malloc(m * sizeof(int));
    }

    // build standard room
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            table[i][j] = ' '; // fill all with space
            if(i == 0 && j >= 3 && j <= 13) {
                table[i][j] = '#'; //top
            }
            else if(i > 0 && i < 7 && (j == 3 || j == 13)) {
                table[i][j] = '#'; // left and right
            }
            else if(i == 7 && ((j > 2 && j < 7) || (j > 9 && j < 14))) {
                table[i][j] = '#'; //midle
            }
            else if(i > 7 && i < 11 && (j == 6 || j == 10)) { 
                table[i][j] = '#'; //bottom
            }
        }
    }
    for(int l =0; l<level ; l++){  //room generation depending the level
        int k =11;
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
