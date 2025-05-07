#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

void move(int **table, int **move, int pos_i, int pos_j, int **heroOnRoomPos);
int pathfinder(int **table, int pos_i, int pos_j, int flag, int dest_i, int dest_j);

#define n 92
#define level 8

int main(void) {
    int **table;
    int m = 17, i, j, ishashtag = 0, herolist[4] = {'B', 0, 0, 0}, luckn, luckm, dif = 2, monster_max=0, mcount;
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

void play(){
    
}

int move(int **table, int **move, int pos_i, int pos_j, int **heroOnRoomPos) {
    int i, j, min, temp;
    int heroOnRoom = 0;
    int k=((pos_i-11)/10)+1; // Room number
    int upperWall = 11 +((k-1)*10);
    int whichRoom=0;
    int checking_i=3;
    int checking_j=3;
    int attack =0;
    // Finds a hero 
    // on the left room and saves the position

    if(pos_j >= 1 && pos_j <= 5){ // left room
        whichRoom = 1;
    }
    else if(pos_j >= 7 && pos_j <= 9) { // mid room
        whichRoom = 2;
    }
    else if(pos_j>=11 && pos_j<=15){ // right room
        whichRoom = 3;
    }
    else if(pos_i <= 6){ // spawn room
        whichRoom = 4;
    }
    else{ //debuging room
        printf("\e[1;95m We got a problem! Room wasn't detected. \e[0;0m");    
        return 0;
    }
    if(whichRoom == 1){ // left room
        for (i=0; i<9; i++){
            for (j=0; j<5; j++){
                if (table[upperWall+1+i][j+1] >= 'A' && table[upperWall+1+i][j+1] <= 'Z') {
                    heroOnRoomPos[heroOnRoom][i] = i+upperWall+1;
                    heroOnRoomPos[heroOnRoom][j] = j+1;
                    heroOnRoom++;
                    break;
                }
            }
        }
    }
    else if(whichRoom == 2){ // mid room
        for (i=0; i<n-8; i++){
            for (j=0; j<3; j++){
                if (table[7+i][j+7] >= 'A' && table[7+i][j+7] <= 'Z') {
                    heroOnRoomPos[heroOnRoom][i] = i+7;
                    heroOnRoomPos[heroOnRoom][j] = j+7;
                    heroOnRoom++;
                    break;
                }
            }
        }
    }
    else if(whichRoom == 3){ // right room
        for (i=0; i<9; i++){
            for (j=0; j<5; j++){
                if (table[upperWall+1+i][j+11] >= 'A' && table[upperWall+1+i][j+11] <= 'Z') {
                    heroOnRoomPos[heroOnRoom][i] = i+upperWall+1;
                    heroOnRoomPos[heroOnRoom][j] = j+11;
                    heroOnRoom++;
                    break;
                }
            }
        }
    }
    else if(whichRoom == 4){  // spawn room
        for (i=0; i<6; i++){
            for (j=0; j<9; j++){
                if (table[1+i][j+4] >= 'A' && table[1+i][j+4] <= 'Z') {
                    heroOnRoomPos[heroOnRoom][i] = i+1;
                    heroOnRoomPos[heroOnRoom][j] = j+4;
                    heroOnRoom++;
                    break;
                }
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
    if(heroOnRoom){
        int count1 =1;
        int count2 =0;
        int MoveCountI = 0;
        int MoveCountJ = 0;
        int step =0;
        while(step<10){ // should add a check for error code
            while(step < 10 && (checking_i != -1 || checking_i != 0) && checking_i!= -2){
                if(pathfinder(table, move[count2][0], move[count2][1], 1, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == -1){
                    if(checking_j == -1){
                        MoveCountJ++;
                        move[count1][0] = pos_i + MoveCountI;
                        move[count1][1] = pos_j + MoveCountJ;
                        step++;
                        count2=count1;
                        count1++;
                        checking_j = 5;
                        continue;
                    }
                    checking_i = -1; // Blocked
                    continue;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 1, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == -2){
                    checking_i = -2; // Error
                    checking_j = -2; // Error
                    continue;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 1, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == 0){
                    checking_i = 0; // No movement needed
                    continue;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 1, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == 1){
                    MoveCountI++;
                    move[count1][0] = pos_i + MoveCountI;
                    move[count1][1] = pos_j + MoveCountJ;
                    step++;
                    count2=count1;
                    count1++;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 1, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == 2){
                    MoveCountI--;
                    move[count1][0] = pos_i + MoveCountI;
                    move[count1][1] = pos_j + MoveCountJ;
                    step++;
                    count2=count1;
                    count1++;
                }
            }
            while(step < 10 && (checking_j != -1 || checking_j != 0) && checking_j!= -2){
                if(pathfinder(table, move[count2][0], move[count2][1], 0, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == -1){
                    if(checking_i == -1){
                        MoveCountJ++;
                        move[count1][0] = pos_i + MoveCountI;
                        move[count1][1] = pos_j + MoveCountJ;
                        step++;
                        count2=count1;
                        count1++;
                        checking_i = 0;
                        continue;
                    }
                    checking_j = -1; // Blocked
                    continue;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 0, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == -2){
                    checking_i = -2; // Error
                    checking_j = -2; // Error
                    continue;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 0, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == 0){
                    checking_j = 0; // No movement needed
                    continue;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 0, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == 1){
                    MoveCountJ++;
                    move[count1][0] = pos_i + MoveCountI;
                    move[count1][1] = pos_j + MoveCountJ;
                    step++;
                    count2=count1;
                    count1++;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 0, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == 2){
                    MoveCountJ--;
                    move[count1][0] = pos_i + MoveCountI;
                    move[count1][1] = pos_j + MoveCountJ;
                    step++;
                    count2=count1;
                    count1++;
                }
            }
            if(checking_i == -2 || checking_j == -2)
            {
                printf("there was a problem in pathfinder\n");
                return 0;
            }
            else if(checking_i ==0 && checking_j == 0){
                return 1;
            }
            else{
                return 0;
            }
        }
    }
}    

int pathfinder(int **table, int pos_i, int pos_j, int flag, int dest_i, int dest_j){
    
    if (flag){
        if (pos_i < dest_i){
            if ((table[pos_i + 1][pos_j] >= '1' && table[pos_i + 1][pos_j] <= 'Z' ) || table[pos_i + 1][pos_j] == '#') {
                return -1; // Blocked
            } else {
                return 1; // Move down
            }
        } else if (pos_i > dest_i){
            if ((table[pos_i - 1][pos_j] >= '1' && table[pos_i - 1][pos_j] <= 'Z' ) || table[pos_i - 1][pos_j] == '#') {
                else{
                    return -1; // Blocked
                }
            } else {
                return 2; // Move up
            }

        } else {
            return 0; // No movement needed
        }
    } else {
        if (pos_j < dest_j){
            if ((table[pos_i][pos_j + 1] >= '1' && table[pos_i][pos_j + 1] <= 'Z' ) || table[pos_i][pos_j + 1] == '#') {
                return -1; // Blocked
            } else {
                return 1; // Move right
            }
        } else if (pos_j > dest_j){
            if ((table[pos_i][pos_j - 1] >= '1' && table[pos_i][pos_j - 1] <= 'Z' ) || table[pos_i][pos_j - 1] == '#') {
                return -1; // Blocked
            } else {
                return 2; // Move left
            }
        } else {
            return 0; // No movement needed
        }
    }
    printf("\e[1;95m We got a problem! Pathfinding failed. \e[0;0m");
    return -2; // Error case
}