#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    int **table;
    int n = 22, m = 17, i, j, level = 1, ishashtag = 0, top1=0, bottom1=0, luckn, luckm;

    srand(time(NULL));

    // Allocate memory for the table
    table = (int**) malloc(n * sizeof(int*));
    for(i = 0; i < n; i++) {
        table[i] = (int*) malloc(m * sizeof(int));
    }

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            table[i][j] = ' ';

            // Top wall
            if(i == 0 && j >= 3 && j <= 13){
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

    int k = 11;

    for(int l = 0; l < level ; l++){
        for(i = k; i < k+10; i++){
            for(j=0; j<m; j++){
                table[i][j] = ' ';
                if(i == k && (j<7 || j>9)){
                    table[i][j] = '#';
                }
                else if(i > 11 && i<k+10){
                    if((j==0 || j==m-1)){
                        table[i][j] = '#';
                    }
                    if(((j == 6 || j == 10) && !(k+5 == i))){
                        table[i][j] = '#';
                    }
                }
            }
        }
        k+=10;
    }
    for(j=0;j<m;j++){
        table[i][j] = '#';
    }
    
    
    for (i = 1; i < 12; i++) {
        ishashtag = 0;
        for (j = 0; j < m; j++) {
            if (table[i][j] == '#' && ishashtag == 0) {
                ishashtag = 1;
                continue;      
            }
            if (table[i][j] == '#' && ishashtag == 1) {
                ishashtag = 0;
                continue;
            }
            if (ishashtag == 1 && table[i][j] != '#'){
                table[i][j] = '.';
            }
        }
    }
    
    k=11;

    for(i=0; i<level; i++){
        for (j=0; j<2; j++) {
            luckm = (rand() % 5)+1;
            luckn = (rand() % 9)+1;
            // printf("%d %d\n", luckn, luckm); // Debugging line
            if(table[k+luckn][luckm] == '@'){
                j--;
                continue;
            }
            else if(luckn+k == k+5 && luckm == 5){
                j--;
                continue;
            }
            else{
                table[luckn+k][luckm] = '@';
            }
        }
        k+=10;
    }
    
    k=11;

    for(i=0; i<level; i++){
        for (j=0; j<2; j++) {
            luckm = (rand() % 5)+11;
            luckn = (rand() % 9)+1;
            // printf("%d %d\n", luckn, luckm); // Debugging linee
            if(table[k+luckn][luckm] == '@'){
                j--;
                continue;
            }
            else if(luckn+k == k+5 && luckm == 11){
                j--;
                continue;
            }
            else{
                table[luckn+k][luckm] = '@';
            }
        }
        k+=10;
    }

    for(i = 1; i<4; i++){
        table[7][6+i] = '.';
    }

    for (i = 12; i < n; i++) {
        for (j = 1; j < m; j++) {
            if (table[i][j] != '#' && table[i][j] != '@') {
                table[i][j] = '.';
            }
        }
    }

	printf("\n     \033[4m "); 

    for(k=0; k<m-1; k++){
        printf("%c ", 'A' +k);
    }
    printf("%c ", 'A' + k);
    printf("\033[0m\n");
    printf( " %.3d %c", 1, 124);
    printf("\n");

    for(k=0; k<n; k++){ 
        printf(" %.3d %c", k+2, 124);
        for( i = 0; i < m; i++) {
            printf("%c ", table[k][i]);
        }
        printf("\n");
    }
    for(i=0; i<n; i++){
        free(table[i]);
    }
    free(table);
    return 0;
}