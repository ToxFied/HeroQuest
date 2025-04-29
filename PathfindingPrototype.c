#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int main(void)
{                                                                                      //w1
    int steps = 0, xytab[10][2]={0}, i, j, table[6][12] = { '.','.','@','.','.','.','.','#','.','.','7','.',
                                                            '.','.','.','.','.','.','.','#','.','.','.','.',
                                                   /*w2*/   '#','#','#','#','.','#','#','#','.','.','.','.',
                                                            '.','.','.','.','.','.','.','.','.','.','@','.',
                                                            '.','B','.','.','.','.','.','#','.','.','.','.',
                                                            '.','.','.','.','.','.','@','#','.','.','.','.'};

    int monsters_pos, isdoor, **table, n, m, dest[2], wall1, wall2, door1, door2, moves[10][2], sameroom, x;
    int heroes_pos[4][2], mcount= 0;

    for(i=0; i<6; i++){
        if( monsters_pos[i] >= 1 && monsters_pos[i] <= 9 ){
            mcount++;
        }
    }

    for(i=0; i<mcount; i++){

        while (sameroom) {
        if (monsters_pos[i][1][0] < wall2 && monsters_pos[i][0][0] < wall1){ //room 1
            if (heroes_pos[i][1] <  wall2 && heroes_pos[i][0] < wall2){
                //move monster to heros pos
            } else {
                if ( wall2 < door1) {
                    //move to door 2
                } else {
                    // move to door 1
                }
            }
        } else if (monsters_pos[i][1][0] > wall2 && monsters_pos[i][0][0] < wall1) { //room 2
            if (heroes_pos[i][1] >  wall2 && heroes_pos[i][0] < wall1){
                //move monster to heros pos
            } else {
                //move to door 1
            }
        } else { // room 3
            if (heroes_pos[i][1] >  wall1){
                //move to heroes pos
            } else {
                //move to door 1
                if (heroes_pos[i][1] >  wall2 && heroes_pos[i][0] < wall1){
                    //move to heroes pos
                } else {
                    //move to door 2
                }
            }
        }
    }
}

    



}