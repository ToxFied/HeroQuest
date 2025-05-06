#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

void move(int **table, int **move, int pos_i, int pos_j, int des_i, int des_j);
void pathfinder(int **table, int **move, int pos_i, int pos_j, int des_i, int des_j);

int main(void) {
    int **table;
    int n = 42, m = 17, i, j, level = 3, ishashtag = 0, herolist[4] = {'B', 0, 0, 0}, luckn, luckm, dif = 2, monster_max=0, mcount;
    int hcount=0, health, move[11][2];
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
            
            if(table[k+luckn][luckm] == '@'){   // Kanei check to @, heroes, mcount
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
    k=11;
    
    //LEFT MONSTERS
    monster_max = 2*dif;
    for(i=0; i<level; i++){
        mcount = (rand() % monster_max) + 1;
        for (j=0; j<mcount; j++) {
            luckm = (rand() % 5)+1;
            luckn = (rand() % 9)+1;
            
            if(table[k+luckn][luckm] >= '1' && table[k+luckn][luckm] <= 'Z' ){   // Kanei check to @, heroes, monsters
                j--;
                continue;
            }
            else if(luckn+k == k+5 && luckm == 5){ // Door case
                j--;
                continue;
            }
            else if((k+luckn == k+1 && luckm == 1) || (k+luckn == k+9 && luckm == 1) ||            // Corner cases for left side
                    (k+luckn == k+1 && luckm == 5) || (k+luckn == k+9 && luckm == 5)){
                j--;
                continue;
            }
            else{
                health = 3*dif-rand()%3;
                table[k+luckn][luckm] = health + '0';
            }
        }
        k+=10;
    }
    k=11;
    //RIGHT MONSTERS
    monster_max = 2*dif;
    for(i=0; i<level; i++){
        mcount = (rand() % monster_max) + 1;
        for (j=0; j<mcount; j++) {
            luckm = (rand() % 5)+11;
            luckn = (rand() % 9)+1;
            
            if(table[k+luckn][luckm] >= '1' && table[k+luckn][luckm] <= 'Z' ){   // Kanei check to @, heroes, monsters
                j--;
                continue;
            }
            else if(luckn+k == k+5 && luckm == 11){
                j--;
                continue;
            }
            else if((k+luckn == k+1 && luckm == 11) || (k+luckn == k+9 && luckm == 11) || 
                (k+luckn == k+1 && luckm == 15) || (k+luckn == k+9 && luckm == 15)) { // Corner cases for right side
                    j--;
                    continue;
            }
            else{
                health = 3*dif-rand()%3;
                table[k+luckn][luckm] = health + '0';
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

void move(int **table, int **move, int pos_i, int pos_j, int **heroOnRoomPos) {
    int i, j, min, temp;
    int heroOnRoom = 0;
    
    // Finds a hero on the left room and saves the position
    for (i=0; i<9; i++){
        for (j=0; j<5; j++){
            if (table[k+i][j+1] >= 'A' && table[k+i][j+1] <= 'Z') {
                heroOnRoomPos[heroOnRoom][i] = i+k;
                heroOnRoomPos[heroOnRoom][j] = j+1;
                heroOnRoom++;
                break;
            }
        }
    }

    if (heroOnRoom) {
        min = (heroOnRoomPos[0][0] + heroOnRoomPos[0][1]) - (pos_i + pos_j); // Arxikopoiei to min
    }

    if(heroOnRoom >1){
        for (i=1; i<heroOnRoom; i++){
            temp = (heroOnRoomPos[i][0] + heroOnRoomPos[i][1]) - (pos_i + pos_j);
            if (temp < min){
                min = temp;
                i--;
            }
        }
    }
    // Finds a hero on the right room and saves the position
    for (i=0; i<9; i++){
        for (j=0; j<5; j++){
            if (table[k+i][j+11] >= 'A' && table[k+i][j+1] <= 'Z') {
                heroOnRoomPos[heroOnRoom][i] = i+k;
                heroOnRoomPos[heroOnRoom][j] = j+1;
                heroOnRoom++;
                break;
            }
        }
    }

    if (heroOnRoom) {
        min = (heroOnRoomPos[0][0] + heroOnRoomPos[0][1]) - (pos_i + pos_j);
    }
    if(heroOnRoom >1){
        for (i=1; i<heroOnRoom; i++){
            temp = (heroOnRoomPos[i][0] + heroOnRoomPos[i][1]) - (pos_i + pos_j);
            if (temp < min){
                min = temp;
                i--;
            }
        }
    }

}    

void pathfinder(int **table, int **move, int pos_i, int pos_j, int des_i, int des_j){
    int flag=0, i, j, step, flag1=0, flag2=0;
    move[0][0] = pos_i;
    move[0][1] = pos_j;
    while(!flag){
        while(step<10 && !flag1){
            if(pos_i > des_i){
                if(table[pos_i-1][pos_j] <= 'Z' && table[pos_i-1][pos_j] >= '0' && table[pos_i][pos_j-1] == '#'){
                    break;
                }
                step++;
                pos_i--;
                move[step][0] = pos_i;
            }
            else if(pos_i < des_i){
                if(table[pos_i+1][pos_j] <= 'Z' && table[pos_i+1][pos_j] >= '0' && table[pos_i][pos_j-1] == '#'){
                    break;
                }
                step++;
                pos_i++;
                move[step][0] = pos_i;
            }
            else{
                flag1=1;
                break;
            }
        }
        while(step<10 && !flag2){
            if(pos_i > des_i){
                if(table[pos_i][pos_j-1] <= 'Z' && table[pos_i][pos_j-1] >= '0' && table[pos_i][pos_j-1] == '#'){
                    break;
                }
                step++;
                pos_j--;
                move[step][1] = pos_j;
            }
            else if(pos_i < des_i){
                if(table[pos_i][pos_j+1] <= 'Z' && table[pos_i][pos_j+1] >= '0' && table[pos_i][pos_j-1] == '#'){
                    break;
                }
                step++;
                pos_j++;
                move[step][1] = pos_j;
            }
            else{
                flag2=1;
                break;
            }
        }
    }
}