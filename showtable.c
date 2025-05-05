#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    int **table;
    int n = 22, m = 17, i, j, level = 1, ishashtag = 0, herolist[4] = {'B', 'W', 'E', 0}, luckn, luckm, dif = 3, monsters_pos, monsters;
    int hcount=0, health;
    srand(time(NULL));
    table = (int**) malloc(n * sizeof(int*));
    for(i = 0; i < n; i++) {
        table[i] = (int*) malloc(m * sizeof(int));
    }
    for(i=0; i<4; i++){
        if(herolist[i] != 0){
            hcount++;
            continue;
        }
        break;
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

    int k = 11;

    for(int l = 0; l < level ; l++){
        for(i = k; i < k+10; i++){
            for(j=0; j<m; j++){
                table[i][j] = ' ';
                if(i == k && (j<7 || j>9)){
                    table[i][j] = '#';
                }
                else if(i > 11 && i < k+10){
                    if((j == 0 || j == m - 1)){
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
    for(j=0;j<m;j++){ // bottom wall
        table[i][j] = '#';
    }
    
    // filling the floor
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

    //O PALIATZIS
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
            // printf("%d %d\n", luckn, luckm); // Debugging line
            
            if(table[k+luckn][luckm] == '@'){   // Kanei check to @, heroes, monsters
                j--;
                continue;
            }
            else if(luckn+k == k+5 && luckm == 11){
                j--;
                continue;
            }
            else{
                table[k+luckn][luckm] = '@';
            }
        }
        k+=10;
    }
    // HEROES
    for(i=0; i<level; i++){
        for(j=0; j<hcount; j++){
            luckm = (rand() % 9)+4;
            luckn = (rand() % 6)+1;
            if(table[luckn][luckm] != '.'){
                j--;
                continue;
            }
            else{
                table[luckn][luckm] = herolist[j];
            }
        }
    }

    k=11;
    //monsters right side
    for(i=0; i<level; i++){
        switch(dif){  // deciding number of monsters
            case 1:
                monsters = (rand() % 2) +1; // Child's Play
                break;
            case 2:
                monsters = (rand() % 4) +1; // Medium
                break;
            case 3:
                monsters = (rand() % 6) +1; // Hurt me plenty	
                break;
        }
        for (j=0; j<monsters; j++) {
            luckm = (rand() % 5)+11;
            luckn = (rand() % 9)+1;
                        
            if(table[k+luckn][luckm] >= '1' && table[k+luckn][luckm] <= 'Z'){   // Kanei check to @, heroes, monsters
                j--;
                continue;
            }
            else if(luckn+k == k+5 && luckm == 5){
                j--;
                continue;
            }
            else{
                switch(dif){
                case 1: // Child's Play
                    health = (rand() % 3) +1;
                        switch(health){
                            case 1:
                                health = '1';
                                break;
                            case 2:
                                health = '2';
                                break;
                            case 3:
                                health = '3';
                                break;
                        }
                        break;
                    case 2: // Medium
                        health = (rand() % 3) +4;
                        switch(health){
                            case 4:
                                health = '4';
                                break;
                            case 5:
                                health = '5';
                                break;
                            case 6:
                                health = '6';
                                break;
                        }
                        break;
                    case 3:
                        health = (rand() % 3) +7;
                        switch(health){
                            case 7:
                                health = '7';
                                break;
                            case 8:
                                health = '8';
                                break;
                            case 9:
                                health = '9';
                                break;
                        }
                }
                table[k+luckn][luckm] = health;
            }
        k+=10;
        }
    }
    k=11;
    //monsters left side
    for(i=0; i<level; i++){
        switch(dif){  // deciding number of monsters
            case 1:
                monsters = (rand() % 2) +1; // Child's Play
                break;
            case 2:
                monsters = (rand() % 4) +1; // Medium
                break;
            case 3:
                monsters = (rand() % 6) +1; // Hurt me plenty	
                break;
        }
        for (j=0; j<monsters; j++) {
            luckm = (rand() % 5)+1;
            luckn = (rand() % 9)+4;
            // printf("%d %d\n", luckn, luckm); // Debugging line
            
            if(table[k+luckn][luckm] >= '1' && table[k+luckn][luckm] <= 'Z' ){   // Kanei check to @, heroes, monsters
                j--;
                continue;
            }
            else if(luckn+k == k+5 && luckm == 5){
                j--;
                continue;
            }
            else{ 
                switch(dif){
                case 1: // Child's Play
                    health = (rand() % 3) +1;
                    switch(health){
                        case 1:
                            health = '1';
                            break;
                        case 2:
                            health = '2';
                            break;
                        case 3:
                            health = '3';
                            break;
                    }
                    break;
                case 2: // Medium
                    health = (rand() % 3) +4;
                    switch(health){
                        case 4:
                            health = '4';
                            break;
                        case 5:
                            health = '5';
                            break;
                        case 6:
                            health = '6';
                            break;
                    }
                    break;
                case 3:
                    health = (rand() % 3) +7;
                    switch(health){
                        case 7:
                            health = '7';
                            break;
                        case 8:
                            health = '8';
                            break;
                        case 9:
                            health = '9';
                            break;
                    }
                default:
                    health = '#';
                }
                table[k+luckn][luckm] = health;
            }
        }
        k+=10;
    }
    for(i = 1; i<4; i++){ 
        table[7][6+i] = '.';
    }

    for (i = 12; i < n; i++) {
        for (j = 1; j < m; j++) {
            if(table[i][j] != '#' && table[i][j] != '@' && (table[i][j] <= '1' || table[i][j] >= 'Z')) {
                table[i][j] = '.';
            }
        }
    }
	printf("\n     \033[4m "); 

    for(k=0; k<m-1; k++){
        printf("%c ", 'A' +k);
    }
    printf("%c |", 'A' + k);
    printf("\033[0m\n");
    printf(" %.3d |", 1);
    printf("\n");
    
    for(k=0; k<n; k++){ 
        printf(" %.3d |", k+2);
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
